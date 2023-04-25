#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 1024

int main(int ac, char *av[])
{
	size_t len = 0;
	ssize_t nread;
	char *line = NULL, *token, command[1024];
	char *path = NULL;
	char new_path[1024];
	extern char **environ;
	int count = 0, pid = 0, status, i;
	(void)ac;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = &environ[i][5];
			break;
		}
	}

	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		count = 0;
		token = strtok(line, " \n");
		if (token == NULL)
			continue;
		while (token != NULL)
		{
			if (count < MAX_ARGS - 1) {
				av[count] = token;
				count++;
			}
			token = strtok(NULL, " \n");
		}
		av[count] = NULL;

		pid = fork();
		if (pid == 0)
		{
			sprintf(command, "/bin/%s", av[0]);
			sprintf(new_path, "%s:%s", path, "/bin");
			putenv(strdup(new_path));
			execve(command, av, environ);
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
