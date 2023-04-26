#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * On  success,  getline() and getdelim() return the number of characters read, including the delimiter character,
 * but not including the terminating null byte ('\0').  This value can be used to handle embedded null bytes in the line read.
 *
 * Both functions return -1 on failure to read a line (including end-of-file condition).  
 * In the event of an error, errno is set to indicate the cause.
 */
int main (void)
{
	char *buffer;
	size_t bufsize = 1024;
	size_t ret = 0;
	char *token;
	char *tokens[64];
	int i = 0;
	int j = 0;


	for (j = 0; j < 64; j++){
		tokens[j] = NULL;
	}

	printf("$ ");

	buffer = malloc(sizeof(char) * bufsize);

	ret = getline(&buffer, &bufsize, stdin);


	   /* get the first token */
	token = strtok(buffer, " \n");

	   /* walk through other tokens */
	while (token)
	{
		tokens[i] = token;
		token = strtok(NULL, " \n");
		i++;	
	}

	for (j = 0; tokens[j]; j++){
		printf("[%d]: %s\n", j, tokens[j]);
	}

	return (0);
}
