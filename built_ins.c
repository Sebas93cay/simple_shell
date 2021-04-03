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

int built_cd(char **args, char *buff, char **argv)
{
	char *pwd, *oldpwd, *home;

	pwd = _getenv("PWD");
	oldpwd = _getenv("OLDPWD");

	if (args[1])
	{
		
	}
	else
	{
		home = _getenv("HOME");
		chdir(home);
		_setenv("PWD", home, 1);
		_setenv("OLDPWD", pwd, 1);
	}
	return (1);
}
