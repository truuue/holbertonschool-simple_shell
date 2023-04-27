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

-   **ls** : list directory contents
-   **pwd** : print name of current/working directory
-   **echo** : display a message
-   **cat** : concatenate and display files

### Exit the Shell

To exit the shell, type `ctrl + D`.

### Error Handling

The shell will display an error message if the entered command is not found.
If forking fails, an error message will be displayed and the shell will exit.
