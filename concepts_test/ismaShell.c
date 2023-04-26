#include "shell.h"


/**
 * main - sistem
 * 
 * @argc: argument
 *
 * @argv: argument
 *
 * @envp: environ
 *
 * Return: always (0) success;
 */

int main(int argc, char *argv[], char *envp[])
{
	char *buffer = NULL;
	size_t bufsize = 0;
	size_t ret = 0;
	char *token;
	char **tokens = NULL;
	int token_count = 0;

	while (1)
	{
		if(isatty(STDIN_FILENO) == 1)
			printf("$ ");

		buffer = malloc(sizeof(char) * bufsize);

		ret = getline(&buffer, &bufsize, stdin);

		if (ret == -1)
		{
			if (feof(stdin))
			{
				printf("Bye\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		token_count = 0;
		token = strtok(buffer, " \n");
		tokens = malloc(sizeof(char*));

		while (token)
		{
			tokens[token_count] = token;

			token = strtok(NULL, " \n");
		}
		/*Exits progrwm when user types "exit"*/
		if (strcmp(buffer, "exit\n") == 0 || ret == -1)
		{
			printf("Bye\n");
			break;
		}

		execve(tokens[0], tokens, * _getenv);

		free(buffer);
	}
	return (0);
}