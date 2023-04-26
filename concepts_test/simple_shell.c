#include "shell.h"
#include "_getenv.c"


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
		/*getenv para pasarle como 3er parametro al execve*/
		
		/* falta fork y arreglar execve*/
		
		execve(tokens[0], tokens, envp);
		
		free(buffer);
	}
	return (0);
}