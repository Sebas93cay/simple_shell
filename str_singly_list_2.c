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

	if (str == NULL || *str == 0)
		return (NULL);
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

	if (str == NULL || *str == 0)
		return (NULL);

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

/**
 * singly_split_words - split string str with character delimiter and
 * store the pieces in the linked list head
 * @str: string
 * @head: linked list pointer
 * @delimiter: character
 * delimiter: character to split str
 * Return: return pointer to linked list with the splited strings
 */
list_t *singly_split_words(char *str, list_t **head, char delimiter)
{
	int letters = 0;
	int bytes_to_add = 0;

	while (*str)
	{
		while (*str == delimiter)
			str++;
		while (str[letters] != 0 && str[letters] != delimiter)
			letters++;
		bytes_to_add = (str[letters] == 0) ? letters : letters + 1;
		add_node_n_end(head, str, bytes_to_add);
		if (*(str + letters) == 0)
			return (*head);
		str += letters + 1;
		letters = 0;
	}
	return (*head);
}

/**
 * pop_list - remove fisrt node in linked list head
 * @head: linked list
 * Return: pointer to string of the first element of the list
*/
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



/**
 * delete_node_at_index - deletes the node at index index
 * of a listint_t linked list.
 * @head: linked list.
 * @index: index to delete
 * Return: 1 if it succeeded, -1 if it failed
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int idx = 0;
	list_t *tmp_head = NULL, *tmp_node = NULL;

	if (head == NULL || *head == NULL)
		return (-1);

	tmp_head = *head;
	if (index == 0)
	{
		tmp_node = *head;
		*head = (*head)->next;
	}
	else
	{
		while (idx < index - 1)
		{
			if (tmp_head == NULL)
				return (-1);
			tmp_head = tmp_head->next;
			idx++;
		}
		tmp_node = tmp_head->next;
		tmp_head->next = tmp_node->next;
	}
	free(tmp_node);
	return (1);
}
