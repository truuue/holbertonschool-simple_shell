#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char *av[], char *envp[])
{
	int MAX_ARGS = 1024;
	size_t len = 0;
	ssize_t nread;
	char *line = NULL;
	char *argv[MAX_ARGS];
	int count = 0, pid = 0, status;
	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		count = 0;
		char *token = strtok(line, " \n");
		if (token == NULL)
			continue;
		while (token != NULL)
		{
			argv[count] = token;
			count++;
			token = strtok(NULL, " \n");
		}
		argv[count] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execvp(argv[0], argv);
			fprintf(stderr, "Erreur: commande introuvable\n");
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	return 0;
}
