#include "../shell_header.h"


list_t *splwords(char *str, list_t **head)
{
	int letters = 0;

	while (*str)
	{
		while (*str == ' ')
			str++;
		while (str[letters] != 0 && str[letters] != ' ')
			letters++;
		add_node_n_end(head, str, letters);
		str += letters;
		letters = 0;
	}
	return (*head);
}

int main(void)
{
	char *buff;
	size_t size = 5;
	int bytes, numero;
	list_t *words = NULL;

	buff = malloc(sizeof(*buff) * size);
	if (!buff)
		printf("Error, buff were not able to initialize");
	printf("$ ");
	bytes = getline(&buff, &size, stdin);
	buff[strlen(buff) - 1] = '\0';

	/* printf("len = %d\nstring = %s\n", (int)strlen(buff), buff); */

	splwords(buff, &words);
	numero = print_list(words);
	printf("numero = %d\n", numero);
	free(words);
	free(buff);
	return (0);
}
