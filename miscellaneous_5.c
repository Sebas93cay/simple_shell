#include "headershell.h"

ssize_t _getline(free_chars_t *FC, int *buffsize)
{
	int bytes, i = 0, keepreading = 0;
	ssize_t read_size = *buffsize - 1, extra_read = BUFFSIZE - 1;

	FC->buff = _realloc(FC->buff, 0, *buffsize);
	if (list_len(FC->lines) != 0)
	{
		free(FC->buff);
		i = FC->lines->len;
		FC->buff = pop_list(&FC->lines);
		if (FC->buff[i - 1] == '\n')
		{
			remove_character(FC->buff, '\n');
			return (i);
		}
		FC->buff = _realloc(FC->buff, i, i + extra_read + 1);
		*buffsize = i + extra_read + 1;
	}
	do {
		read_size = (i != 0) ? (int) *buffsize - 1 - i : read_size;
		bytes = read(STDIN_FILENO, FC->buff + i, read_size);
		keepreading = 0;
		if (bytes == read_size && check_if_character(FC->buff + i, bytes, '\n') == 0
		    && *(FC->buff + i + bytes - 1) != '\n')
		{

			FC->buff = _realloc(FC->buff, *buffsize, *buffsize + extra_read);
			*buffsize += extra_read;
			keepreading = 1;
		}
		i += bytes;
	} while (keepreading);
	FC->buff[i] = 0;
	singly_split_words(FC->buff, &FC->lines, '\n');
	free(FC->buff),	FC->buff = NULL;
	FC->buff = pop_list(&FC->lines);
	remove_character(FC->buff, '\n');
	if (i > 0)
		return (i);
	return (EOF);
}

/**
 * check_if_character - check if buff has character c in the first n bytes
 * if n is cero, checks the buffer until a null character is found
 */
int check_if_character(char *buff, int n, char c)
{
	int i = 0;

	if (n > 0)
	{
		for (i = 0; i < n; i++)
		{
			if (buff[i] == c)
				return (1);
		}
	}
	else
	{
		for (i = 0; buff[i]; i++)
		{
			if (buff[i] == c)
				return (1);
		}
	}
	return (0);
}


void remove_character(char *buff, char c)
{
	int len;

	if (buff == NULL)
		return;

	len = _strlen(buff);
	if (buff[len - 1] == c)
		buff[len - 1] = '\0';

}

int check_if_only_spaces(char *buff)
{
	while (*buff)
	{
		if (*buff != ' ')
			return (0);
		buff++;
	}
	return (1);
}
