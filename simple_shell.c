#include "main.h"

/**
 * main - shell program that executes commands
 * @ac: argument count
 * @av: argument vector
 * @envp: environment variables
 * Return: 0 on success, -1 on failure
 */

int main(int ac, char *av[1024], char *envp[])
{
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	char *line = NULL, *token;
	char command[1024];
	int status;

	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		ac = 0;
		if (strcmp(line, "exit\n") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		pid = fork();
		if (pid == 0)
		{
			token = strtok(line, " \n");
			if (token == NULL)
				continue;
			while (token != NULL)
			{
				av[ac] = token;
				ac++;
				token = strtok(NULL, " \n");
			}
			av[ac] = NULL;

			if (strcmp(av[0], "ls") == 0)
			{
				strcpy(command, "/bin/ls");
				av[0] = command;
			}
			else if (strcmp(av[0], "pwd") == 0)
			{
				strcpy(command, "/bin/pwd");
				av[0] = command;
			}
			else if (strcmp(av[0], "echo") == 0)
			{
				strcpy(command, "/bin/echo");
				av[0] = command;
			}
			else if (strcmp(av[0], "cat") == 0)
			{
				strcpy(command, "/bin/cat");
				av[0] = command;
			}

			execve(av[0], av, envp);
			fprintf(stderr, "Error: command not found\n");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			fprintf(stderr, "Error: failed to fork process\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	free(line);
	return (0);
}
