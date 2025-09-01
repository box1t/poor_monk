Many system programs need to be able to allocate extra memory for dynamic data structures (e.g., linked lists and binary trees), whose size depends on information that is available only at run time. 

## On the heap

To allocate memory, C programs normally use the malloc family of functions, which we describe shortly. However, we begin with a description of brk() and sbrk(), upon which the malloc functions are based.

## Adjusting the Program Break: brk() and sbrk()
Resizing the heap (i.e., allocating or deallocating memory) is actually as simple as telling the kernel to adjust its idea of where the process’s program break is.

The call sbrk(0) returns the current setting of the program break without changing it. This can be useful if we want to track the size of the heap, perhaps in order to monitor the behavior of a memory allocation package.
## Allocating Memory on the Heap: malloc() and free()

In general, C programs use the malloc family of functions to allocate and deallocate memory on the heap. These functions offer several advantages over brk() and sbrk(). In particular, they:

- are standardized as part of the C language;
- are easier to use in threaded programs;
- provide a simple interface that allows memory to be allocated in small units; and
- allow us to arbitrarily deallocate blocks of memory, which are maintained on a free list and recycled in future calls to allocate memory.

```c
#include <stdlib.h>
void *malloc(size_t size);
Returns pointer to allocated memory on success, or NULL on error
```

Because malloc() returns void * , we can assign it to any type of C pointer

If memory could not be allocated (perhaps because we reached the limit to which the program break could be raised), then malloc() returns NULL and sets errno to indicate the error. Although the possibility of failure in allocating memory is small, all calls to malloc(), and the related functions that we describe later, should check for this error return.

The free() function deallocates the block of memory pointed to by its ptr argument, which should be an address previously returned by malloc() or one of the other heap memory allocation functions that we describe later in this chapter.

```c
void free(void *ptr);
```
In general, free() doesn’t lower the program break, but instead adds the block of memory to a list of free blocks that are recycled by future calls to malloc(). This is done for several reasons:

- The block of memory being freed is typically somewhere in the middle of the heap, rather than at the end, so that lowering the program break is not possible.
- It minimizes the number of sbrk() calls that the program must perform. (As noted in Section 3.1, system calls have a small but significant overhead.)
- In many cases, lowering the break would not help programs that allocate large amounts of memory, since they typically tend to hold on to allocated memory or repeatedly release and reallocate memory, rather than release it all and then continue to run for an extended period of time.

