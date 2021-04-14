#include "headershell.h"


/**
 * main - simple shell
 * @argc: argument counts
 * @argv: argument vector
 * @env: eviroment vector
 * Return: always return 0
 */
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
	FC.buff = malloc(sizeof(char));
	FC.ANDORS = NULL;
	FC.aliases = NULL;
	FC.last_command_result = 0;
	FC.need_to_readnextline = 0;
	FC.args_l = NULL;

	infinite_loop(&FC);
	return (0);
}

/**
 * infinite_loop - frees all strings in FC and shows error message
 * @FC: string structure.
 * Return: nothing
 */
void infinite_loop(free_chars_t *FC)
{
	pid_t child_pid;
	int buffSize = BUFFSIZE, status, ndrlen, cmndlen;

	while (1)
	{
		ndrlen = list_len_andor(FC->ANDORS);
		cmndlen = list_len(FC->commands);
		if ((ndrlen == 0 && cmndlen == 0))
		{
			if (check_inputs(FC, &buffSize))
				continue;
		}
		if (check_errors(FC))
			continue;
		if (ndrlen == 0)
			if (check_semicolons(FC) == 1)
				continue;
		if (checkANDOR(FC) == 1)
			continue;
		splitargs_list(FC);
		/* print_list(FC->args_l); */
		pointto_words_list(FC);
		/* print_words(FC->args); */
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
			if (WIFEXITED(status))
				FC->last_command_result = WEXITSTATUS(status);
			else
				FC->last_command_result = 1;
		}
	}
}


/**
 * check_inputs - Read input from stdin
 * @FC: string structure.
 * @buffSize: buffer's size
 * Return: 0 in success, 1 otherwise
 */
int check_inputs(free_chars_t *FC, int *buffSize)
{
	if (isatty(0) && FC->need_to_readnextline == 0)
		_printf("#cisfun$ "); /*print only in terminal*/

	FC->need_to_readnextline = 0;
	if (_getline(FC, buffSize) == EOF)
	{
		free_list(&FC->args_l);
		free_words(environ);
		if (FC->last_command_result == 1)
			exit(127);
		exit(0);
	}
	/* _printf("la linea es = %s\n", FC->buff); */

	if (FC->buff == NULL || *(FC->buff) == 0)
		return (1);

	if (check_if_not_commands(FC->buff) == 1)
		return (1);

	/* _printf("recibimos linea: -> %s\n", FC->buff); */
	return (0);


}


/**
 *check_built_in - check if input is any of the builtins
 * @FC: string structure.
 * Return: 0 in success, 1 otherwise
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
	{
		if (FC->args[1] != NULL && FC->args[2] != NULL)
			return (built_env(FC, 1));
		FC->last_command_result = 1;
		return (1);

	}
	if (_strcmp(FC->args[0], "unsetenv") == 0)
	{
		if (FC->args[1] != NULL)
			return (built_env(FC, 2));
		FC->last_command_result = 1;
		return (1);

	}
	if (_strcmp(FC->args[0], "alias") == 0)
	{
		if (FC->args[1] == NULL)
		{
			built_print_aliases(FC->aliases);
			return (1);
		}
		else
		{
			_printf("el argumento 2 es: %s\n", FC->args[1]);
			_printf("el argumento 3 es: %s\n", FC->args[2]);
		}
	}
	return (0);
}


/**
 * exec_command - executes comands in args.
 * @FC: string structure.
 * Return: nothing
 */
void exec_command(free_chars_t *FC)
{
	int result;

	check_full_path(FC->args);



	if (**(FC->args) == '/')
	{
		result = execve(FC->args[0], FC->args, environ);
		if (result == -1)
			execve_not_working(FC);
	}
	else
	{
			_printf("No se pudo encontrar paila\n");

			FC->last_command_result = 1;
			free(FC->args);
			free_list(&FC->args_l);
			free(FC->buff);
			free_list(&FC->lines);
			/* _printf("commands\n"); */
			free_list(&FC->commands);
			free_words(environ);
			exit(1);
	}
}
