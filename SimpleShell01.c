#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char *av[1024], char *envp[])
{
        size_t len = 0;
        ssize_t nread;
        char *line = NULL, *token, command[1024];
        char *path = getenv("PATH");
        char new_path[1024];
        int count = 0, pid = 0, status;
        struct stat stat_buf;

        (void)ac;

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

                pid = fork();
                if (pid == 0)
                {
                        sprintf(command, "/bin/%s", av[0]);
                        sprintf(new_path, "%s:%s", path, "/bin");
                        setenv("PATH", new_path, 1);

                        if (stat(command, &stat_buf) == -1) {
                                fprintf(stderr, "Error: file not found or not accessible\n");
                                exit(1);
                        }
                        if (access(command, X_OK) == -1) {
                                fprintf(stderr, "Error: file not executable\n");
                                exit(1);
                        }

                        execve(command, av, envp);
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
