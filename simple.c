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
	char *buffer = NULL, *tokens[64];
	size_t bufsize = 0;
	ssize_t ret = 0;
	int i = 0;
	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			printf("$ ");
			fflush(stdout);
		}

		ret = getline(&buffer, &bufsize, stdin);

		if (ret == -1 || buffer == NULL)
		{
			free(buffer);
			buffer = NULL;
			break;
		}

		for (i = 0; (tokens[i] = strtok(buffer, " \n")); i++)
			buffer = NULL;

		if (strcmp(tokens[0], "exit") == 0)
		{
			free(buffer);
			free(*tokens);
			exit(EXIT_SUCCESS);
		}

		tokens[i] = NULL;

		processes(tokens, envp);
		free(tokens[0]);

		if (buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}

		bufsize = 0;
		free(buffer);
		buffer = NULL;
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
		free(tokens);
		return (EXIT_FAILURE);
	}

	if (pid == 0)
	{
		_execvp(tokens[0], tokens, envp);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else 
	{
		free(tokens);
		return (EXIT_FAILURE);
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
	char *path_token, *cmd_path = NULL;

	if (cmd[0] == '/')
	{
		execve(cmd, args, envp);
		perror(cmd);
		exit(127);
	}

	while ((path_token = strtok(path_env, ":")) != NULL)
	{
		cmd_path = malloc(strlen(path_token) + strlen(cmd) + 2);
		
		if (cmd_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		sprintf(cmd_path, "%s/%s", path_token, cmd);

		if (execve(cmd_path, args, envp) == -1)
		{
			free(cmd_path);
			cmd_path = NULL;
			path_env = NULL;
			continue;
		}
		else
		{
			free(cmd_path);
			free(path_env);
			return;
		}
	}
	if (cmd_path != NULL)
		free(cmd_path);

	fprintf(stderr, "%s: No such file or directory\n", args[0]);
	free(path_env);
	exit(EXIT_FAILURE);
}
