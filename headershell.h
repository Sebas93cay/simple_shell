#ifndef PROMT_H
#define PROMT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#include "headerprintf.h"

/*Enviroment variables*/
extern char **environ;
#define BUFFSIZE 1024

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

typedef struct free_chars_t
{
	char **args;
	char ** argv;
	char *buff;
	list_t *lines;
} free_chars_t;

/*shell*/
int main(__attribute__ ((unused)) int argc,
	 __attribute__ ((unused)) char **argv,
	 __attribute__ ((unused)) char **env);
int check_inputs(free_chars_t *FC, size_t *buffSize);
int check_built_in(free_chars_t *FC);
void check_full_path(char **args);
void exec_command(free_chars_t *FC);

/*fuctions_shell_1.c*/
void execve_not_working(free_chars_t *FC);
void create_child(pid_t *child_pid);
void TheExit(int status, free_chars_t *FC);
void childError(pid_t *child);

/*functions_shell_2.c*/
void __attribute__ ((constructor)) premain();
void ignore_signal(int sig);

/*built_ins.c*/
int built_exit(free_chars_t *FC);
int built_cd(free_chars_t *FC);
void change_WD(char *newpwd, char *pwd);
int built_env(free_chars_t *FC, int mode);

/* miscellaneous functions */
/*miscellaneous_1.c string function*/
int _strlen(char *);
char *_strncpy(char *dest, char *src, int n);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, unsigned int n);

/*miscellaneous_2.c*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strncat(int n, char *dest, ...);
char *putPath(char *command, char *path);
int _atoi(char *s);
char *_strdup(char *s);

/*miscellaneous_3.c*/
char **splitwords(char *buff, char token);
void free_words(char **args);
void print_words(char **words);
int check_if_num(char *num);


/*miscellaneous_4.c enviroment functions*/
char *_getenv(const char *);
void _printenv(void);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);
char **words_cpy(char **words);

/*miscellaneous_5.c*/
ssize_t _getline(free_chars_t *FC, size_t *buffsize);
int check_newline(char *buff, int n);
void remove_newline(char *buff);


/*str_singly_list_1.c*/
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_n(list_t **head, const char *str, size_t n);
void free_list(list_t *head);

/*str_singly_list_2.c*/
list_t *add_node_end(list_t **head, const char *str);
list_t *add_node_n_end(list_t **head, const char *str, size_t n);
list_t *singly_split_words(char *str, list_t **head, char delimiter);
char *pop_list(list_t **head);

#endif
