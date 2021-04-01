#ifndef printflib

#define printflib
#define BUFF_SIZE 10240

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

/**
 * struct flag - struct of a flag
 *
 * @c: char found after a '%' character in printf's format
 * @value: int value of flat
 */
typedef struct flag
{
	char c;
	int value;
} flag;

/**
 * struct placeholders - struct of differtent placeholders used in
 * printf
 *
 * @c: char found after a '%' character in printf's format
 * @place_function: The function associated
 */
typedef struct placeholders
{
	char c;
	int (*place_function)(va_list, char *, int *, flag *);
} placeholders;

/*Main printf functions*/
int _printf(const char *, ...);
int trav_format(va_list args, placeholders *ph, const char *format);
void trav_holders(placeholders *ph, const char **trav, int *used_buff,
		  va_list args, char *buff, int *b_cnt);

/*Place functions*/
int place_s(va_list args, char *buff, int *b_cnt, flag *flags);
int place_c(va_list args, char *buff, int *b_cnt, flag *flags);
int place_d(va_list args, char *buff, int *b_cnt, flag *flags);
int place_S(va_list args, char *buff, int *b_cnt, flag *flags);
int place_b(va_list args, char *buff, int *b_cnt, flag *flags);
int place_x(va_list args, char *buff, int *b_cnt, flag *flags);
int place_X(va_list args, char *buff, int *b_cnt, flag *flags);
int place_o(va_list args, char *buff, int *b_cnt, flag *flags);
int place_u(va_list args, char *buff, int *b_cnt, flag *flags);
int place_p(va_list args, char *buff, int *b_cnt, flag *flags);

/*Miscelaneos functions for printf*/
/*printmisc1.c*/
int fillnewbuff(char *buff, char *src, int n, int buff_size, int *b_cnt);
char *_itoa(int buffsize, char sign, unsigned long int num, char *nums);
char *conv_non_printable(char *s);
void itohex_2bytes(unsigned int n, char *dest);
char *_itobi(unsigned int n, char *buff, int size);
/*printmisc2.c*/
char *base_convert(char*, int, unsigned long int, int, int);
char *getAddress_p(void*, char*, int);
int putInBuffer(char *buff, int *b_cnt, char *s, int len);
void checkFlags(char *buff, int *b_cnt, flag *flags, int *new_buffs);

#endif
