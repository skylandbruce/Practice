package framework.entity;

public class MetaType {
  String columnInDB;
  int typeInDB;
  String columnInJava;
  int typeInJava;
  
  public MetaType(String column, int type) {
    this.columnInDB = this.columnInJava = column;
    this.typeInDB = this.typeInJava = type;
  }
  
  public MetaType(String columnInDB, int typeInDB, String columnInJava, int typeInJava) {
    this.columnInDB = columnInDB;
    this.typeInDB = typeInDB;
    this.columnInJava = columnInJava;
    this.typeInJava = typeInJava;
  }
}