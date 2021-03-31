#include "../shell_header.h"


/**
 * list_len -  returns the number of elements in a linked list_t list.
 * @h: pointer to the list_t
 * Return: number of nodes
 */

size_t list_len(const list_t *h)
{
	if (h == NULL)
		return (0);
	if (h->next == NULL)
		return (1);
	else
		return (1 + list_len(h->next));
}

