A process is an instance of an executing program. In this section, we elaborate on this definition and clarify the distinction between a program and a process.

A program is a file containing a range of information that describes how to construct a process at run time. This information includes the following:

- Binary format identification: Each program file includes metainformation describing the format of the executable file. This enables the kernel to interpret the remaining information in the file. Historically, two widely used formats for UNIX executable files were the original a.out (“assembler output”) format and the later, more sophisticated COFF (Common Object File Format).
- Machine-language instructions: These encode the algorithm of the program
- Program entry-point address: This identifies the location of the instruction at which execution of the program should commence
- Data: The program file contains values used to initialize variables and also literal constants used by the program (e.g., strings).
- Symbol and relocation tables: These describe the locations and names of functions and variables within the program. These tables are used for a variety of purposes, including debugging and run-time symbol resolution (dynamic linking).
- Shared-library and dynamic-linking information: The program file includes fields listing the shared libraries that the program needs to use at run time and the pathname of the dynamic linker that should be used to load these libraries.
- Other information: The program file contains various other information that describes how to construct a process.

One program may be used to construct many processes, or, put conversely, many processes may be running the same program.

## Process ID and Parent Process ID

Each process has a process ID (PID), a positive integer that uniquely identifies the process on the system. Process IDs are used and returned by a variety of system calls. For example, the kill() system call (Section 20.5) allows the caller to send a signal to a process with a specific process ID. The process ID is also useful if we need to build an identifier that is unique to a process. A common example of this is the use of the process ID as part of a process-unique filename.

## Memory Layout of a Process

The memory allocated to each process is composed of a number of parts, usually referred to as segments.

- The text segment contains the machine-language instructions of the program run by the process. The text segment is made read-only so that a process doesn’t accidentally modify its own instructions via a bad pointer value.
- The initialized data segment contains global and static variables that are explicitly initialized.
- The uninitialized data segment contains global and static variables that are not explicitly initialized. Before starting the program, the system initializes all memory in this segment to 0.
- The stack is a dynamically growing and shrinking segment containing stack frames. One stack frame is allocated for each currently called function.
- The heap is an area from which memory (for variables) can be dynamically allocated at run time. The top end of the heap is called the program break.

