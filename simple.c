#include "shell.h"

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
	size_t bufsize = 512;
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
			free(buffer);
			break;
		}

		tokens[i] = NULL;

		if (tokens[0] != NULL)
			processes(tokens, envp);

		free(buffer);
		buffer = NULL;
		i = 0;
		memset(tokens, 0, sizeof(tokens));
	}
	return (0);
}

/**
 * processes - which we need to use the shell comand line
 *
 * @tokens: the ones that uses the comand line to separate the string
 * @envp: environ
 *
 * Return: different cases for the comand line inputs
 */

int processes(char **tokens, char **envp)
{
	pid_t pid;
		
	pid = fork();

	if (pid == -1)
	{
		return (-1);
	}

	if (pid == 0)
	{
		_execvp(tokens[0], tokens, envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

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
	char *envp = NULL;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, strlen(name)) == 0)
		{
			envp = strdup(environ[i] + strlen(name) + 1);
			return (envp);
		}
	}
	free(envp);
	return (NULL);
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

	if (cmd[0] == '/')
	{
		execve(cmd, args, envp);
		perror(cmd);
		exit(127);
	}

	while (path_token != NULL)
	{
		char *cmd_path = malloc(strlen(path_token) + strlen(cmd) + 2);

		sprintf(cmd_path, "%s/%s", path_token, cmd);

		execve(cmd_path, args, envp);

		free(cmd_path);
		path_token = strtok(NULL, ":");
	}
	free(path_env);
	exit(1);
}
