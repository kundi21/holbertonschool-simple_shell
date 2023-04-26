#include "shell.h"
#include "fork_wait_execve.c"

/**
 * main - function of getline
 *
 * On  success,
 * getline() and getdelim() return the number of characters read,
 * including the delimiter character,
 * but not including the terminating null byte ('\0').
 * This value can be used to handle embedded null bytes in the line read.
 *
 * Both functions return -1 on failure to read a line
 * (including end-of-file condition).
 * In the event of an error, errno is set to indicate the cause.
 *
 * Return: always 0, success.
 */

int main(void)
{
	char *buffer;
	size_t bufsize = 1024;
	size_t ret = 0;

	while (1)
	{
		printf("$ ");

		buffer = malloc(sizeof(char) * bufsize);

		ret = getline(&buffer, &bufsize, stdin);

		if (strcmp(buffer, "exit\n") == 0 || ret == -1)
		{
			printf("Bye\n");
			break;
		}

	printf("%s", buffer);
	free(buffer);
	}

	return (0);
}
