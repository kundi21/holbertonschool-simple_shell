#include "shell.h"

/**
 * print_path_dirs - prints each directory contained in the env var
 */

void print_path_dirs(void)
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

/**
 * main - calls function
 *
 * Return: always 0, success
 */

int main(void)
{
	printf("PATH=\n");

	print_path_dirs();

	return (0);
}
