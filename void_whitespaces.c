#include "main.h"

/**
 * trim_spaces - delete white spaces
 * @str: string to manage
 */

void skip_spaces(char *str)
{
	char *dest = str;
	char *src = str;

	/** delete white spaces befor arguments */
	while (*src == ' ')
		src++;

/** delete white spaces after arguments */
	while (*src)
	{
		/** copie the argument */
		if (*src != ' ' || (src > str && *(src - 1) != ' '))
			*dest++ = *src;
		src++;
	}

	/** add end charachtére */
	*dest = '\0';
}
