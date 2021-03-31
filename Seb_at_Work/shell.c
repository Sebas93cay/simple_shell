#include "../headershell.h"

void childError(pid_t *child)
{
	_printf("Child %u not created\n", *child);
	exit(1);
}
int main(void)
{
	size_t buffSize = 1;
	char *args[2];
	pid_t child_pid;
	int status;

	args[0] = malloc(sizeof(*args[0]) * buffSize);
	args[1] = NULL;
	if (!args[0])
		printf("Error, buff were not able to initialize");

	while (1)
	{
		_printf("#cisfun$ ");
		getline(&args[0], &buffSize, stdin);
		args[0][_strlen(args[0]) - 1] = '\0'; /*Remove new line*/
		child_pid = fork();
		if (child_pid == -1)
			childError(&child_pid);
		if (child_pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
				perror("Error:");
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
