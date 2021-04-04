#include "headershell.h"

ssize_t _getline(char **buff, size_t *buffsize)
{
	int bytes;
	int i = 0;
	ssize_t read_size = *buffsize - 1; /*Save 1 byte for null character*/
	int len, keepreading = 0;

	static list_t *lines;

	*buff = _realloc(*buff, 0, *buffsize);

	if (list_len(lines) == 0)
	{
		i = 0;
		do {
			bytes = read(STDIN_FILENO, *buff + i, read_size);

			keepreading = 0;
			if (bytes == read_size && check_newline(*buff, bytes) == 0
			    && *((*buff + i) + bytes - 1) != '\n')
			{
				*buff = _realloc(*buff, *buffsize, *buffsize + read_size);
				*buffsize += read_size;
				keepreading = 1;
			}
			i += bytes;
		} while (keepreading);
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
