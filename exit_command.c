#include "main.h"
/**
 * check_exit_command - Check if the input command is "exit" and exit the program if true.
 * @buffer: The command input by the user.
 */
void check_exit_command(char *buffer)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		exit(0); // Quitter le programme
	}
}
