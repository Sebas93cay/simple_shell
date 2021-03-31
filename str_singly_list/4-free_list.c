#include "../shell_header.h"


/**
 * free_list - frees a list_t list.
 * @head: pointer to first element of the list
 * Return: the address of the new element, or NULL if it failed
 */
void free_list(list_t *head)
{
	if (head == NULL)
		return;
	if (head->next != NULL)
		free_list(head->next);
	free(head->str);
	free(head);
	head = NULL;
}
