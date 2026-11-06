## The exec() Library Functions

```c
#include <unistd.h>

int execle(const char *pathname, const char *arg, ... 
		   /* , (char *) NULL, char *const envp[] */ );

int execlp(const char *filename, const char *arg, ...
		   /* , (char *) NULL */);
int execvp(const char *filename, char *const argv[]);
int execv(const char *pathname, char *const argv[]);
int execl(const char *pathname, const char *arg, ...
		  /* , (char *) NULL */);
None of the above returns on success; all return –1 on error
```

- Most of the exec() functions expect a pathname as the specification of the new program to be loaded.
- Instead of using an array to specify the argv list for the new program, execle(), execlp(), and execl() require the programmer to specify the arguments as a list of strings within the call.
- The names of these functions contain the letter l (for list) to distinguish them from those functions requiring the argument list as a NULLterminated array. The names of the functions that require the argument list as an array (execve(), execvp(), and execv()) contain the letter v (for vector).

![](Pasted%20image%2020231209024259.png)

