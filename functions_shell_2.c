#include "headershell.h"

/**
 * premain - function to run before the main is run
 * Return: nothing
 */
void __attribute__ ((constructor)) premain(void)
{
	environ = words_cpy(environ);
	/* signal(SIGINT, ignore_signal); */
}


/**
 * ignore_signal - singal handler, ignore the signal
 * @sig: singal to ingore
 * Return: nothing
 */
void ignore_signal(int sig)
{
	write(1, "\n", 1);
	if (isatty(0))
		_printf(1, "$ "); /*print only in terminal*/
	signal(sig, SIG_IGN);
	signal(sig, ignore_signal);
}


/**
 * check_semicolons - check if there is ';' in the line to execute
 * and separate those commands
 * @FC: string structure
 * Return: always return 0
 */
int check_semicolons(free_chars_t *FC)
{
	if (list_len(FC->commands) == 0)
	{
		if (check_if_character(FC->buff, 0, ';') == 1)
		{
			split_semicolons(FC);
		}
		else
			return (0);
	}
	free(FC->buff), FC->buff = NULL;
	FC->buff = pop_list(&FC->commands);
	remove_last_character(FC->buff, ';');

	return (0);
}


/**
 * split_semicolons - split FC->buff in commands separated by ';'
 * character. These commands are storaged in the linked list FC->commands
 * @FC: string structure
 * Return: nothing
 */
void split_semicolons(free_chars_t *FC)
{
	int hascommand = 0;
	char *buff = FC->buff;
	int i = 0;

	while (*buff)
	{
		hascommand = 0;
		while (buff[i] != ';' && buff[i] != '\0')
		{
			if (buff[i] != ' ')
				hascommand = 1;
			i++;
		}
		if (hascommand || buff[i] == '\0')
		{
			add_node_n_end(&FC->commands, buff, i);
			buff += (buff[i] == ';') ? i + 1 : i;
			i = 0;
		}
	}
}


/**
 * putPath - puth the path before the command concatenated in a
 * new allocated memory, command memory is freed
 * @command: string with command
 * @path: string with path
 * Return: pointer to new allocated memory with the full path
 */
char *putPath(char *command, char *path)
{
	int command_len = _strlen(command);
	int path_len = _strlen(path);
	char tmp_command[100];

	_strncpy(tmp_command, command, command_len);
	tmp_command[command_len] = '\0';

	command = _realloc(command, command_len,
			   command_len + path_len + 1);
	if (command == NULL)
	{
		exit(1);
	}

	_strncpy(command, path, path_len);
	_strncpy(command + path_len, "/", 1);
	_strncpy(command + path_len + 1, tmp_command, command_len);
	command[command_len + path_len + 1] = '\0';

	return (command);
}

