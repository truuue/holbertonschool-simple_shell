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
		if(pid == 0)
		{
			count = 0;

			token = strtok(line, " \n");
			while (token != NULL)
			{
				argv[count] = token;
				count++;
				token = strtok(NULL, " \n");
			}
			argv[count] = NULL;

			if(argv[0] != NULL)
			{
				execve(argv[0], argv, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				fprintf(stderr, "Erreur : commande vide\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	free(line);
	line = NULL;
	return(0);
}
