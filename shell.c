#include "headershell.h"



int main(__attribute__ ((unused)) int argc,
	 __attribute__ ((unused)) char **argv,
	 __attribute__ ((unused)) char **env)
{
	size_t buffSize = 1;
	char *buff = NULL;
	char **args = NULL;
	pid_t child_pid;
	int status;

	args = malloc(sizeof(*args));
	*args = NULL;
	/* _printf("(%u)I'm the father jojojo\n", getpid()); */
	while (1)
	{
		signal(SIGINT, ignore_signal);
		check_inputs(&buff, &buffSize, args);
		if (*buff == '\0')
			continue;
		/* _printf("Vamos a liberarar args\n"); */
		free_words(args);
		/* _printf("Liberamos  args!!\n"); */
		args = splitwords(buff, ' ');
		_printf("Args:\n");
		print_words(args);
		if (check_built_in(args, buff, argv))
			continue;
		create_child(&child_pid);
		/* _printf("(%u)ya creamos nuestro primer hijo\n", getpid()); */
		if (child_pid == 0)
		{
			exec_command(args, argv, buff);
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


int check_built_in(char **args, char *buff, char **argv)
{
	int exit_status;

	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			if (check_if_num(args[1]) == 0)
			{
				exit_status = _atoi(args[1]);
				_printf("exit status = %d\n", exit_status);
				TheExit(exit_status, buff, args);
			}
			else
			{	_printf("%s: 1: exit: Illegal number: %s\n",
					*argv, args[1]);
				return (1);
			}
		}
		else
		{
			TheExit(0, buff, args);
		}
	}
	return (0);
}

void check_full_path(char **args)
{
	char *path = _getenv("PATH");
	char **dirs = NULL;
	char *cwd = NULL, *tmp_ptr = NULL;
	int i, cwd_size = 100;
	struct stat st;

	if (args[0][0] != '/')
	{
		cwd = malloc(sizeof(char) * cwd_size);
		if (cwd == NULL)
			exit(0);
		while (getcwd(cwd, cwd_size) == NULL)
		{
			_printf("cwd_size too small, geting twice it size and trying again");
			cwd_size = 2 * cwd_size;
		}
		_printf("cwd = %s\n", cwd);
		dirs = splitwords(path, ':');
		for (i = 0; dirs[i]; i++)
		{
			chdir(dirs[i]);
			if (stat(*args, &st) == 0)
			{
				_printf("Found in %s \n", dirs[i]);
				chdir(cwd);
				break;
			}
		}
		_printf("dirs[i] == %s\n", dirs[i]);
		if (dirs[i] != NULL)
		{
			tmp_ptr = dirs[i];
			dirs[i] = args[0];
			args[0] = tmp_ptr;
			args[0] = _strncat(2, args[0], "/", dirs[i]);
		}
	}
	free_words(dirs);
	free(cwd);
}

void exec_command(char **args, char **argv, char *buff)
{

	check_full_path(args);
	if (**args == '/' && execve(args[0], args, NULL) == -1)
		execve_not_working(args, argv, buff);
	else
	{
			_printf("No se pudo encontrar paila\n");
			free_words(args);
			free(buff);
	}
}

void ignore_signal(int sig)
{
	write(1, "\n", 1);
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/
	signal(sig, SIG_IGN);
	signal(sig, ignore_signal);
}
