Pipes are the oldest method of IPC on the UNIX system, having appeared in Third Edition UNIX in the early 1970s.
Pipes can be used to pass data between related processes

FIFOs are a variation on the pipe concept. The important difference is that FIFOs can be used for communication between any processes.

![](Pasted%20image%2020231209015901.png)

One point to note in Figure 44-1 is that the two processes are connected to the pipe so that the writing process (ls) has its standard output (file descriptor 1) joined to the write end of the pipe, while the reading process (wc) has its standard input (file descriptor 0) joined to the read end of the pipe. In effect, these two processes are unaware of the existence of the pipe; they just read from and write to the standard file descriptors.

## A pipe is a byte stream
When we say that a pipe is a byte stream, we mean that there is no concept of messages or message boundaries when using a pipe.

The process reading from a pipe can read blocks of data of any size, regardless of the size of blocks written by the writing process. Furthermore, the data passes through the pipe sequentially— bytes are read from a pipe in exactly the order they were written. It is not possible to randomly access the data in a pipe using lseek().

it may be preferable to use alternative IPC mechanisms, such as message queues and datagram sockets, which we discuss in later chapters.

## Reading from a pipe
Attempts to read from a pipe that is currently empty block until at least one byte has been written to the pipe. If the write end of a pipe is closed, then a process reading from the pipe will see end-of-file (i.e., read() returns 0) once it has read all remaining data in the pipe.

## Pipes are unidirectional

Data can travel only in one direction through a pipe. One end of the pipe is used for writing, and the other end is used for reading.

## Pipes have a limited capacity

A pipe is simply a buffer maintained in kernel memory. This buffer has a maximum capacity. Once a pipe is full, further writes to the pipe block until the reader removes some data from the pipe

In general, an application never needs to know the exact capacity of a pipe.

In theory, there is no reason why a pipe couldn’t operate with smaller capacities, even with a single-byte buffer. The reason for employing large buffer sizes is efficiency: each time a writer fills the pipe, the kernel must perform a context switch to allow the reader to be scheduled so that it can empty some data from the pipe. Employing a larger buffer size means that fewer context switches are required.

## Creating and Using Pipes

The pipe() system call creates a new pipe.
```c
#include <unistd.h>
int pipe(int filedes[2]);
Returns 0 on success, or –1 on error
```

A successful call to pipe() returns two open file descriptors in the array filedes: one for the read end of the pipe (filedes[0]) and one for the write end ( filedes[1]).

As with any file descriptor, we can use the read() and write() system calls to perform I/O on the pipe. Once written to the write end of a pipe, data is immediately available to be read from the read end.

We can also use the stdio functions (printf(), scanf(), and so on) with pipes by first using fdopen() to obtain a file stream corresponding to one of the descriptors in filedes (Section 13.7). However, when doing this, we must be aware of the stdio buffering issues described in Section 44.6.

A pipe has few uses within a single process (we consider one in Section 63.5.2). Normally, we use a pipe to allow communication between two processes. To connect two processes using a pipe, we follow the pipe() call with a call to fork(). During a fork(), the child process inherits copies of its parent’s file descriptors (Section 24.2.1), bringing about the situation shown on the left side of Figure 44-3.

![](Pasted%20image%2020231209020417.png)

Therefore, immediately after the fork(), one process closes its descriptor for the write end of the pipe, and the other closes its descriptor for the read end.


## Closing unused pipe file descriptors

Closing unused pipe file descriptors is more than a matter of ensuring that a process doesn’t exhaust its limited set of file descriptors—it is essential to the correct use of pipes. We now consider why the unused file descriptors for both the read and write ends of the pipe must be closed.

The process reading from the pipe closes its write descriptor for the pipe, so that, when the other process completes its output and closes its write descriptor, the reader sees end-of-file (once it has read any outstanding data in the pipe).

