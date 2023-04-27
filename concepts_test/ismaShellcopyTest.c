#include "shell.h"


/**
 * main - sistem
 */

int main(void)
{
	char *buffer;
	size_t bufsize = 1024;
	size_t ret = 0;
	int i = 0;

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

		processes_inputs(buffer);

		free(buffer);
	}
	return (0);
}

void processes_inputs(char *buffer)
{
	if (strstr(buffer, "/bin/ls\n") != NULL)
	{
		if (fork() == 0)
		{
			execl("/bin/ls", "ls", ".", NULL);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
	else if (strstr(buffer, "l\n") != NULL)
	{
		if (fork() == 0)
		{
			execl("/bin/ls", "ls", "-l", ".", NULL);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
	else
	{
		printf("%s", buffer);
	}
}
