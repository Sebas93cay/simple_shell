#include "headerprintf.h"

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
 * itohex_2bytes - convert int n in an hexadecimal of 2 caracters
 * @n: number
 * @dest: buffer of 2 bytes minimum to store number converted
 * Return: nothing
 */
void itohex_2bytes(unsigned int n, char *dest)
{
	int i, digit;

	for (i = 1; i >= 0; i--)
	{
		digit = n % 16;
		n = n / 16;
		if (digit < 10)
			dest[i] = digit + '0';
		else
			dest[i] = digit + 55;
	}
}

/**
 * _itobi - convert unsigned integer n to binary.
 * @n: number to convert
 * @buff: buffer of 33 bytes minimun to store the converted number
 * @size: size of buffer
 * Return: pointer to first byte of number as a string
 */
char *_itobi(unsigned int n, char *buff, int size)
{
	if (size == 31)
	{
		buff[size + 1] = 0;
		if (!n)
		{
			buff[size] = '0';
			return (buff + size);
		}
	}
	if (!n)
		return (buff + size + 1);
	buff[size] = n % 2 + '0';
	return (_itobi(n / 2, buff, size - 1));
}


/**
 * base_convert - convert base 10 n in another base
 * @buff: buffer to save the new number
 * @size_b: size of buff
 * @n: number to change the base
 * @base: new base of n
 * @aditionalChars: aditional chars when the n/base >= 10
 * Return: buffer with the new number
*/

char *base_convert(char *buff, int size_b,
		   unsigned long int n, int base, int aditionalChars)
{
	if (n % base < 10)
		buff[size_b - 1] = (n % base) + '0';
	else
		buff[size_b - 1] = (n % base) + aditionalChars;

	if (!n)
	{
		if (buff[size_b - 1] == '0' && buff[size_b])
			return (buff + size_b);
		else
			return (buff + size_b - 1);
	}

	return (base_convert(buff, size_b - 1, n / base, base, aditionalChars));
}

/**
 * getAddress_p - save address memory of p in a buffer
 * @p: pointer with the address memory to save
 * @buf: buffer to save the address
 * @size_b: size of the buf
 * Return: buff modified
 */

char *getAddress_p(void *p, char *buf, int size_b)
{
	unsigned long int x = (unsigned long int) p;
	char e;
	unsigned int i;
	int j;

	buf[0] = '0';
	buf[1] = 'x';
	printf("sizeof(x) = %lu\n", sizeof(x));
	for (i = 0, j = 0; i < sizeof(x) * 2 && j + 2 < size_b; i++)
	{

		e = "0123456789abcdef"
			[(x >> ((sizeof(x) * 2 - 1 - i) * 4)) & 0xf];
		if (e != '0' || buf[j + 1] != 'x')
		{
			buf[j + 2] = e;
			j++;
		}
		printf("i = %i e = %c buf = %s\n", i, e, buf);
	}
	buf[j + 2] = 0;
	return (buf);
}
