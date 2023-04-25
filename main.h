#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int main(int ac, char *av[1024], char *envp[]);
char *_getenv(const char *name);
void print_path(void);

struct ListNode {
	char* dir;
	struct ListNode* next;
};

#endif
