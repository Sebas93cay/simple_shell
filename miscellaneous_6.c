#include "headershell.h"

/**
 * check_if_num - check if buffer num, only contains numbers
 * @num: buffer
 * Return: return 0 if only number appears, -1 otherwise
 */
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
 * @dest: destination
 * @src: string to copy
 * @n: n
 * Return: string with both strings concatenated
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

/**
 * print_words - print array of strings
 * @words: array of strings
 * Return: nothing
 */
void print_words(char **words)
{
	while (*words)
	{
		_printf("-> %s\n", *words);
		words++;
	}
}

/**
 * change_WD - change working directory
 * @newpwd: new working directory to setenv
 * @pwd: working directory at the time.
 * Return: nothing
 */
void change_WD(char *newpwd, char *pwd)
{
	chdir(newpwd);
	_setenv("PWD", newpwd, 1);
	_setenv("OLDPWD", pwd, 1);
}
