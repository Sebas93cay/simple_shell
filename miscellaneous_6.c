#include "headershell.h"

int check_if_num(char *num)
{
	while (*num)
	{
		if (*num < '0' || *num > '9')
			return (-1);
		num++;
	}
	return (0);
}


/**
 * _strcatn - concatenate first n bytes from src after dest
 */
char *_strcatn(char *dest, char *src, int n)
{
	int dest_len;

	if (dest == NULL)
		return (NULL);

	dest_len = _strlen(dest);

	dest = _realloc(dest, dest_len, dest_len + n + 1);

	_strncpy(dest + dest_len, src, n);

	dest[dest_len + n] = '\0';

	return (dest);
}


void print_words(char **words)
{
	while (*words)
	{
		_printf("-> %s\n", *words);
		words++;
	}
}

void change_WD(char *newpwd, char *pwd)
{
	chdir(newpwd);
	_setenv("PWD", newpwd, 1);
	_setenv("OLDPWD", pwd, 1);
}
