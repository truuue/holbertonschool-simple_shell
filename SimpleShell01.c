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
	int count = 0, pid = 0, status, i, spaces = 1;
	char *token;

	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		pid = fork();
		if(pid == 0)
		{
			count = 0;

			token = strtok(line, " \n");
<<<<<<< HEAD
			while (token != NULL && count < 1024)
			{
				argv[count++] = token;
				token = strtok(NULL, " \n");
			}

			argv[count] = NULL;

			execvp(argv[0], argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		} else {
			wait(&status);
=======
			while (token != NULL)
			{
				argv[count] = token;
				count++;
				token = strtok(NULL, " \n");
			}

			for (i = 0; i < strlen(argv[0]); i++)
			{
				if (argv[0][i] != ' ')
				{
					spaces = 0;
					break;
				}
			}
			if(spaces)
			{
				exit(0);
			}
			execve(argv[0], argv, NULL);
		}
		else
		{
			waitpid(pid, &status, 0);
>>>>>>> 6293c900dd8dd45f5854787d6d9e97d2278f3ccb
		}
	}

	free(line);
	line = NULL;
	return(0);
}
