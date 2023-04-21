#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	size_t len = 0;
	ssize_t nread;
	char *line = NULL;
	char *argv[1024];
	int count, pid, status;
	char *token;

	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			count = 0;

			token = strtok(line, " \n");
			while (token != NULL && count < 1024)
			{
				argv[count++] = token;
				token = strtok(NULL, " \n");
			}

			argv[count] = NULL;

			execve(argv[0], argv, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		} else {
			wait(&status);
		}
	}

	free(line);
	return 0;
}
