Indeed, Dijkstra and colleagues invented the semaphore as a single primitive for all things related to synchronization; as you will see, one can use semaphores as both locks and condition variables

> How can we use semaphores instead of locks and condition variables? What is the definition of a semaphore? What is a binary semaphore? Is it straightforward to build a semaphore out of locks and condition variables? To build locks and condition variables out of semaphores?

A semaphore is an object with an integer value that we can manipulate with two routines; in the POSIX standard, these routines are sem wait() and sem post()1 .

Because the initial value of the semaphore determines its behavior, before calling any other routine to interact with the semaphore, we must first initialize it to some value

```c++
#include <semaphore.h> 
sem_t s; 
sem_init(&s, 0, 1);

```

The second argument to sem init() will be set to 0 in all of the examples we’ll see; this indicates that the semaphore is shared between threads in the same process. See the man page for details on other usages of semaphores (namely, how they can be used to synchronize access across different processes), which require a different value for that second argument.

We’ve now seen two examples of initializing a semaphore. In the first case, we set the value to 1 to use the semaphore as a lock; in the second, to 0, to use the semaphore for ordering.

sem init, sem post, sem wait

Unlike the IPC mechanisms described in previous chapters, System V semaphores are not used to transfer data between processes. Instead, they allow processes to synchronize their actions.

One common use of a semaphore is to synchronize access to a block of shared memory, in order to prevent one process from accessing the shared memory at the same time as another process is updating it.

A semaphore is a kernel-maintained integer whose value is restricted to being greater than or equal to 0. Various operations (i.e., system calls) can be performed on a semaphore, including the following:

- z setting the semaphore to an absolute value;
- adding a number to the current value of the semaphore;
- subtracting a number from the current value of the semaphore; and
- waiting for the semaphore value to be equal to 0.

***
This chapter describes POSIX semaphores, which allow processes and threads to synchronize access to shared resources.

a POSIX semaphore is an integer whose value is not permitted to fall below 0

## Named Semaphores
To work with a named semaphore, we employ the following functions

- The sem_open() function opens or creates a semaphore, initializes the semaphore if it is created by the call, and returns a handle for use in later calls.
- The sem_post(sem) and sem_wait(sem) functions respectively increment and decrement a semaphore’s value.
- The sem_getvalue() function retrieves a semaphore’s current value.
- The sem_close() function removes the calling process’s association with a semaphore that it previously opened.
- The sem_unlink() function removes a semaphore name and marks the semaphore for deletion when all processes have closed it

```c
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
sem_t *sem_open(const char *name, int oflag, ...
				/* mode_t mode, unsigned int value */ );
				Returns pointer to semaphore on success, or SEM_FAILED on error
```

The oflag argument is a bit mask that determines whether we are opening an existing semaphore or creating and opening a new semaphore. If oflag is 0, we are accessing an existing semaphore. If O_CREAT is specified in oflag, then a new semaphore is created if one with the given name doesn’t already exist. If oflag specifies both O_CREAT and O_EXCL, and a semaphore with the given name already exists, then sem_open() fails

If sem_open() is being used to open an existing semaphore, the call requires only two arguments. However, if O_CREAT is specified in flags, then two further arguments are required: mode and value. (If the semaphore specified by name already exists, then these two arguments are ignored.)

Regardless of whether we are creating a new semaphore or opening an existing semaphore, sem_open() returns a pointer to a sem_t value, and we employ this pointer in subsequent calls to functions that operate on the semaphore. On error, sem_open() returns the value SEM_FAILED.

When a process opens a named semaphore, the system records the association between the process and the semaphore. The sem_close() function terminates this association (i.e., closes the semaphore), releases any resources that the system has associated with the semaphore for this process, and decreases the count of processes referencing the semaphore.

```c
int sem_close(sem_t *sem);
Returns 0 on success, or –1 on error
```

***
To use a POSIX shared memory object, we perform two steps:

Use the shm_open() function to open an object with a specified name. (We described the rules governing the naming of POSIX shared memory objects in Section 51.1.) The shm_open() function is analogous to the open() system call. It either creates a new shared memory object or opens an existing object. As its function result, shm_open() returns a file descriptor referring to the object

Pass the file descriptor obtained in the previous step in a call to mmap() that specifies MAP_SHARED in the flags argument. This maps the shared memory object into the process’s virtual address space. As with other uses of mmap(), once we have mapped the object, we can close the file descriptor without affecting the mapping. However, we may need to keep the file descriptor open for subsequent use in calls to fstat() and ftruncate() (see Section 54.2).


![](Pasted%20image%2020231209073614.png)

```c
/* Create shared memory object and set its size */ 
fd = shm_open(argv[optind], flags, perms); 
if (fd == -1) 
	errExit("shm_open"); 
if (ftruncate(fd, size) == -1) 
	errExit("ftruncate"); 

/* Map shared memory object */ 

addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
if (addr == MAP_FAILED) 
	errExit("mmap"); 
exit(EXIT_SUCCESS);
```

The program in Listing 54-3 displays the string in the existing shared memory object named in its command-line argument on standard output. After calling shm_open(), the program uses fstat() to determine the size of the shared memory and uses that size in the call to mmap() that maps the object and in the write() call that prints the string


- They provide fast IPC, and applications typically must use a semaphore (or other synchronization primitive) to synchronize access to the shared region
- Once the shared memory region has been mapped into the process’s virtual address space, it looks just like any other part of the process’s memory space.
- The system places the shared memory regions within the process virtual address space in a similar manner. We outlined this placement while describing System V shared memory in Section 48.5. The Linux-specific /proc/PID/maps file lists information about all types of shared memory regions.
- Assuming that we don’t attempt to map a shared memory region at a fixed address, we should ensure that all references to locations in the region are calculated as offsets (rather than pointers), since the region may be located at different virtual addresses within different processes (Section 48.6)
- The functions described in Chapter 50 that operate on regions of virtual memory can be applied to shared memory regions created using any of these techniques.

There are also a few notable differences between the techniques for shared memory:
- The fact that the contents of a shared file mapping are synchronized with the underlying mapped file means that the data stored in a shared memory region can persist across system restarts.
> System V uses its own scheme of keys and identifiers, which doesn’t fit with the standard UNIX I/O model and requires separate system calls

A POSIX shared memory object is used to share a region of memory between unrelated processes without creating an underlying disk file.

