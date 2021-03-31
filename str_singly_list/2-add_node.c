#include "../shell_header.h"


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
		new->str = strdup(str);
	}
	else
		new->str = NULL;
	new->len = strlen;
	new->next = *head;
	*head = new;
	return (*head);
}


/**
 * add_node_n - adds a new n bytes node at the beginning of a list_t list
 * @head: pointer to pointer to first element of the list
 * @str: string to be copied in new element
 * @n: bytes to copy into new node
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node_n(list_t **head, const char *str, size_t n)
{
	list_t *new;
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
	new->next = *head;
	*head = new;
	return (*head);
}
