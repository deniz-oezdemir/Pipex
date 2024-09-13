# Pipex

Recreating the functionality of the shell pipe `|`.

## Table of Contents
- [About](#about)
- [TL;DR: Installation and Usage](#tldr-installation-and-usage)
- [Explanation of `< file1 cmd1 | cmd2 > file2`](#explanation-of--file1-cmd1--cmd2--file2)
- [Program Structure (Graph)](#program-structure-graph)
- [Information Flow during Program Execution (Graph)](#information-flow-during-program-execution-graph)
- [Functions Used in the Program](#functions-used-in-the-program)
- [Debugging](#debugging)
- [Key Learnings](#key-learnings)
- [Future Work](#future-work)
- [Useful functions](#useful-functions)
- [Sources](#sources)

## About

When executed as `./pipex file1 cmd1 cmd2 file2`, pipex mirrors the behavior of the shell command `< file1 cmd1 | cmd2 > file2`.

## TL;DR: Installation and Usage

To install Pipex for your project, follow these steps:

1. Clone the repository from GitHub, navigate to the directory, build the pipex executable:

    ```
    git clone https://github.com/deniz/pipex.git
    cd pipex
    make
    ```

2. Run Pipex with the desired input and commands:

    ```
    ./pipex file1 cmd1 cmd2 file2
    ```

    Replace `file1` with the input file, `cmd1` with the first command, `cmd2` with the second command, and `file2` with the output file.

3. Check the output file to see the result:

    ```
    cat file2
    ```

    The output should contain the result of the piped commands.



##  Explanation of `< file1 cmd1 | cmd2 > file2`

###   General functionality
The command < file1 cmd1 | cmd2 > file2 involves input/output redirection and a pipeline. Here's an explanation step by step:
1. `< file1`: This part uses input redirection. It takes the content of the file named `file1` and provides it as the input for the command that follows.
2. `cmd1`: This is the first command in the pipeline. It processes the input received from `file1.`
3. `|`: The pipe symbol is used to connect the output of the command on its left (in this case, the output of `cmd1`) to the input of the command on its right (in this case, `cmd2`).
4. `cmd2`: This is the second command in the pipeline. It takes the output of cmd1 as its input.
5. `> file2`: This part involves output redirection. It takes the output of cmd2 and writes it to the file named "file2."

###   Specific example
Let's run through an example using `grep` and `wc`. Suppose you have the following commands:
1. cmd1: Searches for lines containing the word "apple" in the input.
2. cmd2: Counts the number of lines in the input.

Now, let's create an input file "file1" with some lines:

```
echo -e "banana\napple\norange\napple\ngrape\n" > file1
```

Now, let's use the < file1 cmd1 | cmd2 > file2 command:

```
< file1 grep "apple" | wc -l > file2
```

Here's what happens step by step:
1. `< file1`: Takes the content of `file1` (`banana\napple\norange\napple\ngrape\n`) and provides it as input for `grep "apple"`.
2. `grep "apple"`: Searches for lines containing the word "apple," resulting in "apple\napple\n".
3. `wc -l`: Counts the number of lines in the output, resulting in "2\n".
4. `> file2`: Writes the final line count (2) to `file2.`

Now, you can check the content of "file2" to see the result:

```
cat file2
```
The output should be: `2`.

Try also `< file1 cat`.

## Program Structure (Graph)

![Pipex structure](./Pipex%20structure.svg)

## Information Flow during Program Execution (Graph)

![Pipex info flow](./Pipex%20info%20flow.svg)

## Functions used in the Program

* `pid_t` is a data type in C that represents a process ID, which is a unique identifier assigned to each process in a Unix-like operating system. It is commonly used in functions and system calls related to process management. Using `pid_t` ensures portability and consistency when working with process IDs across different systems.

* When the function `int main(int ac, char **av, char **ev)` is executed, the `ev` contains the environment variables (intended to be passed onto `execve`). These variables may include information such as the user's home directory, the path to executable files, and other configuration settings. Type `env` in your terminal to see what is included.

* The `int pipe(int fd[2])` function establishes a unidirectional communication channel between two processes, creating an array of two integers `fd` where `fd[0]` is utilized for reading from the pipe, and `fd[1]` is used for writing to the pipe (refer to second graph in source 1).

* The `pid_t fork()` function creates a new process by duplicating the existing process (parent process). It's like making a copy of our program. The original program continues running as the 'parent,' and the new copy runs as the 'child.' We can tell which one is which because `fork()` gives 0 to the child and a number to the parent. If something goes wrong, it gives -1.

* The `int dup2(int oldfd, int newfd)` duplicates a file descriptor. It takes two arguments: `oldfd`, the file descriptor to be duplicated, and `newfd`, the file descriptor to which oldfd should be duplicated.

* The `pid_t waitpid(pid_t pid, int *status, int options)` function is used to wait for a particular child process to complete its execution. The `pid` parameter is the process ID of the specific child process for which the parent is waiting. We use `NULL` as the second parameter because we aren't interested in storing the exit status of the child process. The third parameter, `0`, signifies that we're not adding any extra options.

* The `int access(const char *pathname, int mode)` function "checks whether calling process can access the file pathname" (refer to source 3). In our case the condition `access(path, F_OK) == 0` checks if the file specified by the path exists.

* The `int execve(const char *filename, char *const argv[], char *const envp[])` function executes the program pointed to by filename.
In our case `execve(path, cmd, ev)` it takes three arguments: the `path` to the executable file, the array `cmd` of commands the new program needs and the array of pointers to null-terminated strings `ev` representing the environment variables.
The execve function is responsible for running a specified command. It needs to explore every possible path to find the correct location of the executable - for example, if you want to know the path to the `touch` command, you can type `which touch` in your terminal. If the command exists, execve will execute it; otherwise, it will do nothing and return -1, indicating an error.
Once the command is executed, execve takes care of cleaning up ongoing processes, including variables. You don't need to worry about freeing up resources; execve handles this for you.

## Debugging

For debugging I used the [pipex-tester](https://github.com/vfurmane/pipex-tester):
* A function `void free_split(char **strs)` was added to free the allocated memory in case of `execve` errors.
* A check for "/dev/urandom" as the first command was added for preventing timeouts by handling this specific case where attempting to open "/dev/urandom" (interface to the kernel's random number generator that provides access to a source of cryptographically secure pseudo-random numbers) leads to a lengthy operation or blocking behavior.
* The error-handling function `void err(int nbr)` was added to display specific error messages based on the error case and exit the program accordingly.

## Key Learnings

* Explored shell commands and pipes, understanding how they can work together for specific tasks.
* Honed skills in file input/output operations, text manipulation and the processes of reading and writing to files.
* Acquired knowledge on managing processes, including process creation, termination, and synchronization.

## Future Work

* Implement a general timeout prevention instead of the specific workaround for the case of "/dev/urandom" being the first command.
* Improve the error-handling function `void err(int nbr)` to provide more accurate error handling for when `access` in `char *get_path(char *cmd, char **ev)` is unsuccessful.
* Investigate the possibility of preventing the parent process from running when the child process encounters an error, and implement this functionality if feasible.

## Useful functions

* `access`, `pipe`, `fork`, `dup2`, `execve`, `waitpid`, `perror`, `open`: Refer to [linux man pages](https://linux.die.net/man/).
* `ft_split`, `ft_strjoin`, `ft_strnstr`: Refer to [libft](https://github.com/deniz-oezdemir/libft).

## Sources

* [Explanation of and pseudocode for the project](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901) for the mandatory part
* [Explanation of how fork() works](https://www.geeksforgeeks.org/fork-system-call/)
* [access(2) - Linux man page](https://linux.die.net/man/2/access)
* [Explanation of stdin, stdout and stderr](https://stackoverflow.com/questions/3385201/confused-about-stdin-stdout-and-stderr)
