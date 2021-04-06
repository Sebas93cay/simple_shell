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
