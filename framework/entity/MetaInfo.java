package framework.entity;

public class MetaInfo {
  private String metaTitle;
  private MetaType[] fieldTypes;

  public MetaInfo(String title, MetaType[] types) {
    metaTitle = title;
    fieldTypes = types;
  }

  public String getMetaTitle() {
    return metaTitle;
  }

  public MetaType[] getMetaTypes() {
    return fieldTypes;
  }
}