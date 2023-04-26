#include "shell.h"

/**
 * print_path_dirs() - prints each directory contained in the env var
 */

void print_path_dirs()
{
	char *path = _getenv("PATH");

	if (path != NULL)
	{
		char *dir = strtok(path, ":");

		while (dir != NULL)
		{
			printf("%s\n", dir);
			dir = strtok(NULL, ":");
		}
	}
}

int main()
{
	printf("PATH=\n");

	print_path_dirs();

	return (0);
}
