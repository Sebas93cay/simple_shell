#include "headershell.h"



int main(__attribute__ ((unused)) int argc,
	 __attribute__ ((unused)) char **argv,
	 __attribute__ ((unused)) char **env)
{
	free_chars_t FC;

	FC.args = NULL;
	FC.argv = argv;
	FC.buff = NULL;
	FC.lines = NULL;
	FC.commands = NULL;
	FC.args = malloc(sizeof(char *));
	*(FC.args) = NULL;
	FC.buff = malloc(sizeof(char));
	FC.ANDORS = NULL;

	infinite_loop(&FC);

	return (0);
}

/**
 * execve_not_working - frees all strings in FC and shows error message
 */
void infinite_loop(free_chars_t *FC)
{
	pid_t child_pid;
	int buffSize = BUFFSIZE, status, ndrlen, cmndlen;

	while (1)
	{
		ndrlen = list_len_andor(FC->ANDORS);
		cmndlen = list_len(FC->commands);
		if (ndrlen == 0 && cmndlen == 0)
		{
			if (check_inputs(FC, &buffSize))
				continue;
		}
		if (ndrlen == 0)
		{
			if (check_semicolons(FC) == 1)
				continue;		
		}		
		if (checkANDOR(FC) == 1)
			continue;
		
			/* semicolonCheck = 0; */
			/* if (list_len(FC->commands) == 0) */
			/* { */
			/* 	if (check_inputs(FC, &buffSize)) */
			/* 		continue; */
			/* 	if (check_if_character(FC->buff, 0, ';') == 1) */
			/* 		semicolonCheck = check_semicolons(FC); */
			/* } */
			/* else */
			/* 	semicolonCheck = check_semicolons(FC); */
			/* if (semicolonCheck) */
			/* 	continue;		 */

		free_words(FC->args);
		FC->args = splitwords(FC->buff, ' ');
		if (check_built_in(FC))
			continue;
		create_child(&child_pid);
		if (child_pid == 0)
		{
			exec_command(FC);
			break;
		}
		else
		{
			wait(&status);
			/* _printf("WIFEXITED = %d\n", WIFEXITED(status)); */
			/* _printf("WEXISTATUS = %d\n", WEXITSTATUS(status)); */
		}
	}

}


/**
 *check_inputs - Receive inputs from stdin
 */
int check_inputs(free_chars_t *FC, int *buffSize)
{
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/

	if (_getline(FC, buffSize) == EOF)
	{
		free_words(FC->args);
		free_words(environ);
		exit(0);
	}

	if (FC->buff == NULL || *(FC->buff) == 0)
		return (1);

	if (check_if_only_spaces(FC->buff) == 1)
		return (1);
	
	

	/* _printf("recibimos linea: -> %s\n", FC->buff); */
	return (0);


}


/**
 *check_built_in - check if input is any of the builtins
 */
int check_built_in(free_chars_t *FC)
{
	if (_strcmp(FC->args[0], "exit") == 0)
		return (built_exit(FC));
	if (_strcmp(FC->args[0], "cd") == 0)
		return (built_cd(FC));
	if (_strcmp(FC->args[0], "env") == 0)
		return (built_env(FC, 0));
	if (_strcmp(FC->args[0], "setenv") == 0)
		return (built_env(FC, 1));
	if (_strcmp(FC->args[0], "unsetenv") == 0)
		return (built_env(FC, 2));
	return (0);
}


/**
 * exec_commands - executes comands in args.
 */
void exec_command(free_chars_t *FC)
{
	int result;
	
	check_full_path(FC->args);

	if (**(FC->args) == '/')
	{
		result = execve(FC->args[0], FC->args, NULL);
		if (result == -1)
			execve_not_working(FC);
	}
	else
	{
			_printf("No se pudo encontrar paila\n");
			free_words(FC->args);
			free(FC->buff);
			free_list(FC->lines);
			free_words(environ);
	}
}


