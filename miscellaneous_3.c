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
