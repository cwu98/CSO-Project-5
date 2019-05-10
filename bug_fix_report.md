

# Name:  Cary Wu

## Bug 1 fix

I fixed Bug 1 in lines 15 and 80 in the procline.c program. 

The original mistake is that ` int narg ` local variable was declared but not initialized. Since it's a local variable, in C programming language, the variable will have indeterminate value. Therefore, one cannot assume that the value is automatically an integer that's 0. Using `narg` without initializing it to 0 will lead to undefined behavior. 

In line 80 at the end of the `while(1)` loop, it's important to reset `narg` to `0`. Setting it to `MAXARG` would not make sense. We want to reset `narg`, the number of arguments, to 0 for the next instruction.


## Bug 2 fix

I fixed Bug 2 in lines 59-68 in the procline.c program.

I implemented the cd command using chdir(). The reason `cd` does not behave as we would expect is because this `cd` does not exist as an executable command. It does not work with `execvp()`. Therefore, to fix the bug, I had to implement a built-in `cd` function that would recognize `cd PATH_NAME` as a command to change the directory. The `int chdir(cons char *path);` call basically accompishes what we want when we type `cd`. 

So I used `strcmp(arg[0],"cd")==0)` to check for whether the user typed in the `cd`command. Then, if `arg[1]==NULL`, that means all that the user type in was `cd  ` and did not specify a path. By default, the directory should be changed to the home directory which is specified in line 61 and 19 by `getenv("HOME")`. 

If the user typed in a `path_name` or `..` after `cd `, then change the directory using `path_name`. Furthermore, `chdir()` already knows how to handle the `..` case.  

If the return value is not 0, then `chdir()` was not successful, so print error message.

## Bug 3 fix

I fixed Bug 3 in lines 36-38 in the procline.c program. 

Since the `exit` command is not recognized, it has to be built into this shell. I implemented the `exit` command by using `strcmp(arg[0],"exit)==0` to see if the user typed in `exit`. If so, call `exit(0)` to terminate the shell program and return `0` to signify success. Since we're not expecting any arguments after the `exit` command and the terminal should terminate, I think it's fine to put it inside the `case ARG: ` chunk. 

## Bug 4 fix

I fixed Bug 4 in lines 8-12 and in line 31 in the proj5.c program, lines 17-21 in the runcommand.c program. 

For this bug, we do not want `Ctrl+C` to terminate the shell, just the foreground processes. 
Before the main function, I implemented a signal handler for the `SIGINT` signal. In the `void sigint_handler(int num)`signal handler function, I put a recursive piece of code: `signal(SIGINT, sigint_handler);` to reset the signal disposition (signal disposition determines how the process behaves when it is delivered the signal). There are cases where a handler set with signal will not be properly used again because after one signal, the handler might be reset to the default, which for `SIGINT`, is to kill the process. In order to handle another signal of this type, the sigint_handler calls the `signal` function again to set the signal disposition. 

I call the signal function inside `main()` of proj5.c.

We don't want SIGINT signal to terminate background processes, which are the processes called with `&`. In the runcommand.c program, I added an `if` statement for background processes, using the `if (where==BACKGROUND) ` check. The code inside the  if block uses `signal` to catch the `SIGINT` signal and executes `SIG_IGN` instead, which just ignores the signal. So, typing `Ctrl+C` when a background process is running will not terminate the background process. 

## Bug 5 fix

I fixed Bug 5 in lines 18-24 in the proj5.c program.

I implemented the `sigchld_handler`. When a child process stops or terminates, the `SIGCHLD` signal is sent to the parent process. The program should catch the `SIGCHLD` signal and reap the zombie/defunct process, which is a child process that has terminated but still has an entry in the process table. When a process terminates, it still consumes system resources so it's best to reap. 

Reaping is performed by parent on terminated child using `wait()` or `waitpid()` function. The parent is given the exit status. The return val is the process id of the child process that terminated. In the `while` line, because the first argument is -1, this tells `waitpid` to block until some child process terminated. If the pid > 0, the wait set is a single child process. 
`WNOHANG` is an option that can be set in the third parameter. It causes `waitpid()` to return immediately if none of the child processes in the wait set terminated, instead of waiting. `waitpid` will return 0 instead of blocking. This option allows continuation of doing work while waiting for a child to terminate.


I call the signal function inside `main()` of proj5.c.


