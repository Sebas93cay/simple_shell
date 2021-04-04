#include "headershell.h"

void execve_not_working(char **args, char **argv, char *buff)
{
	/* _printf("(%u) liberaremos args[0]\n", getpid()); */

	free_words(args);
	free(buff);
	free_words(environ);
	perror(argv[0]);

}

void TheExit(int status, char *buff, char **args)
{
	if (isatty(0) && _strcmp(buff, "exit") != 0)
		write(1, "\n", 1); /*print only in terminal*/
	free(buff);
	free_words(args);
	free_words(environ);
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
