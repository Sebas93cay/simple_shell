#include "headershell.h"


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


int checkANDOR(free_chars_t *FC)
{
	int i = 0, tipo = 0;
	char *buff = NULL;
	

	buff = FC->buff;

	if (list_len_andor(FC->ANDORS) == 0)
	{
		for (; buff[i]; i++)
		{
			if (buff[i] == ' ')
				buff++;
			if (buff[i] == '&' && buff[i + 1] == '&')
			{
				if (i == 0)
				{
					_printf("Unexpected token &&");
					return (1);
				}
				else
				{
					add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
					tipo = 2;
					buff = buff + i + 2;
					i = 0;
				}
			}
			if (buff[i] == '|' && buff[i + 1] == '|')
			{
				if (i == 0)
				{
					_printf("Unexpected token &&");
					return (1);
				}
				else
				{
					add_node_n_end_andor(&FC->ANDORS, buff, i, tipo);
					tipo = 1;
					buff = buff + i + 2;
					i = 0;
				}
			}
		}
		if (i == 1)
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
	
}
