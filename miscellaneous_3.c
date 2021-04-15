#include "headershell.h"

/**
 * splitargs_list - split FC->buff arguments and store them in
 * the linked list FC->args_l.
 * @FC: string structure.
 * Return: pointer to FC->args_l
 */
list_t *splitargs_list(free_chars_t *FC)
{
	int letters = 0;
	char *buff = FC->buff;
	int saving = 0;
	list_t *last_node = NULL;
	char quote;

	free_list(&FC->args_l);

	while (*buff)
	{
		while (*buff == ' ')
			buff++;
		letters = 0;

		while (buff[letters] != 0 && buff[letters] != ' ')
		{
			if (buff[letters] == '\'' || buff[letters] == '\"')
			{
				quote = buff[letters];
				save_arg(FC, &buff, &last_node, &letters, &saving,  0);
				buff++;
				while (buff[letters] != quote)
					letters++;
				save_arg(FC, &buff, &last_node, &letters, &saving, 1);
				buff++;
				if (*buff == ' ')
					saving = 0;
				if (*buff == 0)
					break;
				continue;
			}
			letters++;
		}
		if (*buff == 0)
			break;
		save_arg(FC, &buff, &last_node, &letters, &saving, 0);
		if (*buff == ' ')
			saving = 0;
	}
	return (FC->args_l);
}


/**
 * save_arg - saves part of an argument
 * @FC: string structure.
 * @buff: buff
 * @last_node: pointer to last node in linked_list
 * @letters: letters readed in piece to add to argument
 * @saving: flag, if it's 1 it means that we are saving in an
 * already created node.
 * @force: force to save argument even if it does not have anything
 * Return: array of pointers pointing to strings in FC->args_l
 */
void save_arg(free_chars_t *FC, char **buff, list_t **last_node,
	      int *letters, int *saving, int force)
{
	if ((*letters > 0 && *saving == 0) || (force && *saving == 0))
	{
		*last_node = add_node_n_end(&FC->args_l, *buff, *letters);
		*saving = 1;
	}
	else if ((*letters > 0 && *saving == 1) || (force && *saving == 1))
	{
		(*last_node)->str = _strcatn((*last_node)->str, *buff, *letters);
		(*last_node)->len += *letters;
	}
	*buff += *letters;
	*letters = 0;
}


/**
 * pointto_words_list - make a null terminated array of strings pointing
 * to the strings in the linked list FC->args_l
 * @FC: string structure.
 * Return: array of pointers pointing to strings in FC->args_l
 */
char **pointto_words_list(free_chars_t *FC)
{
	int args_n = list_len(FC->args_l);
	int i = 0;
	list_t *node = FC->args_l;

	if (args_n == 0)
		return (NULL);
	free(FC->args);
	FC->args = malloc(sizeof(char *) * (args_n + 1));
	if (FC->args == NULL)
		return (NULL);

	while (i < args_n)
	{
		FC->args[i] = node->str;
		node = node->next;
		i++;
	}
	FC->args[i] = NULL;
	return (FC->args);
}

/**
 * splitwords - split buff in an array of strings, the split is done with
 * the strings between the character token
 * @buff: string to split
 * @token: character to split buff
 * Return: array of strings
 */
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


/**
 * free_words - free array of strings
 * @args: array of string to free
 * Return: nothing
 */
void free_words(char **args)
{
	int i = 0;

	if (args == NULL)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}



