#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;
	pid_t pid;
	pid_t elmio;

	elmio = getpid();
	printf("elmio = %u\n", elmio);

	printf("Before fork\n");
	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}
	printf("After fork\n");
	printf("elmio = %u\n", elmio);
	my_pid = getpid();
	printf("My pid is %u\n", my_pid);
	return (0);
}
