Shared libraries are a technique for placing library functions into a single unit that can be shared by multiple processes at run time. This technique can save both disk space and RAM. This chapter covers the fundamentals of shared libraries. The next chapter covers a number of advanced features of shared libraries.


## Linking
One way of building a program is simply to compile each of its source files to produce corresponding object files, and then link all of these object files together to produce the executable program

Linking is actually performed by the separate linker program, ld. When we link a program using the cc (or gcc) command, the compiler invokes ld behind the scenes. On Linux, the linker should always be invoked indirectly via gcc, since gcc ensures that ld is invoked with the correct options and links the program against the correct library files.

Although this technique saves us compilation time, it still suffers from the disadvantage that we must name all of the object files during the link phase. Furthermore, our directories may be inconveniently cluttered with a large number of object files.

- To get around these problems, we can group a set of object files into a single unit, known as an object library. **Object libraries are of two types: static and shared**. Shared libraries are the more modern type of object library, and provide several advantages over static libraries, as we describe in Section 41.3.

## Static libraries
They provide the following benefits:

- We can place a set of commonly used object files into a single library file that can then be used to build multiple executables, without needing to recompile the original source files when building each application.
- Link commands become simpler. Instead of listing a long series of object files on the link command line, we specify just the name of the static library. The linker knows how to search the static library and extract the objects required by the executable.

In effect, a static library is simply a file holding copies of all of the object files added to it.



## Shared libraries

When a program is built by linking against a static library (or, for that matter, without using a library at all), the resulting executable file includes copies of all of the object files that were linked into the program.

Thus, when several different executables use the same object modules, each executable has its own copy of the object modules. This redundancy of code has several disadvantages:

- Disk space is wasted storing multiple copies of the same object modules. Such wastage can be considerable.
- If several different programs using the same modules are running at the same time, then each holds separate copies of the object modules in virtual memory, thus increasing the overall virtual memory demands on the system.
- If a change is required (perhaps a security or bug fix) to an object module in a static library, then all executables using that module must be relinked in order to incorporate the change. This disadvantage is further compounded by the fact that the system administrator needs to be aware of which applications were linked against the library.

Shared libraries were designed to address these shortcomings. **The key idea of a shared library is that a single copy of the object modules is shared by all programs requiring the modules.**

**The object modules are not copied into the linked executable**; instead, a single copy of the library is loaded into memory at run time, when the first program requiring modules from the shared library is started.

When other programs using the same shared library are later executed, they use the copy of the library that is already loaded into memory. The use of shared libraries means that executable programs require less space on disk and (when running) in virtual memory.

Advantages:
- Because overall program size is smaller, in some cases, programs can be loaded into memory and started more quickly. This point holds true only for large shared libraries that are already in use by another program. The first program to load a shared library will actually take longer to start, since the shared library must be found and loaded into memory.
- Since object modules are not copied into the executable files, but instead maintained centrally in the shared library, it is possible (subject to limitations described in Section 41.8) to make changes to the object modules without requiring programs to be relinked in order to see the changes. Such changes can be carried out even while running programs are using an existing version of the shared library.


Summary

An object library is an aggregation of compiled object modules that can be employed by programs that are linked against the library. Like other UNIX implementations, Linux provides two types of object libraries: static libraries, which were the only type of library available under early UNIX systems, and the more modern shared libraries.

Because they provide several advantages over static libraries, shared libraries are the predominant type of library in use on contemporary UNIX systems. The advantages of shared libraries spring primarily from the fact that when a program is linked against the library, copies of the object modules required by the program are not included in the resulting executable. Instead, the (static) linker merely includes information in the executable file about the shared libraries that are
equired at run time. When the file is executed, the dynamic linker uses this information to load the required shared libraries. At run time, all programs using the same shared library share a single copy of that library in memory. Since shared libraries are not copied into executable files, and a single memory-resident copy of the shared library is employed by all programs at run time, shared libraries reduce the amount of disk space and memory required by the system.

## Dynamically Loaded Libraries

When an executable starts, the dynamic linker loads all of the shared libraries in the program’s dynamic dependency list. Sometimes, however, it can be useful to load libraries at a later time. For example, a plug-in is loaded only when it is needed. This functionality is provided by an API to the dynamic linker.

The dlopen API enables a program to open a shared library at run time, search for a function by name in that library, and then call the function. A shared library loaded at run time in this way is commonly referred to as a dynamically loaded library, and is created in the same way as any other shared library

The core dlopen API consists of the following functions:
- The dlopen() function opens a shared library, returning a handle used by subsequent calls.
- The dlsym() function searches a library for a symbol (a string containing the name of a function or variable) and returns its address.
- The dlclose() function closes a library previously opened by dlopen().
- The dlerror() function returns an error-message string, and is used after a failure return from one of the preceding functions.

## Opening a Shared Library: dlopen()

```c++
#include <dlfcn.h>
void *dlopen(const char *libfilename, int flags);

Returns library handle on success, or NULL on error
```

The dlopen() function loads the shared library named in libfilename into the calling process’s virtual address space and increments the count of open references to the library.

The flags argument is a bit mask that must include exactly one of the constants RTLD_LAZY or RTLD_NOW, with the following meanings:

RTLD_LAZY - Undefined function symbols in the library should be resolved only as the code is executed. If a piece of code requiring a particular symbol is not executed, that symbol is never resolved. Lazy resolution is performed only for function references; references to variables are always resolved immediately. Specifying the RTLD_LAZY flag provides behavior that corresponds to the normal operation of the dynamic linker when loading the shared libraries identified in an executable’s dynamic dependency list.

RTLD_NOW -  All undefined symbols in the library should be immediately resolved before dlopen() completes, regardless of whether they will ever be required. As a consequence, opening the library is slower, but any potential undefined function symbol errors are detected immediately instead of at some later time. This can be useful when debugging an application, or simply to ensure that an application fails immediately on an unresolved symbol, rather than doing so only after executing for a long time.

## Diagnosing Errors: dlerror()

```c++
#include <dlfcn.h>
const char *dlerror(void);

Returns pointer to error-diagnostic string, or NULL if no error has occurred since previous call to dlerror()
```

If we receive an error return from dlopen() or one of the other functions in the dlopen API, we can use dlerror() to obtain a pointer to a string that indicates the cause of the error


The dlerror() function returns NULL if no error has occurred since the last call to dlerror(). We’ll see how this is useful in the next section.
## Obtaining the Address of a Symbol: dlsym()

```c++
#include <dlfcn.h>
void *dlsym(void *handle, char *symbol);
Returns address of symbol, or NULL if symbol is not found
```

If symbol is found, dlsym() returns its address; otherwise, dlsym() returns NULL. The handle argument is normally a library handle returned by a previous call to dlopen(). Alternatively, it may be one of the so-called pseudohandles described below.


If symbol is the name of a variable, then we can assign the return value of dlsym() to an appropriate pointer type, and obtain the value of the variable by dereferencing the pointer:




On many UNIX implementations, we can use casts such as the following to eliminate warnings from the C compiler:

```c
funcp = (int (*) (int)) dlsym(handle, symbol);
```



## Closing a Shared Library: dlclose()

The dlclose() function closes a library.
```c++
#include <dlfcn.h>
int dlclose(void *handle);
Returns 0 on success, or –1 on error
```


## Summary

The dynamic linker provides the dlopen API, which allows programs to explicitly load additional shared libraries at run time. This allows programs to implement plug-in functionality.
