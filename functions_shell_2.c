#include "headershell.h"

void __attribute__ ((constructor)) premain()
{
	environ = words_cpy(environ);
	/* signal(SIGINT, ignore_signal); */
}


/**
 * ignore_signal - singal handler, ignore the signal
 */
void ignore_signal(int sig)
{
	write(1, "\n", 1);
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/
	signal(sig, SIG_IGN);
	signal(sig, ignore_signal);
}


/**
 * check_semicolumns - check if there is ';' in the line to execute
 *  and separate those commands
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


int split_semicolons(free_chars_t *FC)
{
	int hascommand = 0;
	char *buff = FC->buff;
	int i = 0;

	while(*buff)
	{
		hascommand = 0;
		while(buff[i] != ';' && buff[i] != '\0')
		{
			if (buff[i] != ' ')
				hascommand = 1;
			i++;
		}
		if (hascommand || buff[i] == '\0')
		{
			add_node_n_end(&FC->commands, buff, i);
			buff += (buff[i] == ';')? i + 1 : i;
			i = 0;
		}
		else
		{
			_printf("Error ';' not expected\n");
			return (1);
		}
				
	}
	return (0);
}


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

