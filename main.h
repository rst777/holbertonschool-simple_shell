#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Définition des constantes */
#define MAX_ARGUMENTS 100

/* Déclaration des fonctions */
char **split_string(int max_argument);
int execute_command(int max_argument);

#endif /* MAIN_H */
