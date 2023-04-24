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
	int count = 0, pid = 0, status;
	char *token;

	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			count = 0;

			token = strtok(line, " \n");
			if(token == NULL)
				continue;
			while (token != NULL)
			{
				argv[count++] = token;
				token = strtok(NULL, " \n");
			}
			execve(argv[0], argv, NULL);
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	return(0);
}
