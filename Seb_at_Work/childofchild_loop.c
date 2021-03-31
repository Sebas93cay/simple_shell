#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid, grand_child_pid;
	int status = 547;

	printf("(%u)I'm the father, my father is %u\n", getpid(), getppid());
	
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	for (i = 0; i < 3; i++)
	{
		if (child_pid == 0)
		{
			printf("(%u)I'm a son, my father is %u\n", getpid(), getppid());
			grand_child_pid = fork();
			if (grand_child_pid == -1)
			{
				perror("Error:");
				return (1);
			}
			if (grand_child_pid == 0)
			{
				printf("(%u)I'm a son, my father is %u\n", getpid(), getppid());
			}
			else
			{
				wait(&status);
				printf("(%u) I'm the child\n", getpid());
			}
		}
		else
		{
			wait(&status);
			printf("(%u) I'm the father\n", getpid());
		}
	}
	
	return (0);
}
