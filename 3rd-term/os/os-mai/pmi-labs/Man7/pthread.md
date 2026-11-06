posix threads

Like processes, threads are a mechanism that permits an application to perform multiple tasks concurrently
A single process can contain multiple threads

All of these threads are independently executing the same program, and they all share the same global memory, including the initialized data, uninitialized data, and heap segments
The threads in a process can execute concurrently. On a multiprocessor system, multiple threads can execute parallel.

![](Pasted%20image%2020231209102224.png)

All Pthreads functions return 0 on success or a positive value on failure.

When a program is started, the resulting process consists of a single thread, called the initial or main thread. In this section, we look at how to create additional threads. The pthread_create() function creates a new thread.

The return value of start is likewise of type void * , and it can be employed in the same way as the arg argument. We’ll see how this value is used when we describe the pthread_join() function below


The thread argument points to a buffer of type pthread_t into which the unique identifier for this thread is copied before pthread_create() returns. This identifier can be used in later Pthreads calls to refer to the thread.

Thread Termination

The execution of a thread terminates in one of the following ways:

- The thread’s start function performs a return specifying a return value for the thread.
- The thread calls pthread_exit() (described below).
- The thread is canceled using pthread_cancel() (described in Section 32.1).
- Any of the threads calls exit(), or the main thread performs a return (in the main() function), which causes all threads in the process to terminate immediately.

void pthread_exit(void * retval);

Calling pthread_exit() is equivalent to performing a return in the thread’s start function, with the difference that pthread_exit() can be called from any function that has been called by the thread’s start function.

If the main thread calls pthread_exit() instead of calling exit() or performing a return, then the other threads continue to execute

Joining with a Terminated Thread

The limitation that pthread_join() can join only with a specific thread ID is intentional. The idea is that a program should join only with the threads that it “knows” about. The problem with a “join with any thread” operation stems from the fact that there is no hierarchy of threads, so such an operation could indeed join with any thread, including one that was privately created by a library function.

Threads Versus Processes

- Sharing data between threads is easy. By contrast, sharing data between processes requires more work (e.g., creating a shared memory segment or using a pipe).
- Thread creation is faster than process creation; context-switch time may be lower for threads than for processes.

Using threads can have some disadvantages compared to using processes:

- When programming with threads, we need to ensure that the functions we call are thread-safe or are called in a thread-safe manner. (We describe the concept of thread safety in Section 31.1.) Multiprocess applications don’t need to be concerned with this.
- A bug in one thread (e.g., modifying memory via an incorrect pointer) can damage all of the threads in the process, since they share the same address space and other attributes. By contrast, processes are more isolated from one another.
- Each thread is competing for use of the finite virtual address space of the host process. In particular, each thread’s stack and thread-specific data (or threadlocal storage) consumes a part of the process virtual address space, which is consequently unavailable for other threads. Although the available virtual address space is large (e.g., typically 3 GB on x86-32), this factor may be a significant limitation for processes employing large numbers of threads or threads that require large amounts of memory. By contrast, separate processes can each employ the full range of available virtual memory (subject to the limitations of RAM and swap space).


The following are some other points that may influence our choice of threads versus processes:
- Dealing with signals in a multithreaded application requires careful design. (As a general principle, it is usually desirable to avoid the use of signals in multithreaded programs.) We say more about threads and signals in Section 33.2.
- In a multithreaded application, all threads must be running the same program (although perhaps in different functions). In a multiprocess application, different processes can run different programs.
- Aside from data, threads also share certain other information (e.g., file descriptors, signal dispositions, current working directory, and user and group IDs). This may be an advantage or a disadvantage, depending on the application.


Summary
In a multithreaded process, multiple threads are concurrently executing the same program. All of the threads share the same global and heap variables, but each thread has a private stack for local variables. The threads in a process also share a number of other attributes, including process ID, open file descriptors, signal dispositions, current working directory, and resource limits.

The key difference between threads and processes is the easier sharing of information that threads provide, and this is the main reason that some application designs map better onto a multithread design than onto a multiprocess design. Threads can also provide better performance for some operations (e.g., thread creation is faster than process creation), but this factor is usually secondary in influencing the choice of threads versus processes.

Threads are created using pthread_create(). Each thread can then independently terminate using pthread_exit(). (If any thread calls exit(), then all threads immediately terminate.) Unless a thread has been marked as detached (e.g., via a call to pthread_detach()), it must be joined by another thread using pthread_join(), which returns the termination status of the joined thread.


