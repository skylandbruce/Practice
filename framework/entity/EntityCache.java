package framework.entity;

import java.util.*;

class TimedEntity {
  Entity entity;
  long markTime;

  TimedEntity(Entity e, long time) {
    entity = e;
    markTime = time;
  }

  void updateTime(long newTime) {
    markTime = newTime;
  }
}

public class EntityCache implements Runnable {
  private HashMap entities;
  private long expirationTime;
  private long sleepTime;
  private Thread cleaner;

  public EntityCache(long expirationTime, long sleepTime) {
    entities = new HashMap();
    this.expirationTime = expirationTime;
    this.sleepTime = sleepTime;
    cleaner = new Thread(this);
    cleaner.start();
  }

  public synchronized void put(Entity entity) {
    HashMap classEntities = (HashMap)entities.get(entity.getEntityName());
    if (classEntities == null) {
      classEntities = new HashMap();
      entities.put(entity.getEntityName(), classEntities);
    }
    classEntities.put(entity.getKey(), new TimedEntity(entity, System.currentTimeMillis()));
  }

  public synchronized void put(EntitySet set) {
    set.toFirst();
    while (set.hasNext()) {
      put(set.nextEntity());
    }
  }

  public synchronized Entity get(String key) {
    HashMap classEntities = (HashMap)entities.get(EntityKit.getKeyPrefix(key));
    if (classEntities == null)
      return null;
    TimedEntity te = (TimedEntity)classEntities.get(key);
    if (te == null)
      return null;
    te.updateTime(System.currentTimeMillis());
    return te.entity;
  }

  public synchronized void fetch(EntitySet set, Entity prototype, Condition condition) {
    HashMap classEntities = (HashMap)entities.get(prototype.getEntityName());
    if (classEntities == null)
      return;
    Iterator keys = classEntities.keySet().iterator();

    while (keys.hasNext()) {
      TimedEntity te = (TimedEntity)classEntities.get(keys.next());
      Entity entity = te.entity;
      if (condition.satisfy(entity)) {
        set.addEntity(entity);
        te.updateTime(System.currentTimeMillis());
      }
    }
  }

  public synchronized void remove(Entity entity) {
    HashMap classEntities = (HashMap)entities.get(entity.getEntityName());
    if (classEntities != null)
      classEntities.remove(entity.getKey());
  }

  public synchronized void cacheUp(Entity entity) {
    HashMap classEntities = (HashMap)entities.get(entity.getEntityName());
    if (classEntities == null) {
      classEntities = new HashMap();
      entities.put(entity.getEntityName(), classEntities);
    }
    TimedEntity te = (TimedEntity)classEntities.get(entity.getKey());
    if (te == null) {
      te = new TimedEntity(entity, System.currentTimeMillis());
      classEntities.put(entity.getKey(), te);
    }
    else
      te.updateTime(System.currentTimeMillis());
  }

  private synchronized void cleanUp() {
    System.out.println("start cleaning cache..." + this);

    Iterator entityNames = entities.keySet().iterator();

    while (entityNames.hasNext()) {
      String entityName = (String)entityNames.next();
      HashMap classEntities = (HashMap)entities.get(entityName);
      Iterator keys = classEntities.keySet().iterator();
      long current = System.currentTimeMillis();
  
      while (keys.hasNext()) {
        Object key = keys.next();
        TimedEntity te = (TimedEntity)classEntities.get(key);

        // for debug...
        System.out.println("entity[" + te.entity.getKey() + "]: " + (current - te.markTime));

        if (current - te.markTime > expirationTime)
          keys.remove();
      }
      if (classEntities.isEmpty())
        entityNames.remove();
    }
    System.out.println("end cleaning cache...");
  }

  private boolean stopped = false;
  public void run() {
    while (true) {
      try {
        Thread.sleep(sleepTime);
      }
      catch (InterruptedException e) {
      }
      cleanUp();
      if (stopped)
        break;
    }
  }

  public void stop() {
    stopped = true;
  }
}
