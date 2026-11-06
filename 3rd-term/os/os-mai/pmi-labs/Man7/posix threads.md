pthread = posix thread

Unix process consists of:
- thread
- address space
- file descriptors
- other data

You can have many threads sharing address space, but doing different things.
On a multiprocessor - sumiltaneously.

- **Asynchronous operations** - when they can be proceed independently of each other

The primary Pthreads synchronization object is **mutex**.
Pthreads provide **conditional variables**, which may be signaled or broadcast to indicate changes in shared data state.

Concurrency describes the behavior of threads or processes on a uniprocessor system.
Concurrent operations may be arbitrarily interleaved so they make progress independently, but concurrency does not imply that operations proceed sumiltaneosly.

Parallelism describes concurrent sequences that proceed sumiltaneously.

Thread-safe means that code can be called from multiple threads without destructive results.
It does not require that the code run efficiently in multiple threads, only that it can operate safely.

Invariants are relationships between the data inside the package.
When a program encounters a broken invariant (which are mostly problems with pointers on invalid data element memory space), the result will be incorrect.

Synchronisation protects your program from broken invariants.
If code locks mutex whenever it must (temporarily) break invariant, then other threads (and mutexes too) will be delayed untill the mutex is unlocked.


# Mutexes

Most threated programs need to share some data between threads.
There may be trouble if two threads try to access shared data at the same time, because one thread may be in the midst of modifying some data invariant while another acts on the data as if were consistent.

The most common way to sync between threads is to ensure that all memory accesses to the same (or related) data are "mutually exclusive".

Only one thread is allowed to write at a time-others must wait for their turn.

Mutex = mutual exclusion.

It is easier to use mutexes correctly than it is to use other sync models such as semaphore.

Sync is not only important while modifying data.
We also need sync when a thread needs to read data that was written by another thread, if the order in which data was written matters.

# Cond vars

Cond vars are for signalling, not for mutual exclusion.

A cond var wait always returns with the mutex locked.

