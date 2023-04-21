#include <string.h>
#include <stddef.h>
/**
 *
 */

size_t _strlen(const char *s)
{
	size_t count = 0;

	while (*s != '\0')
	{
		count++;
		s++;
	}

	return (count);
}

/**
 *
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return ((s1[i] < s2[i]) ? -1 : 1);
		}
		if (s1[i] == '\0')
		{
			return (0);
		}
	}

	return (0);
}


