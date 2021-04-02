#include "headershell.h"

/**
 * _realloc - eallocates a memory block using malloc and free
 * The contents will be copied to the newly allocated space,
 * in the range from the start of ptr up to the minimum of
 * the old and new sizes
 * Description: If new_size > old_size, the “added” memory
 * should not be initialized.
 * If new_size == old_size do not do anything and return ptr
 * If ptr is NULL, then the call is equivalent to malloc(new_size),
 * for all values of old_size and new_size
 * If new_size is equal to zero, and ptr is not NULL, then the
 * call is equivalent to free(ptr). Return NULL
 * @ptr: ointer to the memory previously allocated
 * @old_size: is the size, in bytes, of the allocated space for ptr
 * @new_size: is the new size, in bytes of the new memory block
 * Return: pointer to allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *nptr, *temp_ptr;
	unsigned int i;

	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (old_size == new_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	nptr = malloc(new_size);
	if (nptr == NULL)
		return (NULL);

	temp_ptr = (char *) ptr;
	for (i = 0; i < new_size; i++)
	{
		if (i >= old_size)
			break;
		*(nptr + i) = *(temp_ptr + i);
	}
	free(ptr);
	return ((void *)nptr);
}




/**
 * _strcat - concatenate two strings
 * @dest: string destiny
 * @src: string source
 * Return: Returns a pointer to the destiny string
 */
char *_strncat(int n, char *dest, ...)
{
	va_list list;
	int  destlen, addlen;
	char *add = NULL;

	if (dest == NULL)
		return (NULL);
	va_start(list, dest);
	while (n--)
	{
		add = va_arg(list, char*);
		destlen = _strlen(dest);
		addlen = _strlen(add);
		dest = _realloc(dest, destlen, destlen + addlen + 1);
		_strncpy(dest + destlen, add, addlen);
		dest[destlen + addlen] = '\0';
	}
	va_end(list);
	return (dest);
}


char *putPath(char* command, char *path)
{
	int command_len = _strlen(command);
	int path_len = _strlen(path);
	char tmp_command[100];

	_strncpy(tmp_command, command, command_len);
	tmp_command[command_len] = '\0';

	command = _realloc(command, command_len,
			   command_len + path_len + 1);
	if (command == NULL)
	{
		exit (1);
	}

	_strncpy(command, path, path_len);
	_strncpy(command + path_len, "/", 1);
	_strncpy(command + path_len + 1, tmp_command, command_len);
	command[command_len + path_len + 1] = '\0';

	return (command);
}
