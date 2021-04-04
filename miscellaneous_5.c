#include "headershell.h"

ssize_t _getline(char **buff, size_t *buffsize)
{
	int bytes;
	int i = 0;
	ssize_t read_size = *buffsize - 1; /*Save 1 byte for null character*/
	ssize_t extra_read = BUFFSIZE -1;
	int len, keepreading = 0;

	static list_t *lines;

	*buff = _realloc(*buff, 0, *buffsize);

	_printf("numero de lineas guardadas = %d\n", list_len(lines));
	if (list_len(lines) == 0)
	{
		i = 0;
		do {
			read_size = (i == 0) ? read_size : extra_read;
			bytes = read(STDIN_FILENO, *buff + i, read_size);
			_printf("bytes readed = %d\n", bytes);
			_printf("buff despues de leer =");
			write(1, *buff, i + bytes);
			write(1, "\n", 1);
			keepreading = 0;
			if (bytes == read_size && check_newline(*buff + i, bytes) == 0
			    && *(*buff + i + bytes - 1) != '\n')				
			{
				_printf("Segimos leyendo\n");
				*buff = _realloc(*buff, *buffsize, *buffsize + extra_read);
				*buffsize += extra_read;
				keepreading = 1;
			}
			_printf("Vamos a sumarle a i, en este momento i = %d y bytes = %d\n", i, bytes);
			i += bytes;
			_printf("Ahora i = %d\n", i);
		} while (keepreading);
		_printf("Terminamos de leer, en total fueron %d bytes\n", i);
		_printf("Tamaño del buffer = %d\n", *buffsize);
		buff[0][i] = 0;
		len = _strlen(buff[0]);
		if (buff[0][len - 1] == '\n')
			buff[0][len - 1] = '\0'; /*Remove new line*/
		_printf("buff = %s\n", *buff);
		singly_split_words(*buff, &lines, '\n');
		free(*buff);
		*buff = pop_list(&lines);
		if (i > 0)
			return (i);
		return (EOF);
	}
	free(*buff);
	i = lines->len;
	*buff = pop_list(&lines);
	return (i);
}


int check_newline(char *buff, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		if (buff[i] == '\n')
			return (1);
	}
	return (0);
}
