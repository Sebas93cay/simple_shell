#include "headershell.h"

ssize_t _getline(free_chars_t *FC, size_t *buffsize)
{
	int bytes;
	int i = 0;
	ssize_t read_size = *buffsize - 1; /*Save 1 byte for null character*/
	ssize_t extra_read = BUFFSIZE -1;
	int  keepreading = 0;


	FC->buff = _realloc(FC->buff, 0, *buffsize);

	/* _printf("numero de lineas guardadas = %d\n", list_len(lines)); */
	if (list_len(FC->lines) != 0)
	{
		free(FC->buff);
		i = FC->lines->len;
		FC->buff = pop_list(&FC->lines);
		if (FC->buff[i - 1] == '\n')
		{
			remove_newline(FC->buff);
			_printf("buuf antes de salir = %s\n", FC->buff);
			return (i);
		}
		i = i - 1; /*We were counting the null character when split words*/
		FC->buff = _realloc(FC->buff, i, i + extra_read + 1);
		*buffsize = i + extra_read + 1;

	}

	do {
		if (i != 0)
			read_size = *buffsize - 1 - i;

		bytes = read(STDIN_FILENO, FC->buff + i, read_size);
		/* _printf("bytes readed = %d\n", bytes); */
		/* _printf("buff despues de leer ="); */
		/* write(1, *buff, i + bytes); */
		/* write(1, "\n", 1); */
		keepreading = 0;
		if (bytes == read_size && check_newline(FC->buff + i, bytes) == 0
		    && *(FC->buff + i + bytes - 1) != '\n')				
		{
			/* _printf("Segimos leyendo\n"); */
			FC->buff = _realloc(FC->buff, *buffsize, *buffsize + extra_read);
			*buffsize += extra_read;
			keepreading = 1;
		}
		/* _printf("Vamos a sumarle a i, en este momento i = %d y bytes = %d\n", i, bytes); */
		i += bytes;
		/* _printf("Ahora i = %d\n", i); */
	} while (keepreading);
	/* _printf("Terminamos de leer, en total fueron %d bytes\n", i); */
	/* _printf("Tamaño del buffer = %d\n", *buffsize); */
	FC->buff[i] = 0;
	/* _printf("buff = %s\n", *buff); */
	singly_split_words(FC->buff, &FC->lines, '\n');
	free(FC->buff);
	FC->buff = NULL;
	FC->buff = pop_list(&FC->lines);
	remove_newline(FC->buff);
	if (i > 0)
		return (i);
	return (EOF);
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


void remove_newline(char *buff)
{
	int len;

	if (buff == NULL)
		return;

	len = _strlen(buff);
	if (buff[len - 1] == '\n')
		buff[len - 1] = '\0'; /*Remove new line*/

}
