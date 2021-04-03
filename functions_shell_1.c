#include "headershell.h"

void execve_not_working(char **args, char **argv, char *buff)
{
	/* _printf("(%u) liberaremos args[0]\n", getpid()); */

	free_words(args);
	free(buff);
	perror(argv[0]);

}

void check_inputs(char **buff, size_t *buffSize, char **args)
{
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/

	if (getline(buff, buffSize, stdin) == EOF)
		TheExit(0, *buff, args);

	buff[0][_strlen(buff[0]) - 1] = '\0'; /*Remove new line*/
	/* _printf("(%u) recibimos linea:\n%s\n", getpid(), *buff); */
}

void TheExit(int status, char *buff, char **args)
{
	if (isatty(0) && _strcmp(buff, "exit") != 0)
		write(1, "\n", 1); /*print only in terminal*/
	free(buff);
	free_words(args);
	_printf("salimos con = %d\n", status);
	exit(status);
}

void create_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		childError(child_pid);
	/* if (*child_pid != 0) */
	/* { */
	/* 	_printf("(%u) My son is alive, his name is %u\n", getpid(), *child_pid); */
	/* } */
	/* else */
	/* { */
	/* 	_printf("(%u) Yes! I'm alive! my father is %u\n", getpid(), getppid()); */
	/* } */
}

void childError(pid_t *child)
{
	_printf("Child %u not created\n", *child);
	exit(1);
}
