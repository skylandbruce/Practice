package framework.entity;

import java.util.*;
import framework.util.UniqueGenerator;

public class EntityKit {
  private Persistence persister;
  private HashMap entityPrototypes; // entity_name, entity_object
  private EntityCache cache;
  private UniqueGenerator unique;
 
  public EntityKit(Persistence p, long cacheExpirationTime) {
    persister = p;
    unique = UniqueGenerator.instance();
    cache = new EntityCache(cacheExpirationTime, 30000);
    entityPrototypes = new HashMap();
  }

  public Persistence getPersistence() {
    return persister;
  }

  public void registerEntityPrototype(Entity prototype) {
    entityPrototypes.put(prototype.getEntityName(), prototype);
  }

  public Entity getNewEntity(String entityName) {
    Entity prototype = (Entity)entityPrototypes.get(entityName);
    if (prototype == null)
      return null;
    Entity entity = prototype.getInstance();
    entity.setEntityKit(this);
    entity.setKey(entityName + "_" + unique.getUniqueNumber());
    return entity;
  }

  public Entity getEntity(String key) throws PersistenceException {
    Entity entity = cache.get(key);
    if (entity == null) {
      Entity prototype = (Entity)entityPrototypes.get(getKeyPrefix(key));
      if (prototype == null)
        return null;
      entity = prototype.getInstance();
      entity = persister.fetchEntity(entity, key);
      if (entity == null)
        return null;
      entity.setKey(key);
      entity.setEntityKit(this);
      entity.clearState();
      cache.put(entity);
    }
    return entity;
  }

  public EntitySet getEntitySet(String entityName, Condition condition) throws PersistenceException {
    EntitySet set = new EntitySet();
    return getEntitySet(set, entityName, condition);
  }

  public EntitySet getEntitySet(String entityName, Condition condition, String orderByField, boolean ascend) throws PersistenceException {
    EntitySet set = new OrderedEntitySet(orderByField, ascend);
    return getEntitySet(set, entityName, condition);
  }

  private EntitySet getEntitySet(EntitySet set, String entityName, Condition condition) throws PersistenceException {
    Entity prototype = (Entity)entityPrototypes.get(entityName);
    if (prototype == null)
      return set;
    cache.fetch(set, prototype, condition);
    EntitySet newSet = new EntitySet();
    Condition onlyNewEntityCondition = onlyNewEntityCondition(set, condition);
    persister.fetch(newSet, prototype, onlyNewEntityCondition);
    newSet.setEntityKit(this);
    newSet.clearState();
    cache.put(newSet);
    set.addSet(newSet);
    return set;
  }

  private Condition onlyNewEntityCondition(EntitySet exclusive, Condition condition) {
    Condition newCon = condition;
    exclusive.toFirst();
    while (exclusive.hasNext()) {
      Entity entity = (Entity)exclusive.nextEntity();
      newCon = new Condition(newCon, true, new Condition("entitykey", "<>", entity.getKey()));
    }
    return newCon;
  }

  public void insert(Entity entity) throws PersistenceException {
    cache.cacheUp(entity);
    persister.insert(entity);
  }

  public void update(Entity entity) throws PersistenceException {
    cache.cacheUp(entity);
    persister.update(entity);
  }

  public void delete(Entity entity) throws PersistenceException {
    cache.remove(entity);
    persister.delete(entity);
  }

  static String getKeyPrefix(String key) {
    if (key == null)
      return null;
    if (key.indexOf("_") < 0)
      return "";
    return key.substring(0, key.indexOf("_"));
  }

  public void destroy() {
    cache.stop();
    cache = null;
    entityPrototypes = null;
    persister = null;
    unique = null;
  }

  protected void finalize() {
    destroy();
  }
}