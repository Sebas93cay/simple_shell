#include "../shell_header.h"


/**
 * add_node_end - adds a new node at the end of a list_t list.
 * @head: pointer to pointer to first element of the list
 * @str: string to be copied in new element
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new, *l_point;
	int strlen = 0;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	if (str != NULL)
	{
		while (str[strlen])
			strlen++;
		new->str = strdup(str);
	}
	else
		new->str = NULL;

	new->len = strlen;
	new->next = NULL;

	if (*head == NULL)
		*head = new;
	else
	{
		l_point = *head;
		while (l_point->next != NULL)
			l_point = l_point->next;

		l_point->next = new;
	}
	return (new);
}



/**
 * add_node_n_end - adds a new node at the end of a list_t list.
 * @head: pointer to pointer to first element of the list
 * @str: string to be copied in new element
 * @n: bytes to copy into new node
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node_n_end(list_t **head, const char *str, size_t n)
{
	list_t *new, *l_point;
	int strlen = n;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	if (str != NULL)
	{
		new->str = strndup(str, n);
	}
	else
		new->str = NULL;

	new->len = strlen;
	new->next = NULL;

	if (*head == NULL)
		*head = new;
	else
	{
		l_point = *head;
		while (l_point->next != NULL)
			l_point = l_point->next;

		l_point->next = new;
	}
	return (new);
}
