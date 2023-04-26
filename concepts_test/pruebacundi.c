#include "shell.h"


/**
 * main - sistem
 */

int main(int argc, char *argv[], char *envp[])
{
	char *buffer;
	size_t bufsize = 1024;
	size_t ret = 0;
	int i = 0;
	char *token;
	char *tokens[64];
	int j = 0;

	for (j = 0; j < 64; j++)
	{
		tokens[j] = NULL;
	}

	while (1)
	{
		printf("$ ");

		buffer = malloc(sizeof(char) * bufsize);

		ret = getline(&buffer, &bufsize, stdin);
	
		token = strtok(buffer, " \n");
		while (token)
		{
			tokens[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}
		/*Exits progrwm when user types "exit"*/
		if (strcmp(buffer, "exit\n") == 0 || ret == -1)
		{
			printf("Bye\n");
			break;
		}
		/* falta fork y arreglar execve*/
		if (fork() == 0)
		{
		execve(tokens[0], tokens, envp);
		}
		wait(NULL);
		free(buffer);
	}
	return (0);
}
