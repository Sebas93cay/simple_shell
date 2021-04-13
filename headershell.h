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
#define BUFFSIZE 10

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

typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
}alias;

typedef struct ANDOR_t
{
	char *str;
	int tipo;
	struct ANDOR_t *next;
} ANDOR_t;

typedef struct free_chars_t
{
	list_t *args_l;
	char **args;
	char **argv;
	char *buff;
	list_t *lines;
	list_t *commands;
	ANDOR_t *ANDORS;
	int last_command_result;
	int need_to_readnextline;
	alias *aliases;
} free_chars_t;

/*shell*/
int main(__attribute__ ((unused)) int argc,
	 __attribute__ ((unused)) char **argv,
	 __attribute__ ((unused)) char **env);
void infinite_loop(free_chars_t *FC);
int check_inputs(free_chars_t *FC, int *buffSize);
int check_built_in(free_chars_t *FC);
void exec_command(free_chars_t *FC);


/*fuctions_shell_1.c*/
void check_full_path(char **args);
void execve_not_working(free_chars_t *FC);
void create_child(pid_t *child_pid);
void TheExit(int status, free_chars_t *FC);
int check_errors(free_chars_t *FC);

/*functions_shell_2.c*/
void __attribute__ ((constructor)) premain();
void ignore_signal(int sig);
int check_semicolons(free_chars_t *FC);
int split_semicolons(free_chars_t *FC);
char *putPath(char *command, char *path);

/*functions_shell_3.c*/
int check_no_commands_inbetween(free_chars_t *FC);
int check_if_need_more_read_logic(free_chars_t *FC);
int check_if_need_more_read_quotes(free_chars_t *FC);

/*functions_shell_4.c*/
int checkANDOR(free_chars_t *FC);
int check_andor_logic(free_chars_t *FC);

list_t *join_lines(list_t **lines);

/*built_ins.c*/
int built_exit(free_chars_t *FC);
int built_cd(free_chars_t *FC);
void change_WD(char *newpwd, char *pwd);
int built_env(free_chars_t *FC, int mode);
int built_print_aliases(alias *head);

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
int _atoi(char *s);
char *_strdup(char *s);
char *_strndup(char *s, int n);

/*miscellaneous_3.c*/
list_t *splitargs_list(free_chars_t *FC);
void save_arg(free_chars_t *FC, char **buff, list_t **last_node, int *letters, int *saving, int *saved_lett);
char **pointto_words_list(free_chars_t *FC);
char **splitwords(char *buff, char token);
void free_words(char **args);
void print_words(char **words);

/*miscellaneous_4.c enviroment functions*/
char *_getenv(const char *);
void _printenv(void);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);
char **words_cpy(char **words); /*used to copy environ*/

/*miscellaneous_5.c*/
ssize_t _getline(free_chars_t *FC, int *buffsize);
int check_if_character(char *buff, int n, char c);
void remove_last_character(char *buff, char c);
int check_if_not_commands(char *buff);
int check_if_line(char *buff, int n);

/*miscellaneous_6.c*/
int check_if_num(char *num);
char *_strcatn(char *dest, char* src, int n);

/*str_singly_list_1.c*/
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_n(list_t **head, const char *str, size_t n);
void free_list(list_t **head);

/*str_singly_list_2.c*/
list_t *add_node_end(list_t **head, const char *str);
list_t *add_node_n_end(list_t **head, const char *str, size_t n);
list_t *singly_split_words(char *str, list_t **head, char delimiter);
char *pop_list(list_t **head);
int delete_node_at_index(list_t **head, unsigned int index);

/*ANDOR_list_functions.c*/
ANDOR_t *add_node_n_end_andor(ANDOR_t **head, char *str, int n, int tipo);
size_t list_len_andor(const ANDOR_t *h);
char *pop_andor(ANDOR_t **head);
void free_ANDOR(ANDOR_t **head);

#endif
