#include "../headershell.h"


int main(int argc, char **argv, char **env)
{
	char *buff;
	size_t buffsize = 0;
	char **args = NULL;

	getline(&buff, &buffsize, stdin);

	printf("buff = %s\n", buff);

	free(buff);
	df

	return (0);
}
