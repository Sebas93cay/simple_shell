#include "headershell.h"

/**
 * _getline - gets line from stdin
 * @FC: string structure.
 * @buffsize: buffer's size
 * Return: return pointer to variable's value
 */
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
			remove_last_character(FC->buff, '\n');
			return (i);
		}
		FC->buff = _realloc(FC->buff, i, i + extra_read + 1);
		*buffsize = i + extra_read + 1;
	}
	do {
		read_size = (i != 0) ? (int) *buffsize - 1 - i : read_size;
		bytes = read(STDIN_FILENO, FC->buff + i, read_size);
		keepreading = 0;
		i += bytes;
		if (bytes == read_size && check_if_line(FC->buff, i) == 0)
		{

			FC->buff = _realloc(FC->buff, *buffsize, *buffsize + extra_read);
			*buffsize += extra_read;
			keepreading = 1;
		}

	} while (keepreading);
	FC->buff[i] = 0;
	singly_split_words(FC->buff, &FC->lines, '\n');
	free(FC->buff),	FC->buff = NULL;
	FC->buff = pop_list(&FC->lines);
	remove_last_character(FC->buff, '\n');
	if (i > 0)
		return (i);
	return (EOF);
}

/**
 * check_if_character - check if buff has character c in the first n bytes
 * if n is cero, checks the buffer until a null character is found
 * @buff: buffer
 * @n: n
 * @c: character
 * Return: retunt 1 if character c appears, 0 otherwise
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

/**
 * remove_last_character - remove last character on buff
 * if the last character is c
 * @buff: buffer
 * @c: character
 */
void remove_last_character(char *buff, char c)
{
	int len;

	if (buff == NULL)
		return;

	len = _strlen(buff);
	if (buff[len - 1] == c)
		buff[len - 1] = '\0';

}

/**
 * check_if_not_commands - check if buff has anything different than just
 * blank spaces
 * @buff: buffer
 * Return: return 0 if has a command, 1 if there is no command
 */
int check_if_not_commands(char *buff)
{
	if (buff == NULL || *buff == 0)
		return (1);
	while (*buff)
	{
		if (*buff != ' ')
			return (0);
		buff++;
	}
	return (1);
}

/**
 * check_if_line - check if buff has a whole line with a '\n'
 * character at the end in the first n characters.
 * @buff: buffer
 * @n: n
 * Return: return 1 if there is a whole line, 0 otherwise
 */
int check_if_line(char *buff, int n)
{
	int full_line = 0, i = 0;

	if (buff == NULL || *buff == 0)
		return (0);
	while ((buff[i] == '\n' || buff[i] == ' ') && i < n)
		i++;
	if (i == n)
		return (0);
	while (i < n)
	{
		if (buff[i] == '\n')
		{
			full_line = 1;
			break;
		}
		i++;
	}
	return (full_line);
}
