#include "headershell.h"

int built_exit(free_chars_t *FC)
{
	int exit_status;

	if (FC->args[1] != NULL)
	{
		if (check_if_num(FC->args[1]) == 0)
		{
			exit_status = _atoi(FC->args[1]);
			TheExit(exit_status, FC);
		}
		else
		{
			_printf("%s: 1: exit: Illegal number: %s\n",
				*FC->argv, FC->args[1]);
			return (1);
		}
	}
	else
	{
		TheExit(0, FC);
	}
	return (0);
}
int built_cd(free_chars_t *FC)
{
	char *pwd = NULL, *oldpwd = NULL, *home;
	DIR *dir = NULL;
	int dirlen = 0;

	pwd = _strdup(_getenv("PWD"));
	oldpwd = _getenv("OLDPWD");
	if (oldpwd)
		oldpwd = _strdup(oldpwd);
	if (FC->args[1])
	{
		if (_strcmp(FC->args[1], "-") == 0)
		{
			change_WD(oldpwd, pwd);
			_printf("%s\n", oldpwd);
		}
		else if (FC->args[1][0] == '/')
		{
			dir = opendir(FC->args[1]);
			if (dir)
			{
				dirlen = _strlen(FC->args[1]);
				if (FC->args[1][dirlen - 1] == '/' && dirlen > 1)
					FC->args[1][dirlen - 1] = 0;
				change_WD(FC->args[1], pwd);
				closedir(dir);
			}
			else if (errno == ENOENT)
				_printf("%s: 1: can't cd to %s\n", FC->argv[0], FC->args[1]);
		}
	}
	else
	{
		home = _getenv("HOME");
		chdir(home);
		_setenv("PWD", home, 1);
		_setenv("OLDPWD", pwd, 1);
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


int built_env(free_chars_t *FC, int mode)
{
	switch (mode)
	{
	case 0:
		_printenv();
		break;
	case 1:
		_setenv(FC->args[1], FC->args[2], 1);
		break;
	case 2:
		_unsetenv(FC->args[1]);
		break;
	}
	return (1);
}

