#include "main.h"

/**
 * find_command_path - Find the full path of a command using PATH environment variable.
 * @command: The command to find.
 *
 * Return: The full path of the command or NULL if not found.
 */
char *find_command_path(const char *command)
{
	char *path_env, *path_copy, *directory, *full_path;

	if (command == NULL)
	{
		return (NULL);
	}

	if (command[0] == '/' && access(command, X_OK) == 0)
	{/**  Check if the command is already an absolute path*/
		return (strdup(command));
	}

	path_env = my_getenv("PATH");/**Get PATH environment variable*/
	if (path_env == NULL)
	{
		return (NULL); /** PATH not found*/
	}

	path_copy = strdup(path_env);	/** Duplicate PATH variable to manipulate it*/
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	full_path = malloc(1024); /**Allocate memory for the full path*/
	if (full_path == NULL)
	{
		perror("malloc");
		free(path_copy);
		return (NULL);
	}
	directory = strtok(path_copy, ":"); /** Tokenize PATH variable and search for the command*/
	
	while (directory != NULL)
	{
		snprintf(full_path, 1024, "%s/%s", directory, command); /** Build the full path*/

		if (access(full_path, X_OK) == 0)/**Check if the file exists and is executable*/
		{
			free(path_copy);
			return (full_path);
		}
		directory = strtok(NULL, ":"); /**  Get the next directory in PATH*/
	}
	free(full_path); /**Clean up and return NULL if not found*/
	free(path_copy);
	return (NULL);
}
