#include "holberton.h"

/**
 * place_s - finds string in args and copy it to buffer, in
 * case the buffers fill up. buffer is printed and emptied.
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */
int place_s(va_list args, char *buff, int *b_cnt,
	    __attribute__ ((unused)) flag * flags)
{
	char *s = va_arg(args, char *);
	int new_buffs = 0, len;
	char snull[] = "(null)";

	if (s == NULL)
		s = snull;
	len = _strlen(s);

	new_buffs += putInBuffer(buff, b_cnt, s, len);

	return (new_buffs);
}

/**
 * place_S - finds string in args and copy it to buffer, in
 * case the buffers fill up. buffer is printed and emptied.
 * non-printable characters are copyed as \xXX where XX is their
 * value in hexadecimal
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */
int place_S(va_list args, char *buff, int *b_cnt,
	    __attribute__ ((unused)) flag * flags)
{
	char *s = va_arg(args, char *);
	int new_buffs = 0, len;
	char snull[] = "(null)";

	if (s == NULL)
		s = snull;
	s = conv_non_printable(s);
	if (s == NULL)
		return (-1);
	len = _strlen(s);

	new_buffs += putInBuffer(buff, b_cnt, s, len);

	free(s);
	return (new_buffs);
}


/**
 * place_c - finds char in args and copy it to buffer, in
 * case the buffers fill up. buffer is printed and emptied.
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */
int place_c(va_list args, char *buff, int *b_cnt,
	    __attribute__ ((unused)) flag * flags)
{
	char c = va_arg(args, int);
	int new_buff = 0;

	new_buff += putInBuffer(buff, b_cnt, &c, 1);
	return (new_buff);
}

/**
 * place_d - finds int in args and copy it to buffer, in
 * case the buffers fill up. buffer is printed and emptied.
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */
int place_d(va_list args, char *buff, int *b_cnt,
	    flag *flags)
{
	long int num;
	int new_buffs = 0, len;
	char num_holder[25], *num_s;

	if (flags[3].value)
		num = va_arg(args, long int);
	else if (flags[4].value)
		num = (short) va_arg(args, int);
	else
		num = va_arg(args, int);
	if (num < 0)
		num_s = _itoa(25, '-', -num, num_holder);
	else
		num_s = _itoa(25, '+', num, num_holder);
	if (flags[0].value == 1 && num >= 0)
		new_buffs += putInBuffer(buff, b_cnt, "+", 1);
	else if (flags[1].value == 1 && num >= 0)
		new_buffs += putInBuffer(buff, b_cnt, " ", 1);

	len = _strlen(num_s);
	new_buffs += putInBuffer(buff, b_cnt, num_s, len);
	return (new_buffs);
}

/**
 * place_b - finds int in args and copy it to buffer with bynary
 * format, in case the buffers fill up. buffer is printed and emptied.
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */
int place_b(va_list args, char *buff, int *b_cnt,
	    __attribute__ ((unused)) flag * flags)
{
	int num = va_arg(args, int);
	int new_buffs = 0, len;
	char num_holder[33], *num_s;

	num_s = _itobi(num, num_holder, 31);
	len = _strlen(num_s);
	new_buffs += putInBuffer(buff, b_cnt, num_s, len);
	return (new_buffs);
}
