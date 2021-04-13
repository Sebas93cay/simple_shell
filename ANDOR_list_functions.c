#include "headershell.h"

ANDOR_t *add_node_n_end_andor(ANDOR_t **head, char *str, int n, int tipo)
{
	ANDOR_t *new, *l_point;

	if (str == NULL || *str == 0)
		return (NULL);

	new = malloc(sizeof(ANDOR_t));
	if (new == NULL)
		return (NULL);
	if (str != NULL)
	{
		new->str = _strndup(str, n);
	}
	else
		new->str = NULL;

	new->tipo = tipo;
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
 * list_len_andor -  returns the number of elements in a linked list_t list.
 * @h: pointer to the list_t
 * Return: number of nodes
 */

size_t list_len_andor(const ANDOR_t *h)
{
	if (h == NULL)
		return (0);
	if (h->next == NULL)
		return (1);
	else
		return (1 + list_len_andor(h->next));
}



char *pop_andor(ANDOR_t **head)
{
	ANDOR_t *tmp;
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
 * free_ANDOR - frees a ANDOR_t list.
 * @head: pointer to first element of the list
 * Return: nothing
 */
void free_ANDOR(ANDOR_t **head)
{
	if (*head == NULL || head == NULL)
		return;
	if ((*head)->next != NULL)
		free_ANDOR(&(*head)->next);
	free((*head)->str);
	free(*head);
	*head = NULL;
}
