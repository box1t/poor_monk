This chapter discusses the use of the mmap() system call to create memory mappings. Memory mappings can be used for IPC, as well as a range of other purposes. We begin with an overview of some fundamental concepts before considering mmap() in depth.

## Overview
The mmap() system call creates a new memory mapping in the calling process’s virtual address space. A mapping can be of two types:

- **File mapping**: A file mapping maps a region of a file directly into the calling process’s virtual memory. Once a file is mapped, its contents can be accessed by operations on the bytes in the corresponding memory region. The pages of the mapping are (automatically) loaded from the file as required. This type of mapping is also known as a file-based mapping or memory-mapped file.
- **Anonymous mapping**: An anonymous mapping doesn’t have a corresponding file. Instead, the pages of the mapping are initialized to 0.

Another way of thinking of an anonymous mapping (and one is that is close to the truth) is that it is a mapping of a virtual file whose contents are always initialized with zeros.

The memory in one process’s mapping may be shared with mappings in other processes (i.e., the page-table entries of each process point to the same pages of RAM). This can occur in two ways:

- When two processes map the same region of a file, they share the same pages of physical memory.
- A child process created by fork() inherits copies of its parent’s mappings, and these mappings refer to the same pages of physical memory as the corresponding mappings in the parent.

When two or more processes share the same pages, each process can potentially see the changes to the page contents made by other processes, depending on whether the mapping is private or shared

- Private mapping (MAP_PRIVATE): Modifications to the contents of the mapping are not visible to other processes and, for a file mapping, are not carried through to the underlying file. Although the pages of a private mapping are initially shared in the circumstances described above, changes to the contents of the mapping are nevertheless private to each process. The kernel accomplishes this using the copy-on-write technique (Section 24.2.2). This means that whenever a process attempts to modify the contents of a page, the kernel first creates a new, separate copy of that page for the process (and adjusts the process’s page tables). For this reason, a MAP_PRIVATE mapping is sometimes referred to as a private, copy-on-write mapping.
- Shared mapping (MAP_SHARED): Modifications to the contents of the mapping are visible to other processes that share the same mapping and, for a file mapping, are carried through to the underlying file.

Shared file mapping: All processes mapping the same region of a file share the same physical pages of memory, which are initialized from a file region. Modifications to the contents of the mapping are carried through to the file. This type of mapping serves two purposes. First, it permits memory-mapped I/O. By this, we mean that a file is loaded into a region of the process’s virtual memory, and modifications to that memory are automatically written to the file. Thus, memory-mapped I/O provides an alternative to using read() and write() for performing file I/O. A second purpose of this type of mapping is to allow unrelated processes to share a region of memory in order to perform (fast) IPC in a manner similar to System V shared memory segments (Chapter 48).

![](Pasted%20image%2020231209061531.png)

## Creating a Mapping: mmap()

The mmap() system call creates a new mapping in the calling process’s virtual address space.

```c
#include <sys/mman.h>
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
Returns starting address of mapping on success, or MAP_FAILED on error
```

MAP_SHARED
Create a shared mapping. Modifications to the contents of the region are visible to other processes mapping the same region with the MAP_SHARED attribute and, in the case of a file mapping, are carried through to the underlying file. Updates to the file are not guaranteed to be immediate; see the discussion of the msync() system call in Section 49.5.

## Unmapping a Mapped Region: munmap()

The munmap() system call performs the converse of mmap(), removing a mapping from the calling process’s virtual address space.

```c
#include <sys/mman.h>
int munmap(void *addr, size_t length);
Returns 0 on success, or –1 on error
```

## File Mappings

To create a file mapping, we perform the following steps:
1. Obtain a descriptor for the file, typically via a call to open().
2. Pass that file descriptor as the fd argument in a call to mmap().

As a result of these steps, mmap() maps the contents of the open file into the address space of the calling process.

The offset argument specifies the starting byte of the region to be mapped from the file, and must be a multiple of the system page size. Specifying offset as 0 causes the file to be mapped from the beginning. The length argument specifies the number of bytes to be mapped. Together, the offset and length arguments determine which region of the file is to be mapped into memory, as shown in Figure 49-1.

![](Pasted%20image%2020231209070549.png)

Shared file mappings serve two purposes: memory-mapped I/O and IPC.

## Shared File Mappings

When multiple processes create shared mappings of the same file region, they all share the same physical pages of memory. In addition, modifications to the contents of the mapping are carried through to the file. In effect, the file is being treated as the paging store for this region of memory, as shown in Figure 49-2.

## Memory-mapped I/O

Memory-mapped I/O has two potential advantages:

- By replacing read() and write() system calls with memory accesses, it can simplify the logic of some applications.
- It can, in some circumstances, provide better performance than file I/O carried out using the conventional I/O system calls.

The reasons that memory-mapped I/O can provide performance benefits are as follows:

- A normal read() or write() involves two transfers: one between the file and the kernel buffer cache, and the other between the buffer cache and a user-space buffer. Using mmap() eliminates the second of these transfers.

- In addition to saving a transfer between kernel space and user space, mmap() can also improve performance by lowering memory requirements. When using read() or write(), the data is maintained in two buffers: one in user space and the other in kernel space.

## Synchronizing a Mapped Region: msync()

```c
#include <sys/mman.h>
int msync(void *addr, size_t length, int flags);
Returns 0 on success, or –1 on error
```

![](Pasted%20image%2020231209071422.png)

## Summary

The mmap() system call creates a new memory mapping in the calling process’s virtual address space. The munmap() system call performs the converse operation, removing a mapping from a process’s address space.

Mappings can be either private (MAP_PRIVATE) or shared (MAP_SHARED). This distinction determines the visibility of changes made to the shared memory, and, in the case of file mappings, determines whether the kernel propagates changes to the contents of the mapping to the underlying file. When a process maps a file with the MAP_PRIVATE flag, any changes it makes to the contents of the mapping are not visible to other processes and are not carried through to the mapped file. A MAP_SHARED file mapping is the converse—changes to the mapping are visible to other processes and are carried through to the mapped file.

Although the kernel automatically propagates changes to the contents of a MAP_SHARED mapping to the underlying file, it doesn’t provide any guarantees about when this is done. An application can use the msync() system call to explicitly control when the contents of a mapping are synchronized with the mapped file.

Memory mappings serve a variety of uses, including:

- allocating process-private memory (private anonymous mappings);
- initializing the contents of the text and initialized data segments of a process (private file mappings);
- sharing memory between processes related via fork() (shared anonymous mappings); and
- performing memory-mapped I/O, optionally combined with memory sharing between unrelated processes (shared file mappings).

