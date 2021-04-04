#include "headershell.h"

char **splitwords(char *buff, char token)
{
	int i, wordcount = 0, letters = 0;
	char **words = NULL;


	if (buff == NULL || *buff == 0)
		return (NULL);
	for (i = 0; buff[i]; i++)
	{
		if (buff[i] != token && (buff[i + 1] == token
			   || buff[i + 1] == '\0'))
			wordcount++;
	}
	if (wordcount > 0)
		words = malloc(sizeof(*words) * (wordcount + 1));
	if (words == NULL)
		return (NULL);
	i = 0;
	for (; *buff && i < wordcount;)
	{
		while (*buff == token)
			buff++;
		letters = 0;
		while (buff[letters] != 0 && buff[letters] != token)
			letters++;
		words[i] = malloc(sizeof(char) * (letters + 1));
		_strncpy(words[i], buff, letters);
		words[i][letters] = '\0';
		buff += letters;
		i++;
	}
	words[i] = NULL;
	/* _printf("Final de splitwords\n"); */
	return (words);
}

void free_words(char **args)
{
	int i = 0;

	if (args == NULL)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

void print_words(char **words)
{
	while (*words)
	{
		_printf("-> %s\n", *words);
		words++;
	}
}

int check_if_num(char *num)
{
	while (*num)
	{
		if (*num < '0' || *num > '9')
			return (-1);
		num++;
	}
	return (0);
}



ssize_t _getline(char **buff, size_t *buffsize)
{
	int bytes;
	int i = 0;
	ssize_t read_size = *buffsize - 1; /*Save 1 byte for null character*/
	int len, keepreading = 0, terminal = isatty(0);

	static list_t *lines;

	*buff = _realloc(*buff, 0, *buffsize);

	if (list_len(lines) == 0)
	{
		i = 0;
		do {
			bytes = read(STDIN_FILENO, *buff + i, read_size);

			keepreading = 0;
			if (bytes == read_size && *((*buff + i) + bytes - 1) != '\n' &&
				terminal)
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
