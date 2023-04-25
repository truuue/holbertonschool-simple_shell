#include "main.h"

void print_path(void)
{
	char *path_env;
	char *path_copy;
	char *token;

	path_env = _getenv("PATH");
	if (path_env == NULL)
	{
		printf("PATH variable not found\n");
		return;
	}
	path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		printf("Memory allocation error\n");
		return;
	}
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
	free(path_copy);
}
