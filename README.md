# 42-Pipex

##  How does `< file1 cmd1 | cmd2 > file2` work?

The command < file1 cmd1 | cmd2 > file2 involves input/output redirection and a pipeline. Here's an explanation step by step:

1. < file1: This part uses input redirection. It takes the content of the file named "file1" and provides it as the input for the command that follows.

2. cmd1: This is the first command in the pipeline. It processes the input received from "file1."

3. `|`: The pipe symbol (`|`) is used to connect the output of the command on its left (in this case, the output of cmd1) to the input of the command on its right (in this case, cmd2).

4. cmd2: This is the second command in the pipeline. It takes the output of cmd1 as its input.

5. > file2: This part involves output redirection. It takes the output of cmd2 and writes it to the file named "file2."


Let's create an example using `grep` and `wc`. Suppose you have the following commands:

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

1. `< file1`: Takes the content of "file1" ("banana\napple\norange\napple\ngrape\n") and provides it as input for grep "apple".
2. `grep "apple"`: Searches for lines containing the word "apple," resulting in "apple\napple\n".
3. `wc -l`: Counts the number of lines in the output, resulting in "2\n".
4. `> file2`: Writes the final line count (2) to "file2."

Now, you can check the content of "file2" to see the result:

```
cat file2
```
The output should be: `2`.

