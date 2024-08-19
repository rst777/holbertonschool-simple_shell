#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGUMENTS 1024
extern char **environ;
char **split_string(int max_argument);
int execute_command(int max_argument);
int main(void);
#endif
