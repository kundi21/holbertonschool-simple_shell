#include "shell.h"

/**
 * tokenize - function to tokenize a string
 *
 * @input: string to be tokenized
 *
 * Return: array of tokens
 */

char **tokenize(char **input)
{
	char **tokens = malloc(sizeof(char *) * 64);
	char *token;
	int i = 0;

	if (tokens == NULL)
	{
		perror("Error");
		return (NULL);
	}

	token = strtok(*input, " \n");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}
	tokens[i] = NULL;
	return (tokens);
}

