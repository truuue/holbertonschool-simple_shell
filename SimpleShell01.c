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
            
            int i, spaces = 1;
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
		}
	}
	free(line);
    line = NULL;
	return(0);
}
