#include "holberton.h"

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
 * fillnewbuff - fill empty buffer with string src. If buffer is filled, it is
 * printed and it start being filled again with remains of src.
 * @buff: buffer
 * @src: source string
 * @to_write: bytes to write in buffer
 * @buff_size: buffer size
 * @b_cnt: pointer to bytes used in buffer, it's value is updated in function
 * Return: return number of buffers initialized during execution
 */
int fillnewbuff(char *buff, char *src, int to_write, int buff_size, int *b_cnt)
{
	int used_buff;

	if (buff_size >= to_write)
	{
		_strncpy(buff, src, to_write);
		*(b_cnt) = to_write;
		return (1);
	}

	write(1, src, buff_size);
	used_buff = fillnewbuff(buff, src + buff_size, to_write - buff_size,
				buff_size, b_cnt);
	return (used_buff + 1);
}

/**
 * _itoa - convert a integer into a string
 * @num: number
 * @nums: buffer of minimun 12 bytes to storage the number as a string
 * @sign: sing char
 * Return: pointer to first byte of number as a string
 */
char *_itoa(int buffsize, char sign, unsigned long int num, char *nums)
{
	int i = buffsize - 2, negative = 0, digit;

	nums[buffsize - 1] = 0;
	if (sign == '-')
	{
		negative = 1;
	}
	do {
		digit = num % 10;
		digit = (digit < 0) ? -digit : digit;
		nums[i] = digit + '0';
		num = num / 10;
		i--;
	} while (num);
	if (negative)
	{
		nums[i] = '-';
		return (nums + i);
	}
	return (nums + i + 1);
}

/**
 * conv_non_printable - convert non printables characters in string s
 * to format \xXX where XX is its value in hexagesimal
 * @s: string
 * Return: pointer to new malloced string.
 */
char *conv_non_printable(char *s)
{
	int len, i, s_cnt = 0;
	char *s_converted;

	len = _strlen(s) + 1;
	s_converted = malloc(sizeof(*s_converted) * len);
	if (s_converted == NULL)
		return (NULL);
	for (i = 0; s[i]; i++)
	{
		if (s[i] >= 32 && s[i] <= 126)
			s_converted[s_cnt++] = s[i];
		else
		{
			s_converted = _realloc(s_converted, len, len + 3);
			len += 3;
			s_converted[s_cnt++] = '\\';
			s_converted[s_cnt++] = 'x';
			itohex_2bytes(s[i], s_converted + s_cnt);
			s_cnt += 2;
		}
	}
	s_converted[s_cnt] = 0;
	/* _printf("s_cnt = %d\n", s_cnt); */
	return (s_converted);
}
