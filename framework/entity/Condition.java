package framework.entity;

import java.util.StringTokenizer;

// 조건 내용을 추상화한 클래스
// 예1) name = "홍길동"
// 예2) age > 25
// 예3) color = "blue" & shape = "rectangle"

public class Condition {
  // 기본적인 조건인지, 조건들의 복합 조건인지 구별하는 필드
  // 예1, 예2의 경우 leafCondition은 true
  // 예3은 false
  public boolean leafCondition;
  public String fieldName;
  public Object value;
  public String operation;
  public Condition left;
  public Condition right;
  public boolean and;

  public Condition(String fName, String op, Object val) {
    // 예1의 경우 fieldName = "name"
    //            operation = "="
    //            value = "홍길동"
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

  // 어떤 엔티티가 이 조건에 만족하는지 검사하는 메소드
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