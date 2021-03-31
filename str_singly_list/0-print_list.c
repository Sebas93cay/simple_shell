#include "../shell_header.h"

/**
 * print_list - prints all the elements of a list_t list.
 * @h: pointer to the list_t
 * Return: number of nodes
 */
size_t print_list(const list_t *h)
{
	if (!h)
		return (0);
	if (h->str == NULL)
		printf("[%u] %s\n", 0, "(nil)");
	else
		printf("[%u] %s\n", h->len, h->str);

	if (h->next == NULL)
		return (1);
	else
		return (1 + print_list(h->next));

}
