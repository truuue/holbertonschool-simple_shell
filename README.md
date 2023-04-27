#   Simple Shell

This is a basic shell program that executes commands by forking and calling execve. It accepts input from standard input and parses it into arguments to be passed to execve.

### Compilation

To compile the program, run the following command in the terminal :

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell.c -o shell`

### Usage

To start the shell, run the compiled program :

`./shell`

The shell will display a prompt and wait for user input.
Enter a command and press Enter to execute it.

### Supported Commands

This shell supports the following basic commands :

| Command   | Output                                  |
| --------- | ----------------------------------------|
| ls        | list directory contents                 |
| pwd       | print name of current/working directory |
| echo      | display a message                       |
| cat       | concatenate and display files           |

### Test

If you whant to test it I show you the steps :

```
/Compile the program/
user:~/holbertonschool-simple_shell# gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell.c -o shell
/Enter in the shell/
user:~/holbertonschool-simple_shell# ./shell
/Typing the ls command/
ls
/The output/
AUTHORS  main.h  man_1_simple_shell.1  README.md  shell  simple_shell.c
```

### Exit the Shell

To exit the shell, type `ctrl + D`.

### Error Handling

The shell will display an error message if the entered command is not found.
If forking fails, an error message will be displayed and the shell will exit.

### Flowchart

                    +--------------------+
                    |   Start Program    |
                    +--------------------+
                              |
                              V
                    +--------------------+
                    |  Read Input Line   |
                    +--------------------+
                              |
                              V
                   +-----------------------+
                   | Create Child Process  |
                   +-----------------------+
                              |
                              V
                  +-------------------------+
                  | Child Process Executes  |
                  |     Command/Program     |
                  +-------------------------+
                              |
                              V
                  +-------------------------+
                  |  Parent Process Waits   |
                  |   for Child to Finish   |
                  +-------------------------+
                              |
                              V
                     +-------------------+
                     |    End Program    |
                     +-------------------+

###### Date

04/27/2023
