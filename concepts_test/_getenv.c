#include "shell.h"
<<<<<<< HEAD

/**
 * _getenv - function
 */

=======
/**
>>>>>>> cb2dadfe67fa8dde8b43db052497c2b16e31a7ab
char* _getenv(const char* name)
{
	extern char **environ;
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
<<<<<<< HEAD
=======
*/
>>>>>>> cb2dadfe67fa8dde8b43db052497c2b16e31a7ab
