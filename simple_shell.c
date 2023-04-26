#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{
	size_t len = 0;
	ssize_t nread;
	char *line = NULL, *token;
	char command[1024];
	int status;
	(void)argc;

	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		int count = 0;
		pid_t pid = fork();
		if (pid == 0)
		{
			token = strtok(line, " \n");
			if (token == NULL)
				continue;
			while (token != NULL)
			{
				argv[count] = token;
				count++;
				token = strtok(NULL, " \n");
			}
			argv[count] = NULL;

			if (strcmp(argv[0], "ls") == 0)
			{
				strcpy(command, "/bin/ls");
				argv[0] = command;
			}
			else if (strcmp(argv[0], "pwd") == 0)
			{
				strcpy(command, "/bin/pwd");
				argv[0] = command;
			}
			else if (strcmp(argv[0], "echo") == 0)
			{
				strcpy(command, "/bin/echo");
				argv[0] = command;
			}
			else if (strcmp(argv[0], "cat") == 0)
			{
				strcpy(command, "/bin/cat");
				argv[0] = command;
			}

			execve(argv[0], argv, envp);
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
