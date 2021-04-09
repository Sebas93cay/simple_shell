#include "../headershell.h"


int main(int argc, char **argv, char **env)
{
	struct stat st;

	chdir("/bin/");
	printf("%d y %d\n", stat("hola", &st), stat("./ls", &st));

	char *args[] = {"/bin/./ls", NULL};

	execve(args[0], args, NULL);
	


	return (0);
}
