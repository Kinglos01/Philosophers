1.) Windows and Linux implement multiple locking mechanisms because different situations require different ways to manage access to shared resources. 
Spinlocksare used when the wait time is expected to be very short and sleeping isn’t allowed, like in low-level kernel code, 
since they avoid the overhead of context switching by keeping the thread active. Mutex locks are used when threads can sleep and the wait time might be
longer—they’re more CPU-efficient for general use. Semaphores help when multiple threads need access to a limited number of resources, allowing more flexible 
control than just locked/unlocked states. Condition variables are used when a thread should wait for a specific condition to be true, letting it sleep efficiently
until another thread signals a change. Each mechanism is chosen based on performance, fairness, and whether threads are allowed to block or not.

2.)To use a mutex lock instead of a binary semaphore in the producer and consumer processes, we would need to remove the semaphores “semEmpty and semFull” 
and replace them with condition variables along with the mutex. The mutex "mutexBuffer" would still protect access to the shared buffer, 
but since mutexes don't handle waiting based on buffer state like full or empty, we’d need condition variables to make threads wait when the buffer is full 
“for producers” or empty “for consumers”. So, inside the producer, we’d add a while (count == 10) loop with pthread_cond_wait() to pause when the buffer is full,
and inside the consumer, we’d do while (count == 0) with pthread_cond_wait() to wait when it's empty. After producing or consuming, we’d use pthread_cond_signal()
to wake up the other side. This way, the mutex ensures safe access, and the condition variables manage the proper synchronization.

3.)Deadlock is possible in the dining-philosophers problem when each philosopher picks up one fork; say, the one on their left and then waits for the
other fork on their right, which is already taken by the next philosopher. If all five philosophers do this at the same time, they’ll all be stuck waiting
forever for the fork that never becomes available this is a classic circular wait, one of the conditions for deadlock. In the code, deadlock could happen if
all philosophers become hungry and call take_fork() at the same time, setting their state to HUNGRY and blocking at S[phnum].wait(lock) because neither of 
their neighbors is releasing a fork (they’re also waiting). Since no one can eat and therefore no one can put down a fork, the system gets stuck.

