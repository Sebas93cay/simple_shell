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
	pid_t child_pid = 1;
	int status = 547, i;
	char *argv[] = {"/bin/ls", ".", NULL};

	for (i = 0; i < 5; i++)
	{
		printf("(%u)before fork i = %d\n", getpid(), i);
		/* if (child_pid != 0) */
		child_pid = fork();
		printf("(%u)after fork i = %d\n", getpid(), i);
		if (child_pid == -1)
		{
			perror("Child not created\n");
			return (1);
		}

		if (child_pid == 0)
		{
			printf("I'm child %u\n", getpid());
			sleep(1);
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve not executed\n");
				return (1);
			}
			/* break; */
		}
		else
		{
			wait(&status);
			printf("(%u) My son %u has finished his job\n", getpid(), child_pid);
		}
	}
	return (0);
}
