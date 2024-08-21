#include "main.h"
/**
 * check_exit_command - if input command is exit, exit the program if true.
 * @buffer: The command input by the user.
 */
void check_exit_command(char *buffer)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		exit(0);
	}
}
