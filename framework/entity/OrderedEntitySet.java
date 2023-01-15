package framework.entity;

public class OrderedEntitySet extends EntitySet {
  private String orderByField;
  private boolean ascend;

  OrderedEntitySet(String orderByField, boolean ascend) {
    super();
    this.orderByField = orderByField;
    this.ascend = ascend;
  }

  public void addEntity(Entity entity) {
    Object target = entity.getValue(orderByField);
    if (!(target instanceof Comparable))
      super.addEntity(entity);

    int i=0;

    while (true) {
      Entity e;
      if (i < entities.size())
        e = (Entity)entities.get(i);
      else break;
      Object value = e.getValue(orderByField);
      if (ascend ^ (((Comparable)value).compareTo(target) <= 0))
        break;
      i++;
    }
    entities.add(i, entity);
  }

  public void addSet(EntitySet set) {
    set.toFirst();
    while (set.hasNext())
      addEntity(set.nextEntity());
  }
}