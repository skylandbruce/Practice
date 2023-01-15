package framework.entity;

import java.util.LinkedList;

public class EntitySet {
  protected LinkedList entities;
  protected int index;

  EntitySet() {
    entities = new LinkedList();
    index = 0;
  }

  public void toFirst() {
    index = 0;
  }

  public boolean hasNext() {
    return (index >= 0) && (index < entities.size());
  }

  public Entity nextEntity() {
    Entity entity = null;
    try {
      entity = (Entity)entities.get(index++);
    }
    catch (IndexOutOfBoundsException e) {
      return null;
    }
    return entity;
  }

  public void addEntity(Entity entity) {
    entities.add(entity);
  }

  public void addSet(EntitySet set) {
    entities.addAll(set.entities);
  }

  void setEntityKit(EntityKit kit) {
    for (int i=0; i<entities.size(); i++)
      ((Entity)entities.get(i)).setEntityKit(kit);
  }

  void clearState() {
    for (int i=0; i<entities.size(); i++)
      ((Entity)entities.get(i)).clearState();
  }

  public Entity[] getEntityList() {
    return (Entity[])entities.toArray(new Entity[0]);
  }

  public Entity[] getEntityList(Entity[] type) {
    return (Entity[])entities.toArray(type);
  }
}