#include "../headershell.h"


int main(int argc, char **argv, char **env)
{
	char *buff;
	size_t buffsize = 0;
	char **args = NULL;

	FILE *stream;

	stream = stdin;

	printf("el puntero : %p\n", stream->_IO_read_ptr);
	printf("el puntero : %p\n", stdin->_IO_read_ptr);



	free(buff);


	return (0);
}
