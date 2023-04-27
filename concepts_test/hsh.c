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
 * @av: command
 *
 * @envp: environ
 *
 * Return: success.
 */

char *_execvp(char *av[], char **envp)
{
	char *path_env = _getenv("PATH");
	char *path_token = strtok(path_env, ":");
	char *cmd = av[0];
	char *cmd_path;

	while (path_token != NULL)
	{
		cmd_path = malloc(strlen(path_token) + strlen(cmd) + 2);
		sprintf(cmd_path, "%s/%s", path_token, cmd);
		path_token = strtok(NULL, ":");
		if (access(cmd_path, F_OK) == 0)
		{
			execve(cmd_path, av, envp);
			free(cmd_path);
			free(path_env);
			return (NULL);
		}
		free(cmd_path);
	}

	free(path_env);
	return (NULL);
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

	buffer = malloc(bufsize);
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");

		ret = getline(&buffer, &bufsize, stdin);
		if (ret == -1)
		{
			free(buffer);
			break;
		}

		i = 0;
		token = strtok(buffer, " \n");
		while (token)
		{
			if (strcmp(buffer, "exit") == 0)
			{
				free(buffer);
				exit(EXIT_SUCCESS);
			}
			tokens[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}

		tokens[i] = NULL;
		processes(tokens, envp);
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

void processes(char **commands, char **envp)
{
	char **tokens;
	char *path;
	pid_t pid;
	int status;

	tokens = tokenize(commands);
	path = _execvp(tokens, envp);

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
	}

	if (pid == 0)
	{
		if (path == NULL)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		execve(path, tokens, envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(tokens);
	free(path);
}
