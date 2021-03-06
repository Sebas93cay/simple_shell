#include "headershell.h"

/**
 * _getenv - gets enviroment variable name
 * @name: enviroment variable
 * Return: return pointer to variable's value
 * or NULL of failure
 */
char *_getenv(const char *name)
{
	int len = _strlen((char *) name);
	char **env = environ;

	/* _printf(1, "len = %d\n", len); */
	while (*env)
	{
		/* _printf("*env = %s\n", *env); */
		if (_strncmp(*env, (char *)name, len) == 0 &&
			env[0][len] == '=')
		{
			return (*env + len + 1);
		}
		env++;
	}
	return (NULL);
}

/**
 * _printenv - print enviroment
 * Return: nothing
 */
void _printenv(void)
{
	int i = 0;

	while (environ[i])
	{
		_printf(1, "%s\n", environ[i]);
		i++;
	}
}


/**
 * _setenv - sets enviroment variable name with value value
 * @name: enviroment variable
 * @value: value
 * @overwrite: overwrite variable is this argument is set
 * Return: return pointer to variable's value
 */
int _setenv(char *name, char *value, int overwrite)
{
	int len = _strlen((char *) name), size = 0;
	char **env = environ;
	int val_len = _strlen((char *)value);
	char *tmpstr = NULL;

	for (size = 0; env[size]; size++)
	{
		/* _printf("env = %s\n", env[size]); */
		if (_strncmp(env[size], name, len) == 0 && env[size][len] == '=')
			break;
	}
	/* _printf("env = %s\n", env[size]); */
	if (env[size] == NULL)
	{
		/* _printf("No habia esa variable\n"); */
		/* _printf("_setenv &environ = %p\n", &environ); */
		environ = _realloc(environ, sizeof(char *) * (size + 1),
			sizeof(char *) * (size + 2));
		if (environ == NULL)
			return (-1);
		/* _printf("_setenv &environ = %p\n", &environ); */
		environ[size + 1] = NULL;
		environ[size] = malloc(sizeof(**environ) *
					   (len + val_len + 2));
		tmpstr = _strncpy(environ[size], name, len);
		tmpstr = _strncpy(tmpstr + len, "=", 1);
		tmpstr = _strncpy(tmpstr + 1, value, val_len);
		tmpstr = _strncpy(tmpstr + val_len, "\0", 1);
	}
	else if (overwrite)
	{
		environ[size] = _realloc(environ[size], len + 1,
					 sizeof(char) * (len + val_len + 2));
		tmpstr = _strncpy(environ[size], name, len);
		tmpstr = _strncpy(tmpstr + len, "=", 1);
		tmpstr = _strncpy(tmpstr + 1, value, val_len);
		tmpstr = _strncpy(tmpstr + val_len, "\0", 1);
	}
	return (0);
}

/**
 * _unsetenv - unset enviroment variable name
 * @name: enviroment variable
 * Return: return always 0
 */
int _unsetenv(char *name)
{
	int len = _strlen((char *) name);
	char **env = environ;

	while (*env)
	{
		if (_strncmp(*env, name, len) == 0 &&
		    env[0][len] == '=')
		{
			free(env[0]);
			env[0] = env[1];
			break;
		}
		env++;
	}
	if (*env != NULL)
	{
		env++;
		while (*env)
		{
			env[0] = env[1];
			env++;
		}
	}
	return (0);
}


/**
 * words_cpy - copy an array of strings into an allocated
 * space of memory
 * @words: array of strings to copy
 * Return: pointer to allocated space with array copied
 */
char **words_cpy(char **words)
{
	int word_count, letter_count, i;
	char **ret = NULL;

	word_count = 0;
	while (words[word_count])
		word_count++;

	ret = malloc(sizeof(char *) * (word_count + 1));
	if (ret == NULL)
		return (NULL);

	ret[word_count] = NULL;

	for (i = 0; words[i]; i++)
	{
		letter_count = _strlen(words[i]);
		ret[i] = malloc(sizeof(char) * (letter_count + 1));
		if (ret[i] == NULL)
		{
			i--;
			for (; i >= 0; i--)
				free(ret[i]);
			free(ret);
			return (NULL);
		}
		ret[i] = _strcpy(ret[i], words[i]);
	}
	return (ret);
}
