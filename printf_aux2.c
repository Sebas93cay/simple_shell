#include "headerprintf.h"
#include "headershell.h"
/**
 * place_x - write the first number in the argument list
 * in format HEX format lowercase
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */
int place_x(va_list args, char *buff, int *b_cnt,
	    flag *flags, int out)
{
	long int num;
	int new_buffs = 0, len;
	char num_holder[17], *num_s;

	if (flags[3].value)
		num = va_arg(args, long int);
	else if (flags[4].value)
		num = (short) va_arg(args, int);
	else
		num = va_arg(args, int);

	printf("num =\n%lx\n", ULONG_MAX);
	num_holder[16] = 0;
	if (flags[2].value == 1 && num != 0)
		new_buffs += putInBuffer(buff, b_cnt, "0x", 2, out);
	num_s = base_convert(num_holder, 16, num, 16, 87);
	len = _strlen(num_s);

	new_buffs += putInBuffer(buff, b_cnt, num_s, len, out);
	return (new_buffs);
}

/**
 * place_X - write the first number in the argument list
 * in format HEX format uppercase
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */

int place_X(va_list args, char *buff, int *b_cnt,
	    flag *flags, int out)
{
	long int num;
	int new_buffs = 0, len;
	char num_holder[17], *num_s;

	if (flags[3].value)
		num = va_arg(args, long int);
	else if (flags[4].value)
		num = (short) va_arg(args, int);
	else
		num = va_arg(args, int);

	num_holder[16] = 0;
	if (flags[2].value == 1 && num != 0)
		new_buffs += putInBuffer(buff, b_cnt, "0X", 2, out);

	num_s = base_convert(num_holder, 16, num, 16, 55);
	len = _strlen(num_s);
	new_buffs += putInBuffer(buff, b_cnt, num_s, len, out);
	return (new_buffs);
}

/**
 * place_o - write the first number in the argument list
 * in format OCTAL format
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */

int place_o(va_list args, char *buff, int *b_cnt,
	    flag *flags, int out)
{
	long int num;
	int new_buffs = 0, len;
	char num_holder[27], *num_s;

	if (flags[3].value)
		num = va_arg(args, long int);
	else if (flags[4].value)
		num = (short) va_arg(args, int);
	else
		num = va_arg(args, int);

	if (flags[2].value == 1 && num != 0)
		new_buffs += putInBuffer(buff, b_cnt, "0", 1, out);
	num_holder[26] = 0;

	num_s = base_convert(num_holder, 26, num, 8, 0);
	len = _strlen(num_s);
	new_buffs += putInBuffer(buff, b_cnt, num_s, len, out);
	return (new_buffs);
}


/**
 * place_u - write the first number in the argument list
 * in format UNSIGNED format
 * @args: argument list
 * @buff: buffer
 * @b_cnt: bytes printed counter
 * @flags: structure with flags activated to have into account
 * Return: return number of new buffers needed to print string
 */
int place_u(va_list args, char *buff, int *b_cnt, flag *flags, int out)
{
	unsigned long int num;
	int new_buffs = 0, len;
	char num_holder[25], *num_s;

	if (flags[3].value)
		num = va_arg(args, unsigned long int);
	else if (flags[4].value)
		num = (short) va_arg(args, int);
	else
		num = va_arg(args, int);

	num_s = _itoa(25, '+', num, num_holder);
	len = _strlen(num_s);
	new_buffs = putInBuffer(buff, b_cnt, num_s, len, out);
	return (new_buffs);
}

int place_p(va_list args, char *buff, int *b_cnt,
	    __attribute__ ((unused)) flag *flags, int out)
{
	char *s;
	void *ptr = va_arg(args, void*);
	int new_buffs = 0, len;
	char snull[] = "(nil)";
	char buffer[20];

	if (!ptr)
		s = snull;
	else
		s = getAddress_p(ptr, buffer, 20);

	len = _strlen(s);

	new_buffs = putInBuffer(buff, b_cnt, s, len, out);

	return (new_buffs);
}
