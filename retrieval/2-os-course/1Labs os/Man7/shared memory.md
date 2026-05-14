Shared memory allows two or more processes to share the same region (usually referred to as a segment) of physical memory.

Since a shared memory segment becomes part of a process’s user-space memory, no kernel intervention is required for IPC.

All that is required is that one process copies data into the shared memory; that data is immediately available to all other processes sharing the same segment.

This provides fast IPC by comparison with techniques such as pipes or message queues, where the sending process copies data from a buffer in user space into kernel memory and the receiving process copies in the reverse direction.

In mmap() terminology, a memory region is mapped at an address

## Overview

In order to use a shared memory segment, we typically perform the following steps:

- Call **shmget()** to create a new shared memory segment or obtain the identifier of an existing segment (i.e., one created by another process). This call returns a shared memory identifier for use in later calls.
- Use **shmat()** to attach the shared memory segment; that is, make the segment part of the virtual memory of the calling process.
- At this point, the shared memory segment can be treated just like any other memory available to the program. In order to refer to the shared memory, the program uses the addr value returned by the shmat() call, which is a pointer to the start of the shared memory segment in the process’s virtual address space.
- Call **shmdt()** to detach the shared memory segment. After this call, the process can no longer refer to the shared memory. This step is optional, and happens automatically on process termination.
- Call **shmctl()** to delete the shared memory segment. The segment will be destroyed only after all currently attached processes have detached it. Only one process needs to perform this step.

## Creating or Opening a Shared Memory Segment

The shmget() system call creates a new shared memory segment or obtains the identifier of an existing segment. The contents of a newly created shared memory segment are initialized to 0.

```c
#include <sys/types.h>
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);
Returns shared memory segment identifier on success, or –1 on error
```
