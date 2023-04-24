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
	char *token;
	int count = 0, pid = 0, status;

	while ((nread = getline(&line, &len, stdin)) != -1)
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
		argv[count] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execve(argv[0], argv, NULL);
			fprintf(stderr, "Erreur: commande introuvable\n");
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	return(0);
}
