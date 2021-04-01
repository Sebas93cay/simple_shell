#ifndef PROMT_H
#define PROMT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "headerprintf.h"

/*Enviroment variables*/
extern char **environ;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/*shell*/
void execve_not_working(char **args, char **argv, char *buff);
void create_child(pid_t *child_pid);
void check_inputs(char **buff, size_t *buffSize, char **args);
void childError(pid_t *child);

/* miscellaneous functions */
/*miscellaneous_1.c string function*/
int _strlen(char *);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, unsigned int n);
char **splitwords(char *buff, char token);

/*miscellaneous_2.c*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*miscellaneous_3.c*/
void free_args(char **args);

/*miscellaneous_4.c enviroment functions*/
char *_getenv(const char *var);
void _printenv(void);
int _setenv(char *name, char *value, int overwrite);

/*String linked list functions*/
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_n(list_t **head, const char *str, size_t n);
list_t *add_node_end(list_t **head, const char *str);
list_t *add_node_n_end(list_t **head, const char *str, size_t n);
void free_list(list_t *head);


#endif
