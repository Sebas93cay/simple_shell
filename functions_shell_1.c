#include "headershell.h"

/**
 * check_full_path - check if command has the full path, if not looks
 * for the directory in the PATH where commands is and add the full path
 * to args[0]
 */
void check_full_path(char **args)
{
	char *path = _getenv("PATH"), *command = NULL;
	/* char **dirs = NULL; */
	list_t *dirs = NULL, *dir = NULL;
	char *cwd = NULL, *tmp_ptr = NULL;
	struct stat st;

	cwd = _getenv("PWD");
	if (args[0][0] == '.' && args[0][1] == '/')
	{
		if(stat(*args + 2, &st) == 0)
		{
			command = _strdup(*args + 2);
			free(args[0]);
			args[0] = _strdup(cwd);
			args[0] = _strncat(2, args[0], "/", command);
			free(command);
		}
	}
	else if (args[0][0] != '/')
	{
		singly_split_words(path, &dirs, ':');
		dir = dirs;

		while (dir)
		{
			remove_last_character(dir->str, ':');

			chdir(dir->str);

			if (stat(*args, &st) == 0)
			{
				chdir(cwd);
				break;
			}

			dir = dir->next;
		}

		if (dir != NULL)
		{
			tmp_ptr = dir->str;
			dir->str = args[0];
			args[0] = tmp_ptr;
			args[0] = _strncat(2, args[0], "/", dir->str);
		}

	}
	free_list(dirs);
}


/**
 * execve_not_working - frees all strings in FC and shows error message
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
 */

void TheExit(int status, free_chars_t *FC)
{
	if (isatty(0) && _strcmp(FC->buff, "exit") != 0)
		write(1, "\n", 1); /*print only in terminal*/
	free(FC->buff);
	free_words(FC->args);
	free_words(environ);
	free_list(FC->lines);
	exit(status);
}


/**
 * create_child - create a child
 */
void create_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
	{
		_printf("Child not created\n");
		exit(1);
	}
}

/**
 *  checkANDOR - split buffer in commands separated for tokens
 * && and ||. It assings a type tipo to each command being
 * tipo = 0 for the first command
 * tipo = 1 for commands after a || token
 * tipo = 2 for commands after a && token
 */
int checkANDOR(free_chars_t *FC)
{
	int i = 0, tipo = 0;
	char *buff = NULL;

	buff = FC->buff;

	if (list_len_andor(FC->ANDORS) == 0)
	{
		while (buff[i])
		{
			if (buff[i] == ' ' && i <= 1)
				buff++;
			else if (buff[i] == '|' && buff[i + 1] == '|')
			{
				if (i == 0)
				{
					_printf("Unexpected token ||\n");
					free_list(FC->commands), FC->commands = NULL;
					free(FC->buff), FC->buff = NULL;
					if (isatty(0))
					{
						return (1);
					}
					else
					{
						free_list(FC->lines), FC->lines = NULL;
						free_words(environ);
						exit (2);
					}
				}
				else
				{
					add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
					tipo = 1;
					buff = buff + i + 2;
					i = 0;
				}
			}
			else if (buff[i] == '&' && buff[i + 1] == '&')
			{
				if (i == 0)
				{
					_printf("Unexpected token &&\n");
					free_list(FC->commands), FC->commands = NULL;
					free(FC->buff), FC->buff = NULL;
					if (isatty(0))
					{
						return (1);
					}
					else
					{
						free_list(FC->lines), FC->lines = NULL;
						free_words(environ);
						exit (2);
					}
				}
				else
				{
					add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
					tipo = 2;
					buff = buff + i + 2;
					i = 0;
				}
			}
			else
				i++;
		}
		if (*buff == 0)
		{
			_printf("Debemos seguir leyendo\n");
		}
		else
		{
			add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
		}
	}
	free(FC->buff), FC->buff = NULL;
	FC->buff = pop_andor(&FC->ANDORS);

	return (0);
}
