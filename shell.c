#include "headershell.h"



int main(__attribute__ ((unused)) int argc,
	 __attribute__ ((unused)) char **argv,
	 __attribute__ ((unused)) char **env)
{
	size_t buffSize = 1;
	char *buff = NULL;
	char *args[2];
	pid_t child_pid;
	int status;

	args[1] = NULL;
	/* _printf("(%u)I'm the father jojojo\n", getpid()); */
	while (1)
	{
		check_exits(&buff, &buffSize);
		args[0] = buff;
		if (**args == '\0')
			continue;
		create_child(&child_pid);
		/* _printf("(%u)ya creamos nuestro primer hijo\n", getpid()); */
		if (child_pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
				execve_not_working(args, argv);
			break;
		}
		else
		{
			wait(&status);
		}
		/* _printf("(%u) salimos de if\n", getpid()); */
	}
	return (0);
}

void execve_not_working(char **args, char **argv)
{
	/* _printf("(%u) liberaremos args[0]\n", getpid()); */
	free(args[0]);
	perror(argv[0]);
}

void check_exits(char **args, size_t *buffSize)
{
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/
	if (getline(args, buffSize, stdin) == EOF
	    || _strcmp(args[0], "exit") == 0)
	{
		if (isatty(0) && _strcmp(args[0], "exit") != 0)
			write(1, "\n", 1); /*print only in terminal*/
		free(args[0]);
		exit(0);
	}
	/* _printf("(%u) recibimos linea\n", getpid()); */
	args[0][_strlen(args[0]) - 1] = '\0'; /*Remove new line*/
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
