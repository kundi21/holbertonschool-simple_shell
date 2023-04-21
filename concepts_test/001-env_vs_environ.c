#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[], char *envp[])
{
	char **env = envp;

	while (*env != NULL)
	{
		env++;
	}

	printf("Address of envp: %p\n", &envp);
	printf("Address of the last environment variable: %p\n", env-1);

	char **environ_ptr = environ;

	printf("Address of environ: %p\n", &environ_ptr);
	printf("Address of the last environment variable: %p\n", *(environ_ptr + 1));

	return (0);
}
