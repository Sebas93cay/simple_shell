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
	pid_t child_pid;
	int status = 547;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		printf("childi status 1 = %p - >%d\n", (void *)&status, status);
		printf("Wait for me, wait for me\n");
		sleep(2);
		printf("childi status 2 = %p - >%d\n", (void *)&status, status);
	}
	else
	{
		printf("father status 1 = %p - >%d\n", (void *)&status, status);
		wait(&status);
		printf("father status 2 = %p - >%d\n", (void *)&status, status);
		printf("Oh, it's all better now\n");
	}
	return (0);
}
