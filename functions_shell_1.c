#include "headershell.h"

void execve_not_working(free_chars_t *FC)
{
	/* _printf("(%u) liberaremos args[0]\n", getpid()); */

	free_words(FC->args);
	free(FC->buff);
	free_words(environ);
	perror(FC->argv[0]);

}

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

void create_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		childError(child_pid);
}

void childError(pid_t *child)
{
	_printf("Child %u not created\n", *child);
	exit(1);
}
