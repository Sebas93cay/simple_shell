#include "headershell.h"

/**
 * check_full_path - check if command has the full path, if not looks
 * for the directory in the PATH or same folder, if command is found
 * add the full path to begining of args[0]
 * @args: array of string containing the arguments given by the user
 * Return: nothing
 */
void check_full_path(char **args, free_chars_t *FC)
{
	char *path = _getenv("PATH"), *command = NULL, *cwd = NULL;
	/* char **dirs = NULL; */
	list_t *dirs = NULL, *dir = NULL;
	struct stat st;

	if (path == NULL)
		return;
	cwd = _getenv("PWD");
	if (args[0][0] == '.' && args[0][1] == '/')
	{
		if (stat(*args + 2, &st) == 0)
		{
			command = _strdup(*args + 2);
			FC->full_command = _strdup(cwd);
			FC->full_command = _strncat(2, FC->full_command, "/", command);
			free(command);
		}
	}
	else if (args[0][0] != '/')
	{
		singly_split_words(path, &dirs, ':');
		dir = dirs;
		while (dir)
		{
			remove_last_character(dir->str, ':'), chdir(dir->str);
			if (stat(*args, &st) == 0)
			{
				chdir(cwd);
				break;
			}
			dir = dir->next;
		}
		if (dir != NULL)
		{
			FC->full_command = _strdup(dir->str);
			FC->full_command = _strncat(2, FC->full_command, "/", args[0]);
		}
	}
	free_list(&dirs);
}


/**
 * execve_not_working - frees all strings in FC and shows error message
 * @FC: string structure.
 */
void execve_not_working(free_chars_t *FC)
{
	/* _printf("(%u) liberaremos args[0]\n", getpid()); */

	free_words(FC->args);
	free(FC->buff);
	free_words(environ);
	perror(FC->argv[0]);

}

/**
 * TheExit - free all strings in FC and exit program with status value
 * @status: status to exit
 * @FC: string structure.
 */
void TheExit(int status, free_chars_t *FC)
{
	if (isatty(0) && _strcmp(FC->buff, "exit") != 0)
		write(1, "\n", 1); /*print only in terminal*/
	free(FC->buff);
	free(FC->args);
	free_list(&FC->args_l);
	free_words(environ);
	free_list(&FC->lines);
	free_list(&FC->commands);
	exit(status);
}


/**
 * create_child - create a child
 * @child_pid: pointer to child pid
 * Return: nothing
 */
void create_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
	{
		_printf(2, "Child not created\n");
		exit(1);
	}
}


/**
 * check_errors - check errors in line just readed in FC->buff
 * @FC: string structure.
 * Return: 0 if not error was detected, 1 if an error was detected
 */
int check_errors(free_chars_t *FC)
{
	if (check_no_commands_inbetween(FC) == 1)
		return (1);
	if (check_if_need_more_read_logic(FC) == 1)
		return (1);
	return (0);
}
