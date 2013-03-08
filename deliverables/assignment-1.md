### 5.1.1 Thread Questions
  1. What happens to a thread when it exits (i.e., calls thread_exit() )? What
     about when it sleeps?
     * When a thread exits, its address space gets destroyed and it removes
       itself from the global thread count. It doesn't actually get destroyed
       itself until thread_destroy is called from exorcise.
     * When a thread sleeps, it assigns itself a "sleep address" and stops being
       processed, freeing the CPU to handle another process. When it wakes up,
       it must be awoken from the same sleep address.
  2. What function(s) handle(s) a context switch?
     * `mi_switch` and `md_switch`
  3. How many thread states are there? What are they?
     * 4; `S_RUN`, `S_READY`, `S_SLEEP`, `S_ZOMB`
  4. What does it mean to turn interrupts off? How is this accomplished? Why is
     it important to turn off interrupts in the thread subsystem code?
     * Turning interrupts off means the CPU can't be retasked by an interrupt
       sent from any one of many different sources (mouse click, etc.).
       Interrupts are turned off using the splhigh function.
       It's important to turn off interrupts in the thread subsystem code so
       that we can accomplish certain tasks atomically, such as printing the
       entire run queue.
  5. What happens when a thread wakes up another thread? How does a sleeping
     thread get to run again?
     * For a thread to wake up another thread, it needs to know the sleep
       address of the sleeping thread.
       A sleeping thread will only run again if thread_wakeup is called using
       the correct sleep address.

### 5.1.2 Scheduler Questions
  6. What function is responsible for choosing the next thread to run?
     * scheduler
  7. How does that function pick the next thread?
     * It chooses the next thread in the run queue.
  8. What role does the hardware timer play in scheduling? What hardware
     independent function is called on a timer interrupt?
     * The hardware timer influences `rtclock`, a generic clock interface.
       `hardclock` is called from the timer interrupt a set number of times per
       second.

### 5.1.3 Synchronization Questions
  9. Describe how thread_sleep() and thread_wakeup() are used to implement
     semaphores. What is the purpose of the argument passed to thread_sleep() ?
     * `thread_sleep` and `thread_wakeup` are used to implement semaphores by
       treating a sleeping thread as a lock and a `thread_wakeup` call as a
       release.
       The argument passed to `thread_sleep` allows `thread_wakeup` to wake
       threads selectively by sleep address -- it is used as a way to identify
       sleeping threads.
  10. Why does the lock API in OS161 provide lock_do_i_hold(), but not
      lock_get_holder() ?

### Identify Deadlocks
* Here are code samples for two threads that use binary semaphores. Give a
  sequence of execution and context switches in which these two threads can
  deadlock. Propose a change to one or both of them that makes deadlock
  impossible. What general principle do the original threads violate that
  causes them to deadlock?

      semaphore *mutex, *data;

      void me() {
        P(mutex);
        /* do something */
        P(data);
        /* do something else */
        V(mutex);
        /* clean up */
        V(data);
      }

      void you() {
        P(data)
        P(mutex);
        /* do something */
        V(data);
        V(mutex);
      }

  * The function `me` starts running and when it calls `P(mutex)`, it decrements
    the mutex counter, which sets it below 0 so the thread sleeps.  Then we
    switch to `you` and it sees that the counter is below 0 so it attempts to
    wake the other process which calls `P(data)` which sets it below 0 again so
    it sleeps and `you` is waiting on `me` which is sleeping, so they'll never
    continue.

* Here are two more threads. Can they deadlock? If so, give a concurrent
  execution in which they do and propose a change to one or both that makes
  them deadlock free.

      lock *file1, *file2, *mutex;

      void laurel() {
        lock_acquire(mutex);
        /* do something */
        lock_acquire(file1);
        /* write to file 1 */
        lock_acquire(file2);
        /* write to file 2 */
        lock_release(file1);
        lock_release(mutex);
        /* do something */

        lock_acquire(file1);
        /* read from file 1 */
        /* write to file 2 */

        lock_release(file2);
        lock_release(file1);
      }

      void hardy() {
        /* do stuff */
        lock_acquire(file1);
        /* read from file 1 */
        lock_acquire(file2);
        /* write to file 2 */
        lock_release(file1);
        lock_release(file2);
        lock_acquire(mutex);
        /* do something */
        lock_acquire(file1);
        /* write to file 1 */
        lock_release(file1);
        lock_release(mutex);
      }

  * `laurel` runs and gets the lock on `mutex`, `file1`, and `file2` and then
    releases `file1` and `mutex` and then we switch to `hardy` and it locks
    `file1` and then tries to get `file2` but it has to wait because `laurel`
    still has the lock on it. So it switches back to `laurel` which attempts to
    lock `file1` but can't because `hardy` has the lock on it still so `laurel`
    is waiting for `hardy`, but `hardy` is waiting on `laurel` so it deadlocks.

### Cat/mouse problem

To avoid starvation in our solution, we randomize the bowls that cats eat from
in order to increase the chances of a hungry cat choosing an empty bowl. When
all bowls are free, mice will attempt to eat from a random bowl.

When a mouse eats, it obtains locks on both bowls so that it will not be seen by
a cat.
