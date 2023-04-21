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

		printf("%s", buffer);

		if (strstr(buffer, "/bin/ls") != NULL)
		{
		for (i = 0; i < 5; i++)
		{
			if (fork() == 0)
			{
				execl("/bin/ls", "ls", "-l", "/tmp", NULL);
				return (0);
			}
			wait(NULL);
		}
		}

		free(buffer);
	}
	return (0);
}
