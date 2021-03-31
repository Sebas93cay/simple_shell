#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
	extern char **environ;

	printf("----env located at %p\n", &env);
	printf("env[0] = %s\n", env[0]);
	printf("environ located at %p\n", &environ);
	printf("environ[0] = %s\n", environ[0]);
	return (0);
}
