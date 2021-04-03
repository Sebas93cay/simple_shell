#include "headershell.h"

int built_exit(char **args, char *buff, char **argv)
{
	int exit_status;

	if (args[1] != NULL)
	{
		if (check_if_num(args[1]) == 0)
		{
			exit_status = _atoi(args[1]);
			TheExit(exit_status, buff, args);
		}
		else
		{
			_printf("%s: 1: exit: Illegal number: %s\n",
				*argv, args[1]);
			return (1);
		}
	}
	else
	{
		TheExit(0, buff, args);
	}
	return (0);
}
int built_cd(char **args, char **argv)
{
	char *pwd, *oldpwd, *home;
	DIR *dir = NULL;
	int dirlen = 0;

	pwd = _strdup(_getenv("PWD"));
	oldpwd = _strdup(_getenv("OLDPWD"));
	if (args[1])
	{
		if (_strcmp(args[1], "-") == 0)
			change_WD(oldpwd, pwd);

		else if (args[1][0] == '/')
		{
			dir = opendir(args[1]);
			if (dir)
			{
				dirlen = _strlen(args[1]);
				if (args[1][dirlen - 1] == '/')
					args[1][dirlen - 1] = 0;
				change_WD(args[1], pwd);
				closedir(dir);
			}
			else if (errno == ENOENT)
				_printf("%s: 1: can't cd to %s\n", argv[0], args[1]);
		}
	}
	else
	{
		home = _getenv("HOME");
		chdir(home);
		_setenv("PWD", home, 1);
		_setenv("OLDPWD", oldpwd, 1);
	}
	free(oldpwd);
	free(pwd);
	return (1);
}


void change_WD(char *newpwd, char *pwd)
{
	chdir(newpwd);
	_setenv("PWD", newpwd, 1);
	_setenv("OLDPWD", pwd, 1);
}


int built_env(__attribute__ ((unused)) char **args)
{
	_printenv();
	return (1);
}

