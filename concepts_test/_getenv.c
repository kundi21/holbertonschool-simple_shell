#include "shell.h"
/**
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
*/
