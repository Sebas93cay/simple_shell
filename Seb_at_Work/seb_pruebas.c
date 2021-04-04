#include "../headershell.h"


int main(int argc, char **argv, char **env)
{

	FILE *stream;

	stream = stdin;

	printf("el puntero : %p\n", stream->_IO_read_ptr);
	printf("el puntero : %p\n", stdin->_IO_read_ptr);



	


	return (0);
}
