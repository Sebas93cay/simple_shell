#include "headershell.h"

/**
 * built_exit - exit built-in. It exits the shell
 * @FC: string structure.
 * Return: return 1 if exit was unsucesfull
 */
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
			_printf(2, "%s: %d: exit: Illegal number: %s\n",
				*FC->argv, FC->line_count, FC->args[1]);
			if (!isatty(0))
				TheExit(2, FC);
			return (1);
		}
	}
	else
	{
		TheExit(0, FC);
	}
	return (0);
}
/**
 * built_cd - change directory built-in.
 * @FC: string structure.
 * Return: return 1
 */

int built_cd(free_chars_t *FC)
{
	char *pwd = NULL, *oldpwd = NULL, *home;

	pwd = _strdup(_getenv("PWD"));
	oldpwd = _getenv("OLDPWD");
	if (oldpwd)
		oldpwd = _strdup(oldpwd);
	if (FC->args[1])
	{
		cd_to(FC, oldpwd, pwd);
	}
	else
	{
		home = _getenv("HOME");
		chdir(home);
		_setenv("PWD", home, 1);
		_setenv("OLDPWD", pwd, 1);
		FC->last_command_result = 0;
	}
	free(oldpwd);
	free(pwd);
	return (1);
}

/**
 * cd_to - change directory to specific directory, this function is
 * used when something is tiped after cd by the user.
 * @FC: string structure.
 * @oldpwd: enviroment variable OLDPWD value
 * @pwd: enviroment variable PWD value
 * Rerturn: nothing
 */
void cd_to(free_chars_t *FC, char *oldpwd, char *pwd)
{
	DIR *dir = NULL;
	int dirlen = 0;

	if (_strcmp(FC->args[1], "-") == 0)
	{
		change_WD(oldpwd, pwd);
		_printf(1, "%s\n", oldpwd);
		FC->last_command_result = 0;
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
			FC->last_command_result = 0;
		}
		else if (errno == ENOENT)
		{
			_printf(1, "%s: %d: can't cd to %s\n", FC->argv[0],
				FC->line_count, FC->args[1]);
			FC->last_command_result = 1;
		}
	}
}


/**
 * built_env - enviroment built in
 * @FC: string structure.
 * @mode: defines if the built is goint to print the enviroment (mode = 0),
 * set a new enviroment variable (mode = 1) or delete anviroment varaible
 * (mode = 2)
 * Return: return 1
 */
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
	FC->last_command_result = 0;
	return (1);
}

/**
 * built_print_aliases - print all the alias saved in a linked list
 * @head: pointer to first node of the list
 * Return: return 1
 */
int built_print_aliases(alias *head)
{
	if (head == NULL)
		return (1);
	_printf(1, "alias %s='%s'\n", head->name, head->value);
	return (built_print_aliases(head->next));
}
