#include <stdio.h>

/**
 * main - prints all arguments
 * @ac: the number of arguments.
 * @av: an array of strings that contains the arg.
 * Return: 0.
 */
int main(int ac, char **av)
{
	int i = 0;

	while (av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}

	return (0);
}
