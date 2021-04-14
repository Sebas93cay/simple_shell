#include "headershell.h"

/**
 * _strlen - Get the lenght of a string
 * @s: string
 * Return: return length of a string
 */
int _strlen(char *s)
{
	int i = 0;

	if (s == NULL || *s == 0)
		return (0);

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
 * _strcpy - copy the first n bytes of src into dest
 * @dest: destination buffer
 * @src: source
 * Return: return pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (; *(src + i) != 0; i++)
		*(dest + i) = *(src + i);
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
	} while (diff == 0 && *(s1 + i - 1) != 0 && *(s2 + i - 1) != 0);
	return (diff);
}


/**
 * _strncmp - compare first n bytes in two strings
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


