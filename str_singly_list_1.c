#include "headershell.h"

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

/**
 * add_node - adds a new node at the beginning of a list_t list.
 * @head: pointer to pointer to first element of the list
 * @str: string to be copied in new element
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;
	int strlen = 0;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	if (str != NULL)
	{
		while (str[strlen])
			strlen++;
		new->str = _strdup((char *)str);
	}
	else
		new->str = NULL;
	new->len = strlen;
	new->next = *head;
	*head = new;
	return (*head);
}

/**
 * free_list - frees a list_t list.
 * @head: pointer to first element of the list
 * Return: the address of the new element, or NULL if it failed
 */
void free_list(list_t **head)
{
	if (head == NULL || *head == NULL)
		return;
	if ((*head)->next != NULL)
		free_list(&(*head)->next);
	free((*head)->str);
	free(*head);
	*head = NULL;
}
