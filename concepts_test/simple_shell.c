#include "shell.h"

/**
 * main - sistem
 */
char* _getenv(const char* name)
{
        extern char **environ;
        int i;
        char *envp;

        for(i = 0; environ[i] != NULL; i++)
        {
                if(strstr(environ[i], name))
                {
                        envp = environ[i];
                        envp = strcpy(envp, environ[i]);
                }
                envp++;
        }
        return (envp);
}

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

int main(int argc, char *argv[], char *envp[])
{
	char *buffer, *token, *tokens[64];
	size_t bufsize = 1024, ret = 0;
	int i = 0, j = 0;

	while (1)
	{
		if(isatty(STDIN_FILENO) == 1)
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

		if (strcmp(buffer, "exit\n") == 0 || ret == -1)
		{
			printf("Bye\n");
			break;
		}

		tokens[i] = NULL;
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

		free(buffer);
		i = 0;
	}
	return (0);
}
