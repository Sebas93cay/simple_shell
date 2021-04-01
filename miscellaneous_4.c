#include "headershell.h"

char *_getenv(const char *var)
{
	int len = _strlen((char *) var);
	char **env = environ;

	/* _printf("len = %d\n", len); */
	while (*env)
	{
		/* _printf("*env = %s\n", *env); */
		if (_strncmp(*env, (char *)var, len) == 0 &&
			env[0][len] == '=')
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


/*
 * _setenv does not work because environ is not an allocated variable
 * So it can be "reallocated"
*/
int _setenv(char *name, char *value, int overwrite)
{
	int len = _strlen((char *) name), size = 0;
	char **env = environ;
	int val_len = _strlen(value);
	char *tmpstr = NULL;

	/* _printf("_setenv---- &env = %p\n", &env); */
	/* _printf("_setenv &environ = %p\n", &environ); */
	/* _printf("Vamos a poner %s=%s\n", name, value); */
	for (size = 0; env[size]; size++)
	{
		_printf("env = %s\n", env[size]);
		if (_strncmp(env[size], name, len) == 0 && (*env)[len] == '=')
			break;
	}
	/* _printf("env = %s\n", env[size]); */
	if (env[size] == NULL)
	{
		/* _printf("_setenv &environ = %p\n", &environ); */
		environ = _realloc(environ, size + 1, size + 2);
		/* _printf("_setenv &environ = %p\n", &environ); */
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
