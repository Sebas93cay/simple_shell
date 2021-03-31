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

void _printenv(void)
{
	int i = 0;

	while (environ[i])
	{
		_printf("%s\n", environ[i]);
		i++;
	}
}

int _setenv(char *name, char *value, int overwrite)
{
	int len = _strlen((char *) name), size = 0;
	char **env = environ;
	int val_len = _strlen(value);
	char *tmpstr = NULL;

	_printf("_setenv---- &env = %p\n", &env);
	_printf("_setenv &environ = %p\n", &environ);
	_printf("Vamos a poner %s=%s\n", name, value);
	for (size = 0; env[size]; size++)
	{
		if (_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			break;
	}
	if (*env == NULL)
	{
		environ = _realloc(environ, size + 1, size + 2);
		environ[size + 2] = NULL;
		environ[size + 1] = malloc(sizeof(**environ) *
					   (len + val_len + 2));
		tmpstr = _strncpy(environ[size + 1], name, len);
		tmpstr = _strncpy(tmpstr + len, "=", 1);
		tmpstr = _strncpy(tmpstr + 1, value, val_len);
		tmpstr = _strncpy(tmpstr + val_len, "\0", 1);
	}
	else if (overwrite)
	{
		environ[size] = malloc(sizeof(*(environ[size])) * (len + val_len + 2));
		tmpstr = _strncpy(environ[size], name, len);
		tmpstr = _strncpy(tmpstr + len, "=", 1);
		tmpstr = _strncpy(tmpstr + 1, value, val_len);
		tmpstr = _strncpy(tmpstr + val_len, "\0", 1);
	}
	return (0);
}
