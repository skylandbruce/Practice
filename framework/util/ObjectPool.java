package framework.util;

import java.util.*;

public abstract class ObjectPool implements Runnable {
  private long expirationTime;
  private long sleepTime;
  private int maxUsing;
  private int objectCount;
  private int minPool;
	private TimedQueue pool;
  private Thread cleaner;

  protected ObjectPool(long expirationTime, long sleepTime, int maxUsing, int minPool) {
    this.expirationTime = expirationTime;
    this.sleepTime = sleepTime;
    this.maxUsing = maxUsing;
    this.minPool = minPool;

		pool = new TimedQueue();
    cleaner = new Thread(this);
    cleaner.start();
  }
  
  protected synchronized void checkIn(Object o)	{
    if (o != null) {
			pool.insert(o);
    }
  }

  protected synchronized Object checkOut() throws Exception {
    Object o;
    
    while (true) {
      if (pool.size() <= 0)
        break;
      o = pool.remove();
      if (isValid(o))
        return o;
    }
    while (objectCount >= maxUsing)
      wait();
    o = create();
    objectCount++;
    return o;
  }
  
  private synchronized void cleanUp() {
    Object o;
    long current = System.currentTimeMillis();

    while (pool.size() > minPool) {
      if ((current - pool.headTime()) < expirationTime)
        break;
      o = pool.remove();
      expire(o);
      objectCount--;
      notifyAll();
    }
  }

  public void run() {
    while (true) {
      try {
        Thread.sleep(sleepTime);
      }
      catch(InterruptedException e) {
      }
      cleanUp();
    }
  }
  
  protected abstract Object create() throws Exception;
  protected abstract void expire(Object o);
  protected abstract boolean isValid(Object o);
}
