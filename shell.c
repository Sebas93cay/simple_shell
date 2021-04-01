#include "headershell.h"



void childError(pid_t *child)
{
	_printf("Child %u not created\n", *child);
	exit(1);
}
int main(__attribute__ ((unused)) int argc,
	 __attribute__ ((unused)) char **argv,
	 __attribute__ ((unused)) char **env)
{
	size_t buffSize = 1;
	char *args[2];
	pid_t child_pid, executer_pid;
	int status;

	globalhijos = 0;
	args[0] = malloc(sizeof(*args[0]) * buffSize);
	args[1] = NULL;
	if (!args[0])
		perror(argv[0]);

	_printf("(%u)I'm the father jojojo\n", getpid());
	while (1)
	{
		if (isatty(0))
			_printf("#cisfun$ ");
		if (getline(&args[0], &buffSize, stdin) == EOF)
		{
			free(args[0]);
			write(1, "\n", 1);
			return (0);
		}
		args[0][_strlen(args[0]) - 1] = '\0'; /*Remove new line*/
		create_child(&child_pid);
		_printf("(%u)ya creamos nuestro primer hijo\n", getpid());
		if (child_pid == 0)
		{
			create_child(&executer_pid);
			if (executer_pid == 0)
			{
				if (execve(args[0], args, NULL) == -1)
					perror(argv[0]);
				break;
			}
			else
			{
				wait(&status);
				free(args[0]);
				_printf("(%u) liberamos args[0]\n", getpid());
				break;
			}
			_printf("(%u) salimos de if\n", getpid());
		}
		else
			wait(&status);
		_printf("(%u) salimos de if\n", getpid());
	}
	return (0);
}


void create_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		childError(child_pid);
	if (*child_pid != 0)
	{
		_printf("(%u) My son is alive, his name is %u\n", getpid(), *child_pid);
	}
	else
	{
		_printf("(%u) Yes! I'm alive! my father is %u\n", getpid(), getppid());
	}
}
