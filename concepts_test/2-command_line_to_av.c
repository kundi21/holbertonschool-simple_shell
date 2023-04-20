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

	printf("$ ");

	buffer = malloc(sizeof(char) * bufsize);

	ret = getline(&buffer, &bufsize, stdin);


	   /* get the first token */
	token = strtok(buffer, " \n");

	   /* walk through other tokens */
	while (token)
	{
		printf( " %s\n", token );
		token = strtok(NULL, " \n");
	}

	return (0);
}
