#include "headershell.h"

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


list_t *singly_split_words(char *str, list_t **head, char delimiter)
{
	int letters = 0;

	while (*str)
	{
		while (*str == delimiter)
			str++;
		while (str[letters] != 0 && str[letters] != delimiter)
			letters++;
		add_node_n_end(head, str, letters);
		str += letters;
		letters = 0;
	}
	return (*head);
}

char *pop_list(list_t **head)
{
	list_t *tmp;
	char *ret;

	if (head == NULL || *head == NULL)
		return (NULL);

	ret = (*head)->str;

	tmp = *head;
	*head = tmp->next;
	free(tmp);
	return (ret);
}

