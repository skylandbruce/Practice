package framework.entity;

import java.util.*;

public abstract class Persistence {
  public Persistence() {
  }	
  public abstract void setDatabase(String database);

  public abstract Entity fetchEntity(Entity entity, String key) throws PersistenceException;

  public abstract void fetch(EntitySet set, Entity prototype, Condition condition) throws PersistenceException;
  
  public abstract void insert(Entity entity) throws PersistenceException;

  public abstract void update(Entity entity) throws PersistenceException;

  public abstract void delete(Entity entity) throws PersistenceException;

  public HashMap getValueTable(Entity entity) {
    return entity.getValueTable();
  }
}
