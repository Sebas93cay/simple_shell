#include "headerprintf.h"
#include "headershell.h"

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
	/* printf("sizeof(x) = %lu\n", sizeof(x)); */
	for (i = 0, j = 0; i < sizeof(x) * 2 && j + 2 < size_b; i++)
	{

		e = "0123456789abcdef"
			[(x >> ((sizeof(x) * 2 - 1 - i) * 4)) & 0xf];
		if (e != '0' || buf[j + 1] != 'x')
		{
			buf[j + 2] = e;
			j++;
		}
		/* printf("i = %i e = %c buf = %s\n", i, e, buf); */
	}
	buf[j + 2] = 0;
	return (buf);
}

/**
 * putInBuffer - copy s into buff, in case buff is filled, it is printed
 * and started to being filled from zero
 * @buff: buffer
 * @b_cnt: bytes used in current buffer
 * @s: string to copy
 * @len: lenght in bytes of s
 * Return: pointer to first byte of number as a string
 */
int putInBuffer(char *buff, int *b_cnt, char *s, int len)
{
	int available, new_buffs = 0;

	available = BUFF_SIZE - *b_cnt;

	if (available >= len)
	{
		_strncpy(buff + *b_cnt, s, len);
		(*b_cnt) += len;
	}
	else
	{
		_strncpy(buff + *b_cnt, s, available);
		write(1, buff, BUFF_SIZE);
		(*b_cnt) = 0;
		new_buffs += fillnewbuff(buff, s + available, len - available,
			    BUFF_SIZE, b_cnt);
	}
	return (new_buffs);
}


/**
 * checkFlags - d
 * @buff: buffer
 * @b_cnt: bytes used in current buffer
 * @flags: array of structs with activated flags
 * @new_buffs: buffers quantity to use
 * Return: nothing
 */
void checkFlags(char *buff, int *b_cnt, flag *flags, int *new_buffs)
{
	int i;

	for (i = 0; flags[i].c; i++)
	{
		if (flags[i].value)
		{
			*new_buffs += putInBuffer(buff, b_cnt,
						 &(flags[i].c), 1);
			break;
		}
	}

}
