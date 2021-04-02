#include "../headershell.h"


int main(int argc, char **argv, char **env)
{
	char buff[1000];
	FILE *stream;
	char *searcher = NULL;

	stream = stdin;

	read(0, buff, 2);
	write(1, buff, 2);
	write(1, "-Que cosas-", 11);
	read(0, buff, 2);
	write(1, buff, 2);



	searcher = memchr((void *)(stdin->_IO_read_ptr), 's', 100);
	printf("searcher = %p\n", searcher);
	printf("read_ptr = %p\n", (void *)stdin->_IO_read_ptr);
	printf("read_end = %p\n", stdin->_IO_read_end);
	return (0);
}
