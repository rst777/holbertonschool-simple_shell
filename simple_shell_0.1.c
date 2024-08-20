#include "main.h"
/**
 * find_command_path - Trouve le chemin de la commande en recherchant dans PATH
 * @command: Commande à exécuter
 *
 * Return: Le chemin complet de la commande ou NULL si non trouvé
 */
char *find_command_path(char *command)
{
	char *path = NULL;
	char *token, *path_copy;
	char full_path[MAX_COMMAND_LENGTH];
	struct stat st;
	int i;
	/* Rechercher la variable d'environnement PATH dans environ */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5; /* Sauter "PATH=" */
			break;
		}
	}
		if (path == NULL)
	{
		return (NULL);
	}
	/* Créer une copie de la variable PATH pour utiliser strtok sans problème */
		path_copy = strdup(path);
		if (path_copy == NULL)
		{
			return (NULL);
		}
	/*	Diviser PATH en tokens et rechercher la commande */
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR)
		{
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	return (NULL);
}
/**
 * free_argv - free momory allouée to all arguments.
 * @argv: array of pointer arguments.
 */
void free_argv(char **argv)
{
	int i;

	if (argv == NULL)
	{
		return;
	}
	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);
}

/**
 *split_string - function .
 *@max_argument: The number of arguments.
 * This function reads and catchs the arguments (commands) passed on the prompt
 * Return: a pointer of arguments
 **/

/**  Fonction pour lire la ligne de commande et diviser en arguments */
char **split_string(int max_argument)
{
	int i = 0;
	char *token, **argv;
	char *buffer = NULL;
	size_t len = 0;
	ssize_t nread;
	/** using getline to get the commands */
	nread = getline(&buffer, &len, stdin);
	if (nread == -1)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	else
		buffer[nread - 1] = '\0'; /* Supprimer le retour à la ligne */
	/** allocating memory for arguments */
	argv = malloc(max_argument * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	/* strtok with " " and "if there is "\n" to extract each argument command */
	token = strtok(buffer, " \n");
	while (token != NULL && i < max_argument - 1)
	{ /** put each token into agv[i] */
		argv[i] = strdup(token);
		if (argv[i] == NULL)
		{
			perror("strdup");
			free(buffer);
			free_argv(argv);
			exit(EXIT_FAILURE);
		}
		i++;
		token = strtok(NULL, " \n");
	}
	argv[i] = NULL;
	free(buffer);
	return (argv);
}
/**
 *execute_command - function .
 *@max_argument: The number of arguments.
 *@envp: Tableau des variables d'environement.
 * This function excute the arguments (commands) passed to it
 * Return: 0 on sucsess
 **/
int execute_command(int max_argument, char **envp)
{
	pid_t pid;
	int statut;
	char **argv;
	char *command_path;

	/* we call our function to extract argument and devide it */
	argv = split_string(max_argument);
	if (argv == NULL || argv[0] == NULL)
	{
		free_argv(argv);
		return (-1);
	}
	/* Si le chemin est absolu ou relatif, pas besoin de chercher dans PATH */
	if (argv[0][0] == '/' || argv[0][0] == '.')
	{
		command_path = strdup(argv[0]);
	}
	else
	{
	command_path = find_command_path(argv[0]);
	}
	if (command_path == NULL)
	{
		fprintf(stderr, "./hsh: %s: No such file or directory\n", argv[0]);
		free_argv(argv);
		return (-1);
	}
	/* launching process after our programme*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		free_argv(argv);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		/* Dans le processus fils, exécuter la commande */
		if (execve(command_path, argv, envp) == -1)
		{
			perror(argv[0]);
			free(command_path);
			free_argv(argv);
			exit(EXIT_FAILURE);
		}
	}
		else
		{
		/* Dans le processus père, attendre la fin du fils */
		waitpid(pid, &statut, 0);
		}
		free(command_path);
		free_argv(argv);
		return (0);
}
/**
 * main - Fonction principale du programme shell.
 * @ac: Nombre d'arguments en ligne de commande.
 * @av: Arguments en ligne de commande.
 * @envp: Tableau des variables d'environnement.
 *
 * Return: 0 en cas de succès
 */
int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
		}
		if (execute_command(MAX_ARGUMENTS, envp) == -1)
		{
			break;
		}
		if (!isatty(STDIN_FILENO))
		{
			break;
		}
	}
	return (EXIT_SUCCESS);
}
