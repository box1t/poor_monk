All system calls for performing I/O refer to open files using **a file descriptor**, a (usually small) nonnegative integer.

File descriptors are used to refer to all types of open files, including pipes, FIFOs, sockets, terminals, devices, and regular files. Each process has its own set of file descriptors.

![](Pasted%20image%2020231209011359.png)

When referring to these file descriptors in a program, we can use either the numbers (0, 1, or 2) or, preferably, the POSIX standard names defined in ***unistd.h***


The following are the four key system calls for performing file I/O:

- fd = open(pathname, flags, mode) opens the file identified by pathname, returning a file descriptor used to refer to the open file in subsequent calls. If the file doesn’t exist, open() may create it, depending on the settings of the flags bitmask argument. The flags argument also specifies whether the file is to be opened for reading, writing, or both. The mode argument specifies the permissions to be placed on the file if it is created by this call. If the open() call is not being used to create a file, this argument is ignored and can be omitted.
- numread = read(fd, buffer, count) reads at most count bytes from the open file referred to by fd and stores them in buffer. The read() call returns the number of bytes actually read. If no further bytes could be read (i.e., end-of-file was encountered), read() returns 0.
- numwritten = write(fd, buffer, count) writes up to count bytes from buffer to the open file referred to by fd. The write() call returns the number of bytes actually written, which may be less than count.
- status = close(fd) is called after all I/O has been completed, in order to release the file descriptor fd and its associated kernel resources.

![](Pasted%20image%2020231209024917.png)

## Opening a File: open()
The open() system call either opens an existing file or creates and opens a new file.

```c
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags, ... /* mode_t mode */);
Returns file descriptor on success, or –1 on error
```
- The file to be opened is identified by the pathname argument. If pathname is a symbolic link, it is dereferenced. On success, open() returns a file descriptor that is used to refer to the file in subsequent system calls. If an error occurs, open() returns –1 and errno is set accordingly.
- The flags argument is a bit mask that specifies the access mode for the file, using one of the constants shown in Table 4-2.

When open() is used to create a new file, the mode bit-mask argument specifies the permissions to be placed on the file.

## Reading from a File: read()

The read() system call reads data from the open file referred to by the descriptor fd
```c
#include <unistd.h>
ssize_t read(int fd, void *buffer, size_t count);
Returns number of bytes read, 0 on EOF, or –1 on error
```
The count argument specifies the maximum number of bytes to read. (The size_t data type is an unsigned integer type.) The buffer argument supplies the address of the memory buffer into which the input data is to be placed. This buffer must be at least count bytes long.

System calls don’t allocate memory for buffers that are used to return information to the caller. Instead, we must pass a pointer to a previously allocated memory buffer of the correct size. This contrasts with several library functions that do allocate memory buffers in order to return information to the caller.

A successful call to read() returns the number of bytes actually read, or 0 if end-offile is encountered. On error, the usual –1 is returned. The ssize_t data type is a signed integer type used to hold a byte count or a –1 error indication.

## Writing to a File: write()

The write() system call writes data to an open file
```c
#include <unistd.h>
ssize_t write(int fd, void *buffer, size_t count);
Returns number of bytes written, or –1 on error
```

The arguments to write() are similar to those for read(): buffer is the address of the data to be written; count is the number of bytes to write from buffer; and fd is a file descriptor referring to the file to which data is to be written.
On success, write() returns the number of bytes actually written;

## Closing a File: close()
The close() system call closes an open file descriptor, freeing it for subsequent reuse by the process. When a process terminates, all of its open file descriptors are automatically closed.

```c
#include <unistd.h>
int close(int fd);
```

## Relationship Between File Descriptors and Open Files

To understand what is going on, we need to examine three data structures maintained by the kernel:

- the per-process file descriptor table; z 
- the system-wide table of open file descriptions; and z 
- the file system i-node table.

**For each process, the kernel maintains a table of open file descriptors.** 
Each entry in this table records information about a single file descriptor, including:

- a set of flags controlling the operation of the file descriptor (there is just one such flag, the close-on-exec flag, which we describe in Section 27.4); and
- a reference to the open file description

////


## Duplicating File Descriptors
The shell achieves the redirection of standard error by duplicating file descriptor 2 so that it refers to the same open file description as file descriptor 1 (in the same way that descriptors 1 and 20 of process A refer to the same open file description in Figure 5-2). This effect can be achieved using the dup() and dup2() system calls.

he two file descriptors would not share a file offset pointer, and hence could end up overwriting each other’s output.

. Another reason is that the file may not be a disk file.

```c
int dup2(int oldfd, int newfd);
Returns (new) file descriptor on success, or –1 on error
```
The dup2() system call makes a duplicate of the file descriptor given in oldfd using the descriptor number supplied in newfd. If the file descriptor specified in newfd is already open, dup2() closes it first. (Any error that occurs during this close is silently ignored; safer programming practice is to explicitly close() newfd if it is open before the call to dup2().)

successful dup2() call returns the number of the duplicate descriptor (i.e., the value passed in newfd)


