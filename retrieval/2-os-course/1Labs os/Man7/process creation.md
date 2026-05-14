fork(), exit(), wait(), and execve().

The fork() system call allows one process, the parent, to create a new process, the child. This is done by making the new child process an (almost) exact duplicate of the parent: the child obtains copies of the parent’s stack, data, heap, and text segments (Section 6.3). The term fork derives from the fact that we can envisage the parent process as dividing to yield two copies of itself.

The exit(status) library function terminates a process, making all resources (memory, open file descriptors, and so on) used by the process available for subsequent reallocation by the kernel. The status argument is an integer that determines the termination status for the process. Using the wait() system call, the parent can retrieve this status.

The wait(&status) system call has two purposes. First, if a child of this process has not yet terminated by calling exit(), then wait() suspends execution of the process until one of its children has terminated. Second, the termination status of the child is returned in the status argument of wait().

The execve(pathname, argv, envp) system call loads a new program (pathname, with argument list argv, and environment list envp) into a process’s memory. The existing program text is discarded, and the stack, data, and heap segments are freshly created for the new program. This operation is often referred to as execing a new program. Later, we’ll see that several library functions are layered on top of execve(), each of which provides a useful variation in the programming interface. Where we don’t care about these interface variations, we follow the common convention of referring to these calls generically as exec(), but be aware that there is no system call or library function with this name.

![](Pasted%20image%2020231208222326.png)

In many applications, creating multiple processes can be a useful way of dividing up a task. For example, a network server process may listen for incoming client requests and create a new child process to handle each request; meanwhile, the server process continues to listen for further client connections. Dividing tasks up in this way often makes application design simpler. It also permits greater concurrency (i.e., more tasks or requests can be handled simultaneously). 

The fork() system call creates a new process, the child, which is an almost exact duplicate of the calling process, the parent.


The key point to understanding fork() is to realize that after it has completed its work, two processes exist, and, in each process, execution continues from the point where fork() returns.

For the parent, fork() returns the process ID of the newly created child. This is useful because the parent may create, and thus need to track, several children (via wait() or one of its relatives). For the child, fork() returns 0. If necessary, the child can obtain its own process ID using getpid(), and the process ID of its parent using getppid().

If a new process can’t be created, fork() returns –1. Possible reasons for failure are that the resource limit (RLIMIT_NPROC, described in Section 36.3) on the number of processes permitted to this (real) user ID has been exceeded or that the systemwide limit on the number of processes that can be created has been reached.

