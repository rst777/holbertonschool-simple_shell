#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"
extern char **environ;
#define MAX_ARGUMENTS 100
#include "main.h"
/**
*split_string - function .
*@max_argument: The number of arguments.
* This function reads and catchs the arguments (commands) passed on the prompt
* Return: a pointer of arguments
**/

/**  Fonction pour lire la ligne de commande et diviser en arguments */
char **split_string(int max_argument)

{
	int i;
	char *token;
	char **argv;
	char *buffer = NULL;
	size_t len = 0;
	ssize_t nread;

	i = 0;

/** using getline to get the commands */
	nread = getline(&buffer, &len, stdin);
	if (nread == -1)
	{
		free(buffer);
		 exit(EXIT_SUCCESS);
	}

/** allocating memory for arguments */
	argv = malloc(max_argument * sizeof(char *));

/** strtok with " " and "if there is "\n" to extract each argument command*/
	token = strtok(buffer, " \n");

	while (token != NULL && i < max_argument - 1)
	{
		/** puting it into a pointer called token */
		argv[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}
	argv[i] = NULL;

	/**Note : Pas besoin de libérer `buffer` ici car les pointeurs `argv[i]`*/

	return (argv);
}

/**
*execute_command - function .
*@max_argument: The number of arguments.
* This function excute the arguments (commands) passed to it
* Return: 0 on sucsess
**/

int execute_command(int max_argument)

{
	pid_t pid;
	int statut;
	char **argv;

/** we call our function to extract argument and devide it */
	argv = split_string(max_argument);
	if (argv == NULL)
	{
		return (-1);
	}
/** launching  process after our programme*/
	pid = fork();

	if (pid == -1)
	{
		perror("faillure");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		execve(argv[0], argv, environ);

		perror(argv[0]);
		free(argv);
		exit(EXIT_FAILURE);
	}

	else

	{
		wait(&statut);
		free(argv);
	}

	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
*main - function to execute the programe shell
*Return: 0 on sucsess
*/

int main(void)

{
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
		}

		if (execute_command(MAX_ARGUMENTS) == -1)
		{
			break;
		}
	}

	return (EXIT_SUCCESS);
}
