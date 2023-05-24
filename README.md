# Project Title

### 0x16. C - Simple Shell
##### Weight: 10 

## Names of Participant
+ Joseph Johnson Aniekan
+ Olabanji Enioluwayan Emmanuel (collaborator)

## Resources
1. Unix shell
2. Thompson shell
3. Ken Thompson

## Allowed Editors
+ Vi|Vim
+ Emacs

## Compilation

***gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh***

## Concept

**PID & PPID**
> A process is an instance of an executing program, that has a unique process ID. This process ID is used by many functions and system calls to interact with and manipulate processes. In order to retrieve the current process’ ID, you can use the system call 

**Arguments**
> The command line arguments are passed through the main function: int main(int ac, char **av); av is a NULL terminated array of strings ac is the number of items in av av[0] usually contains the name used to invoke the current program. av[1] is the first argument of the program, av[2] the second, and so on.

**Executing a program**
> The system call execve allows a process to execute another program (man 2 execve). Note that this system call does load the new program into the current process’ memory in place of the “previous” program: on success execve does not return to continue the rest of the “previous” program.

## Output

***Interactive mode***

```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
***Non-Interactive mode***

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
