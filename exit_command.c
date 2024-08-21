#include "main.h"
/**
 * check_exit_command - if input command is exit, exit the program if true.
 * @buffer: The command input by the user.
 */
void check_exit_command(char *buffer)
{
	char *command = buffer; /**Début de la chaîne de commande */
	int exit_code = 0;		/** Code de sortie par défaut */

	/** Supprimer les espaces en début */
	while (*command == ' ')
	{
		command++;
	}
	/** Supprimer les espaces en fin */
	char *end = command + strlen(command) - 1;
	while (end > command && *end == ' ')
	{
		end--;
	}
	/** Terminer la chaîne */
	end[1] = '\0';

	/** Vérifier si la commande est "exit" */
	if (strncmp(command, "exit", 4) == 0 && (command[4] == '\0' || command[4] == ' '))
	{
		/** Lire et utiliser le code de sortie s'il est présent */
		if (command[4] != '\0')
		{
			exit_code = atoi(command + 4);
		}

		/** Libérer la mémoire et quitter */
		free(buffer);
		exit(exit_code);
	}
}
