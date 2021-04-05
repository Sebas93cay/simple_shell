#include "headershell.h"



int main(__attribute__ ((unused)) int argc,
	 __attribute__ ((unused)) char **argv,
	 __attribute__ ((unused)) char **env)
{
	size_t buffSize = BUFFSIZE;
	pid_t child_pid;
	int status;
	free_chars_t FC;

	FC.args = NULL;
	FC.argv = argv;
	FC.buff = NULL;
	FC.lines = NULL;
	FC.args = malloc(sizeof(char*));
	*(FC.args) = NULL;
	FC.buff = malloc(sizeof(char));
	/* _printf("(%u)I'm the father jojojo\n", getpid()); */
	while (1)
	{
		/* signal(SIGINT, ignore_signal); */

		if (check_inputs(&FC, &buffSize))
			continue;

		free_words(FC.args);

		FC.args = splitwords(FC.buff, ' ');
		/* _printf("Args:\n"); */
		/* print_words(args); */
		if (check_built_in(&FC))
			continue;
		create_child(&child_pid);
		/* _printf("(%u)ya creamos nuestro primer hijo\n", getpid()); */
		if (child_pid == 0)
		{
			exec_command(&FC);
			break;
		}
		else
		{
			wait(&status);
		}
		/* _printf("(%u) salimos de if\n", getpid()); */
	}
	return (0);
}


int check_inputs(free_chars_t *FC, size_t *buffSize)
{
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/

	if (_getline(FC, buffSize) == EOF)
		TheExit(0, FC);

	if (*(FC->buff) == 0)
		return (1);
	_printf("recibimos linea: -> %s\n", FC->buff);
	return (0);


}


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

void check_full_path(char **args)
{
	char *path = _getenv("PATH");
	char **dirs = NULL;
	char *cwd = NULL, *tmp_ptr = NULL;
	int i;
	struct stat st;

	if (args[0][0] != '/')
	{
		cwd = _getenv("PWD");

		dirs = splitwords(path, ':');

		for (i = 0; dirs[i]; i++)
		{
			chdir(dirs[i]);
			if (stat(*args, &st) == 0)
			{
				/* _printf("Found in %s \n", dirs[i]); */
				chdir(cwd);
				break;
			}
		}
		/* _printf("dirs[i] == %s\n", dirs[i]); */
		if (dirs[i] != NULL)
		{
			tmp_ptr = dirs[i];
			dirs[i] = args[0];
			args[0] = tmp_ptr;
			args[0] = _strncat(2, args[0], "/", dirs[i]);
		}
	}
	free_words(dirs);
}

void exec_command(free_chars_t *FC)
{
	/* _printf("Inside exec_command\n"); */
	/* _printf("Buff = %s\n", buff); */
	/* _printf("Arg[0] = %s\n", args[0]); */
	check_full_path(FC->args);
	/* _printf("Despues de buscar path\n"); */
	/* _printf("Buff = %s\n", buff); */
	/* _printf("Arg[0] = %s\n", args[0]); */
	
	if (**(FC->args) == '/' && execve(FC->args[0], FC->args, NULL) == -1)
		execve_not_working(FC);
	else
	{
			_printf("No se pudo encontrar paila\n");
			free_words(FC->args);
			free(FC->buff);
			free_words(environ);
	}
}

