## Redis Distributed Lock Example

### Example 1: Manual Implementation (Basic)

```python
  import redis
  import time
  import uuid

  class RedisDistributedLock:
      def __init__(self, redis_client, lock_name, timeout=10):
          self.redis = redis_client
          self.lock_name = f"lock:{lock_name}"
          self.timeout = timeout
          self.identifier = str(uuid.uuid4())  # Unique ID for this lock holder

      def acquire(self, blocking=True, blocking_timeout=10):
          """Acquire the lock"""
          end_time = time.time() + blocking_timeout

          while True:
              # Set lock with NX (only if not exists) and EX (expiration)
              if self.redis.set(self.lock_name, self.identifier, nx=True, ex=self.timeout):
                  return True

              if not blocking:
                  return False

              if time.time() > end_time:
                  return False

              time.sleep(0.001)  # Small delay before retry

      def release(self):
          """Release the lock (only if we own it)"""
          # Lua script ensures atomic check-and-delete
          lua_script = """
          if redis.call("get", KEYS[1]) == ARGV[1] then
              return redis.call("del", KEYS[1])
          else
              return 0
          end
          """
          self.redis.eval(lua_script, 1, self.lock_name, self.identifier)

      def __enter__(self):
          self.acquire()
          return self

      def __exit__(self, exc_type, exc_val, exc_tb):
          self.release()

  # Usage
  r = redis.Redis(host='localhost', port=6379, decode_responses=True)

  # Method 1: Context manager
  with RedisDistributedLock(r, "my_resource", timeout=30):
      print("Critical section - only one process can be here")
      # Do your work here
      time.sleep(2)

  # Method 2: Manual acquire/release
  lock = RedisDistributedLock(r, "my_resource")
  if lock.acquire(blocking=True, blocking_timeout=5):
      try:
          print("Lock acquired, doing work...")
          time.sleep(2)
      finally:
          lock.release()
  else:
      print("Could not acquire lock")
```

### Example 2: Using redis-py-lock Library (Recommended)

```python
  import redis
  from redis.lock import Lock

  r = redis.Redis(host='localhost', port=6379, decode_responses=True)

  # Simple usage
  lock = Lock(r, "my_lock", timeout=10)

  if lock.acquire(blocking=True, blocking_timeout=5):
      try:
          print("Doing critical work...")
          # Your code here
      finally:
          lock.release()

  # Or with context manager
  with Lock(r, "my_lock", timeout=10):
      print("Critical section protected by lock")

  Example 3: Using Redlock Algorithm (More Robust)

  # Install: pip install python-redis-lock
  import redis_lock
  import redis

  r = redis.StrictRedis(host='localhost', port=6379)

  # Redlock is more reliable for distributed systems
  with redis_lock.Lock(r, "my_resource", expire=60, auto_renewal=True):
      print("Doing critical work...")
      time.sleep(5)  # Lock auto-renews if needed
```
### Key Considerations
  1. Timeout: Always set an expiration to prevent deadlocks if a process crashes
  2. Unique Identifier: Use unique IDs to ensure only the lock owner can release it
  3. Atomic Operations: Use Lua scripts for check-and-set operations
  4. Auto-renewal: For long operations, consider auto-renewing the lock
  5. Retry Logic: Implement exponential backoff for retries in high-contention scenarios

###  Common Pitfalls
  - No expiration: Lock never released if process crashes
  - Releasing others' locks: Always verify ownership before releasing
  - Clock skew: In multi-server setups, use Redlock algorithm
  - Network partitions: Consider using Redlock with multiple Redis instances
