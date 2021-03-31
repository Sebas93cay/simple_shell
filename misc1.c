#include "headershell.h"

/**
 * _strcmp - compare first n bytes in two strings
 * @s1: string 1
 * @s2: string 2
 * @n: bytes to compare
 * Return: Returns 0 if strings are equal, otherwise
 * returns the difference
 */
int _strncmp(char *s1, char *s2, unsigned int n)
{
	int i = 0, diff = 0;

	do {
		diff = *(s1 + i) - *(s2 + i);
		i++;
	} while (diff == 0 && *(s1 + i) != 0 && *(s2 + i) != 0 && i < n);
	return (diff);
}

char *_getenv(const char *var)
{
	int len = _strlen((char *) var);
	char **env = environ;

	/* _printf("len = %d\n", len); */
	while (*env)
	{
		/* _printf("*env = %s\n", *env); */
		if (_strncmp(*env, (char *)var, len) == 0)
		{
			return (*env + len + 1);
		}
		env++;
	}
	return (NULL);
}

