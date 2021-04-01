#include "headershell.h"

/**
 * _strlen - Get the lenght of a string
 * @s: string
 * Return: return length of a string
 */
int _strlen(char *s)
{
	int i = 0;

	while (*(s + i))
		i++;

	return (i);
}

/**
 * _strncpy - copy the first n bytes of src into dest
 * @dest: destination buffer
 * @src: source
 * @n: number of bytes to be copyed
 * Return: return pointer to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	for (; i < n && *(src + i) != 0; i++)
		*(dest + i) = *(src + i);
	for (; i < n; i++)
		*(dest + i) = 0;

	return (dest);
}


/**
 * _strcmp - compare first n bytes in two strings
 * @s1: string 1
 * @s2: string 2
 * Return: Returns 0 if strings are equal, otherwise
 * returns the difference
 */
int _strcmp(char *s1, char *s2)
{
	int diff = 0;
	unsigned int i = 0;

	do {
		diff = *(s1 + i) - *(s2 + i);
		i++;
	} while (diff == 0 && *(s1 + i) != 0 && *(s2 + i) != 0);
	return (diff);
}


/**
 * _strcmp - compare first n bytes in two strings
 * @s1: string 1
 * @s2: string 2
 * @n: bytes to compare
 * Return: Returns 0 if strings are equal, otherwise
 * returns the difference
 */
int _strncmp(char *s1, char *s2, unsigned int n)
{
	int diff = 0;
	unsigned int i = 0;

	do {
		diff = *(s1 + i) - *(s2 + i);
		i++;
	} while (diff == 0 && *(s1 + i) != 0 && *(s2 + i) != 0 && i < n);
	return (diff);
}


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
	for (; *buff && i < wordcount; buff++)
	{
		while (*buff == token)
			buff++;
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
