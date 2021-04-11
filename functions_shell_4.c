#include "headershell.h"


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
			if (buff[i] == '|' && buff[i + 1] == '|')
			{
				add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
				tipo = 1;
				buff += i + 2;
				i = 0;
				continue;
			}
			if (buff[i] == '&' && buff[i + 1] == '&')
			{
				add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
				tipo = 2;
				buff += i + 2;
				i = 0;
				continue;
			}
			i++;
		}
		if (check_if_not_commands(buff))
		{
			_printf("> ");
			FC->need_to_readnextline = 1;
			return (1);
		}
		else
		{
			add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
		}
	}	
	free(FC->buff), FC->buff = NULL;

	return (check_andor_logic(FC));
}

int check_andor_logic(free_chars_t *FC)
{
	int tipo = FC->ANDORS->tipo;

	if (list_len_andor(FC->ANDORS) == 0)
	{
		return (1);
	}

	FC->buff = pop_andor(&FC->ANDORS);
	if ((tipo == 1 && FC->last_command_result == 0) ||
	    (tipo == 2 && FC->last_command_result == 1))
	{
		return (check_andor_logic(FC));
	}
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
		if (!isatty(0))
			join_lines(&FC->lines);
		return (1);
	}
	return (0);
}

list_t *join_lines(list_t **lines)
{

	if(lines == NULL || *lines == NULL)
		return (NULL);
	if((*lines)->next == NULL)
		return (*lines);

	(*lines)->str = _strncat(1, (*lines)->str, (*lines)->next->str);
	(*lines)->len = _strlen((*lines)->str);

	delete_node_at_index(lines, 1);
	return (*lines);
}
