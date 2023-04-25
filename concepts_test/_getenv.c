#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern char **environ;

char *main(char *pathname)
{
	int i;
	char *envp;

	for(i = 0; environ[i] != NULL; i++)
	{
		if(strstr(environ[i], pathname))
		{
			envp = environ[i];
			envp = strcpy(envp, environ[i]);
		}
	}
	return (envp);
}
