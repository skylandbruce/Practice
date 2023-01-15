package framework.entity;

import java.util.StringTokenizer;

// ���� ������ �߻�ȭ�� Ŭ����
// ��1) name = "ȫ�浿"
// ��2) age > 25
// ��3) color = "blue" & shape = "rectangle"

public class Condition {
  // �⺻���� ��������, ���ǵ��� ���� �������� �����ϴ� �ʵ�
  // ��1, ��2�� ��� leafCondition�� true
  // ��3�� false
  public boolean leafCondition;
  public String fieldName;
  public Object value;
  public String operation;
  public Condition left;
  public Condition right;
  public boolean and;

  public Condition(String fName, String op, Object val) {
    // ��1�� ��� fieldName = "name"
    //            operation = "="
    //            value = "ȫ�浿"
    fieldName = fName;
    operation = op;
    value = val;
    leafCondition = true;
  }

  public Condition(Condition l, boolean and, Condition r) {
    left = l;
    right = r;
    this.and = and;
    leafCondition = false;
  }

  // � ��ƼƼ�� �� ���ǿ� �����ϴ��� �˻��ϴ� �޼ҵ�
  public boolean satisfy(Entity entity) {
    if (leafCondition) {
      Object entityValue = entity.getValueTable().get(fieldName);
      if (operation.equals("=")) {
        return value.equals(entityValue);
      }
      else if (operation.equals(">")) {
        if (value instanceof Comparable && entityValue instanceof Comparable)
          return (((Comparable)entityValue).compareTo(value) > 0);
      }
      else if (operation.equals(">=")) {
        if (value instanceof Comparable && entityValue instanceof Comparable)
          return (((Comparable)entityValue).compareTo(value) >= 0);
      }
      else if (operation.equals("<")) {
        if (value instanceof Comparable && entityValue instanceof Comparable)
          return (((Comparable)entityValue).compareTo(value) < 0);
      }
      else if (operation.equals("<=")) {
        if (value instanceof Comparable && entityValue instanceof Comparable)
          return (((Comparable)entityValue).compareTo(value) <= 0);
      }
      else if (operation.equals("<>")) {
        return !(value.equals(entityValue));
      }
      else if (operation.equals("like")) {
        if (value instanceof String && entityValue instanceof String) {
          StringTokenizer keyword = new StringTokenizer((String)value, "%");
          if (keyword.hasMoreTokens())
            return (((String)entityValue).indexOf(keyword.nextToken()) != -1);
          return true;
        }
      }
      return false;
    }
    else {
      if (and)
        return (left.satisfy(entity)) & (right.satisfy(entity));
      else
        return (left.satisfy(entity)) | (right.satisfy(entity));
    }
  }
}