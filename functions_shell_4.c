#include "headershell.h"

/**
 * check_errors
 */
int check_errors(free_chars_t *FC)
{
	if (check_no_commands_inbetween(FC) == 1)
		return (1);
	if (check_if_need_more_read(FC) == 1)
		return (1);
	return (0);
}

int check_no_commands_inbetween(free_chars_t *FC)
{
	int hascommand = 0;
	char *buff = FC->buff;
	int i = 0;

	while(*buff)
	{
		hascommand = 0;
		while(buff[i] != ';'&&
		      !(buff[i] == '|' && buff[i + 1] == '|') &&
		      !(buff[i] == '&' && buff[i + 1] == '&') &&
		      buff[i] != '\0')
		{
			if (buff[i] != ' ')
				hascommand = 1;
			i++;
		}
		if (hascommand || buff[i] == '\0')
		{
			if (buff[i] == ';')
				buff += i + 1;
			else if((buff[i] == '|' && buff[i + 1] == '|')||
				(buff[i] == '&' && buff[i + 1] == '&'))
				buff += i + 2;
			else
				buff += i;
			i = 0;
		}
		else
		{
			if (buff[i] == ';')
				_printf("Error ';' not expected\n");
			else if (buff[i] == '|' && buff[i + 1] == '|')
				_printf("Unexpected token ||\n");
			else if	(buff[i] == '&' && buff[i + 1] == '&')
				_printf("Unexpected token &&\n");
			free_list(FC->commands), FC->commands = NULL;
			free(FC->buff), FC->buff = NULL;
			free_list(FC->lines), FC->lines = NULL;
			if (isatty(0))
			{
				return (1);
			}
			else
			{
				free_words(environ);
				exit (2);
			}

		}
	}
	return (0);
}

int check_if_need_more_read(free_chars_t *FC)
{
	char *buff = FC->buff;
	int i = 0;

	while (buff[i])
	{
		if ((buff[i] == '&' && buff[i + 1] == '&') ||
		    (buff[i] == '|' && buff[i + 1] == '|'))
		{
			buff += i + 2;
			i = 0;
		}
		i++;
	}
	if (check_if_not_commands(buff))
	{
		if (isatty(0))
			_printf("> ");
		add_node(&FC->lines, FC->buff);
		FC->need_to_readnextline = 1;
		return (1);
	}
	return (0);
}
