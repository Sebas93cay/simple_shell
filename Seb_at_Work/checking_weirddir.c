#include "../headershell.h"


int main(int argc, char **argv, char **env)
{
	struct stat st;

//if (stat("/tmp/.ICE-unix", &st) == 0)
	if (stat("/tmp", &st) == 0)
	{
		printf("Esta\n");
	}
	else
		printf("No esta\n");
	return (0);
}
