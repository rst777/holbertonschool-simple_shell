#include "main.h"

void print_env(void)
{
	char **env;
	env = environ;

	while(*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
