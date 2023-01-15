package framework.util;

import java.util.*;

public class TimedQueue {
  private LinkedList queue;
  private HashMap timeMap;
  
  public TimedQueue() {
    queue = new LinkedList();
    timeMap = new HashMap();
  }
  
  public synchronized void insert(Object o) {
    queue.add(o);
    timeMap.put(o, new Long(System.currentTimeMillis()));
  }
  
  public synchronized Object remove() {
    if (queue.size() > 0) {
      Object o = queue.remove(0);
      timeMap.remove(o);
      return o;
    }
    return null;
  }
  
  public synchronized long headTime() {
    Object o = queue.get(0);
    if (o != null) {
      Long time = (Long)timeMap.get(o);
      if (time != null)
        return time.longValue();
    }
    return -1;
  }
  
  public synchronized int size() {
    return queue.size();
  }
}