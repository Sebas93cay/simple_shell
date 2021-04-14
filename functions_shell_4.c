#include "headershell.h"


/**
 *  checkANDOR - split buffer in commands separated for tokens
 * && and ||. It assings a type tipo to each command being
 * tipo = 0 for the first command
 * tipo = 1 for commands after a || token
 * tipo = 2 for commands after a && token
 * @FC: string structure
 * Return: 1 if no command is going to be executed, 0 otherwise
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
			_printf(1, "> ");
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

/**
 * check_andor_logic - check if next command should be executed
 * according if the previous command was succesfull or not.
 * If commands is tipo 1, it should be executed if previous command
 * was unsuccesfull, if it is tipo 2, it should be the oposite.
 * The command that should be executed is pointed by FC->buff
 * @FC: string structure
 * Return: if a command that should be executed is found, a 0 is
 * returned, otherwise, a 1 is returned
 */
int check_andor_logic(free_chars_t *FC)
{
	int tipo;

	if (list_len_andor(FC->ANDORS) == 0)
	{
		return (1);
	}

	tipo = FC->ANDORS->tipo;

	FC->buff = pop_andor(&FC->ANDORS);
	if ((tipo == 1 && FC->last_command_result == 0) ||
	    (tipo == 2 && FC->last_command_result == 1))
	{
		return (check_andor_logic(FC));
	}
	return (0);
}


/**
 * join_lines - joing the first two nodes in the linked list lines
 * in the first node and removes the second node.
 * @lines: linked list
 * Return: pointer to linked list;
*/
list_t *join_lines(list_t **lines)
{

	if (lines == NULL || *lines == NULL)
		return (NULL);
	if ((*lines)->next == NULL)
		return (*lines);

	(*lines)->str = _strncat(1, (*lines)->str, (*lines)->next->str);
	(*lines)->len = _strlen((*lines)->str);

	delete_node_at_index(lines, 1);
	return (*lines);
}
