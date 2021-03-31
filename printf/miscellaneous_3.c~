#include "holberton.h"

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

void arrangeFlags(char *order, flag *flags)
{
	flag aux_flag;
	int i, j;

	for (i = 0; order[i]; i++)
	{
		for (j = 0; flags[j].c; j++)
		{
			if (order[i] == flags[j].c)
			{
				aux_flag = flags[i];
				flags[i] = flags[j];
				flags[j] = aux_flag;
				break;
			}
		}
	}
}
