#include "main.h"

int main(int ac, char *av[1024], char *envp[])
{
        size_t len = 0;
        ssize_t nread;
        char *line = NULL, *token;
        char *path_token, *saveptr = NULL, *path;
        char *path_list[1024];
        char command[1024];
        int count = 0, i, pid = 0, status, path_count = 0, found = 0;
        (void) ac;

        path = getenv("PATH");
        if (path == NULL) {
                fprintf(stderr, "Error: PATH environment variable not found\n");
                exit(1);
        }

        path_count = 0;
        path_token = strtok_r(path, ":", &saveptr);
        while (path_token != NULL) {
                path_list[path_count++] = path_token;
                path_token = strtok_r(NULL, ":", &saveptr);
        }

        while ((nread = getline(&line, &len, stdin)) != -1)
        {
                count = 0;
                token = strtok(line, " \n");
                if (token == NULL)
                        continue;
                while (token != NULL)
                {
                        av[count] = token;
                        count++;
                        token = strtok(NULL, " \n");
                }
                av[count] = NULL;
                found = 0;
                for(i = 0; i < path_count; i++)
                {
                        sprintf(command, "%s/%s", path_list[i], av[0]);
                        if(access(command, X_OK) == 0)
                        {
                                found = 1;
                                break;
                        }
                }
                if(!found) {
                        fprintf(stderr, "Error: command not found\n");
                        continue;
                }

                pid = fork();
                if(pid == 0)
                {
                        execve(command, av, envp);
                        fprintf(stderr, "Error: execve failed\n");
                        exit(1);
                }
                else
                {
                        wait(&status);
                }
        }
        free(line);
        return (0);
}
