#include <stdio.h>
#include <stdlib.h>
/**
 *
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t bufsize = 0;
	int i = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
			printf("$ ");
			fflush(stdout);
			printf("%s", line);
	}

	free(line);
	return (0);
}
