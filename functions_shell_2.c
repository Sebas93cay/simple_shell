#include "headershell.h"

void __attribute__ ((constructor)) premain()
{
	environ = words_cpy(environ);
	signal(SIGINT, ignore_signal);
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
void check_semicolumns(free_chars_t *FC)
{
	if (list_len(FC->commands) == 0)
	{
		FC->commands = singly_split_words(FC->buff, &FC->commands, ';');
	}
	free(FC->buff), FC->buff = NULL;
	FC->buff = pop_list(&FC->commands);
	remove_character(FC->buff, ';');

}
