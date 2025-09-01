![](Pasted%20image%2020231208235419.png)

- **Data-transfer facilities**: The key factor distinguishing these facilities is the notion of writing and reading. In order to communicate, one process writes data to the IPC facility, and another process reads the data. **These facilities require two data transfers between user memory and kernel memory**: one transfer from user memory to kernel memory during writing, and another transfer from kernel memory to user memory during reading. 
- **Shared memory**: Shared memory allows processes to exchange information by placing it in a region of memory that is shared between the processes.  A process can make data available to other processes by placing it in the shared memory region. Because communication doesn’t require system calls or data transfer between user memory and kernel memory, shared memory can provide very fast communication.

***Data transfer:***
- **Byte stream**: The data exchanged via pipes, FIFOs, and datagram sockets is an undelimited byte stream. Each read operation may read an arbitrary number of bytes from the IPC facility, regardless of the size of blocks written by the writer. This model mirrors the traditional UNIX “file as a sequence of bytes” model.
- **Message**: The data exchanged via System V message queues, POSIX message queues, and datagram sockets takes the form of delimited messages. Each read operation reads a whole message, as written by the writer process. It is not possible to read part of a message, leaving the remainder on the IPC facility; nor is it possible to read multiple messages in a single read operation.


***Shared memory:***

- Although shared memory provides fast communication, this speed advantage is offset by the need to synchronize operations on the shared memory. For example, one process should not attempt to access a data structure in the shared memory while another process is updating it. A **semaphore is the usual synchronization method used with shared memory**.
- Data placed in shared memory is visible to all of the processes that share that memory. (This contrasts with the destructive read semantics described above for data-transfer facilities.)

## Synchronization Facilities

- **Semaphores**: A semaphore is a kernel-maintained integer whose value is never permitted to fall below 0. A process can decrease or increase the value of a semaphore. If an attempt is made to decrease the value of the semaphore below 0, then the kernel blocks the operation until the semaphore’s value increases to a level that permits the operation to be performed.  
  
  
  The meaning of a semaphore is determined by the application. A process decrements a semaphore (from, say, 1 to 0) in order to reserve exclusive access to some shared resource, and after completing work on the resource, increments the semaphore so that the shared resource is released for use by some other process. 
  
- **File locks**: File locks are a synchronization method explicitly designed to coordinate the actions of multiple processes operating on the same file. They can also be used to coordinate access to other shared resources. 
  
  ***File locks come in two flavors: read (shared) locks and write (exclusive) locks***. Any number of processes can hold a read lock on the same file (or region of a file). However, when one process holds a write lock on a file (or file region), other processes are prevented from holding either read or write locks on that file (or file region). 
  
  Linux provides file-locking facilities via the flock() and fcntl() system calls. The flock() system call provides a simple locking mechanism, allowing processes to place a shared or an exclusive lock on an entire file. Because of its limited functionality, flock() locking facility is rarely used nowadays. The fcntl() system call provides record locking, allowing processes to place multiple read and write locks on different regions of the same file.

- **Mutexes and condition variables**.


![](Pasted%20image%2020231209001744.png)

- **Some data-transfer facilities transfer data as a byte stream** (pipes, FIFOs, and stream sockets); others are message-oriented (message queues and datagram sockets). Which approach is preferable depends on the application. (An application can also impose a message-oriented model on a byte-stream facility, by using delimiter characters, fixed-length messages, or message headers that encode the length of the total message; see Section 44.8.)
- Pipes, FIFOs, and sockets are implemented using file descriptors
- POSIX message queues provide a notification facility that can send a signal to a process, or instantiate a new thread, when a message arrives on a previously empty queue.
- UNIX domain sockets provide a feature that allows a file descriptor to be passed from one process to another. This allows one process to open a file and make it available to another process that otherwise might not be able to access the file.
- UDP (Internet domain datagram) sockets allow a sender to broadcast or multicast a message to multiple recipients. 

