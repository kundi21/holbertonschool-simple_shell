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
	int i = 0;
	char *buffer = NULL,  *tokens[64] = {NULL};
	size_t bufsize = 0;
	ssize_t ret = 0;
	(void)argc, (void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ "), fflush(stdout);

		ret = getline(&buffer, &bufsize, stdin);
		if (ret == -1 || buffer == NULL)
			free(buffer), buffer = NULL, exit(EXIT_FAILURE);

		for (i = 0; (tokens[i] = strtok(buffer, " \n")); i++)
			buffer = NULL;

		if (tokens[0] != NULL && strcmp(tokens[0], "exit") == 0)
		{
			free(buffer);
			buffer = NULL;
			free(tokens[i]);
			tokens[i] = NULL;
			free(*tokens);
			exit(EXIT_SUCCESS);
		}

		tokens[i] = NULL;
		processes(tokens, envp);
		free(tokens[0]);

		free(buffer), buffer = NULL, bufsize = 0;
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
		perror("fork");
		free(tokens);
		exit(EXIT_FAILURE);
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
	size_t len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
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
	char *path_copy = strdup(path_env);
	char *path_token = NULL, *cmd_path = NULL, *new_path_copy = NULL;

	if (cmd[0] == '/')
	{
		if (execve(cmd, args, envp) == -1)
		{
			perror(cmd);
			free(path_env), free(path_copy), exit(127);
		}
	}

	new_path_copy = malloc(strlen(path_copy) + 3);
	if (new_path_copy == NULL)
	{
		perror("malloc");
		free(path_copy), free(path_env), exit(EXIT_FAILURE);
	}

	sprintf(new_path_copy, ".:%s", path_copy);
	free(path_copy);
	path_copy = new_path_copy;
	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		cmd_path = malloc(strlen(path_token) + strlen(cmd) + 2);

		if (cmd_path == NULL)
		{
			perror("malloc");
			free(path_copy), free(path_env), exit(EXIT_FAILURE);
		}

		sprintf(cmd_path, "%s/%s", path_token, cmd);

		execve(cmd_path, args, envp);
		free(cmd_path), cmd_path = NULL;
		path_token = strtok(NULL, ":");
	}
	if (cmd_path != NULL)
		free(cmd_path);
	fprintf(stderr, "%s: %s: No such command file or directory\n", args[0], cmd);
	free(path_copy), free(path_env), free(cmd_path);
	exit(EXIT_FAILURE);
}
