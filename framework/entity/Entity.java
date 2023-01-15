package framework.entity;

import java.util.*;

public abstract class Entity {
  public final static int STATE_NEW = 1;
  public final static int STATE_CLEARED = 2;
  public final static int STATE_UPDATED = 3;
  public final static int STATE_DELETED = 4;
  public final static int STATE_INVALID = -1;

  public final static int MT_DEFAULT = 0;
  public final static int MT_INTEGER = 1;
  public final static int MT_DOUBLE = 2;
  public final static int MT_STRING = 3;
  public final static int MT_DATE = 4;
  public final static int MT_TIME = 5;
  public final static int MT_TIMESTAMP = 6;

  protected int state;
  protected HashMap fieldValues;
  protected EntityKit kit;
  protected String key;

  protected Entity() {
    fieldValues = new HashMap();
    state = STATE_NEW;
  }

  public abstract Entity getInstance();

  public abstract MetaInfo getMetaInfo();

  void setEntityKit(EntityKit kit) {
    this.kit = kit;
  }

  public void clearState() {
    state = STATE_CLEARED;
  }

  public void delete() throws PersistenceException {
    if (state == STATE_NEW)
      state = STATE_INVALID;
    else
      state = STATE_DELETED;
    save();
  }

  public void update() {
    if (state == STATE_CLEARED)
      state = STATE_UPDATED;
  }

  public void save() throws PersistenceException {
    if (state == STATE_NEW) {
      kit.insert(this);
      state = STATE_CLEARED;
    }
    else if (state == STATE_UPDATED) {
      kit.update(this);
      state = STATE_CLEARED;
    }
    else if (state == STATE_DELETED) {
      kit.delete(this);
      state = STATE_INVALID;
    }
  }

  public void setKey(String key) {
    this.key = key;
  }

  public String getKey() {
    return key;
  }

  public String getEntityName() {
    return getMetaInfo().getMetaTitle();
  }

  protected void registerField(String fieldName, Object initValue) {
    fieldValues.put(fieldName, initValue);
  }
  
// Setter Getter fieldValue typed Object class
  protected Object getValue(String fieldName) {
    return fieldValues.get(fieldName);
  }

  protected void setValue(String fieldName, Object value) {
    if (fieldValues.containsKey(fieldName))
      fieldValues.put(fieldName, value);
    update();
  }

  public boolean equals(Object other) {
    if (other == null)
      return false;
    if (other instanceof Entity) {
      return key.equals(((Entity)other).getKey());
    }
    return false;
  }

  HashMap getValueTable() {
    return fieldValues;
  }
}