#include "shell.h"

/**
 * _getenv - function to get the environment
 *
 * @name: of the string
 *
 * Return: the pointer to the environment variable
 */

char *_getenv(const char *name)
{
	int i;
	char *envp;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strstr(environ[i], name))
		{
			envp = environ[i];
			envp = strcpy(envp, environ[i]);
		}
		envp++;
	}
	return (envp);
}

/**
 * _execvp - the function to find specific comands at the bin directory
 *
 * @cmd: comand
 *
 * @args: argument
 *
 * @envp: environ
 */

void _execvp(char *cmd, char **args, char **envp)
{
	char *path_env = _getenv("PATH");
	char *path_token = strtok(path_env, ":");

	while (path_token != NULL)
	{
		char *cmd_path = malloc(strlen(path_token) + strlen(cmd) + 2);

		sprintf(cmd_path, "%s/%s", path_token, cmd);

		execve(cmd_path, args, envp);

		free(cmd_path);
		path_token = strtok(NULL, ":");
	}
	fprintf(stderr, "%s: command not found\n", cmd);
	exit(1);
}

/**
 * main - the main function of the simple shell
 *
 * @argc: argument
 *
 * @argv: argument
 *
 * @envp: environ
 *
 * Return: always 0, success.
 */

int main(int argc, char *argv[], char *envp[])
{
	char *buffer = NULL, *token, *tokens[64];
	size_t bufsize = 1024;
	ssize_t ret = 0;
	int i = 0;
	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
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

		if (ret == -1)
		{
			free(stderr);
			free(buffer);
			break;
		}

		tokens[i] = NULL;
		processes(tokens, envp);

		free(buffer);
		i = 0;
	}
	return (0);
}

/**
 * processes - which we need to use the shell comand line
 *
 * @tokens: the ones that uses the comand line to separate the string
 *
 * @envp: environ
 *
 * Return: different cases for the comand line inputs
 */

int processes(char **tokens, char **envp)
{
	int pid = fork();

	if (pid == 0)
	{
		_execvp(tokens[0], tokens, envp);
		perror("execve");
		exit(1);
	}
	else if (pid == -1)
		perror("fork");
	else
		wait(NULL);

	return (0);
}
