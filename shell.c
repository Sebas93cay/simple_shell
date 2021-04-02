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
	/* _printf("(%u)I'm the father jojojo\n", getpid()); */
	while (1)
	{
		check_inputs(&buff, &buffSize, args);
		if (*buff == '\0')
			continue;
		/* _printf("Vamos a liberarar args\n"); */
		free_words(args);
		/* _printf("Liberamos  args!!\n"); */
		args = splitwords(buff, ' ');
		_printf("Args:\n");
		print_words(args);
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

void exec_command(char **args, char **argv, char *buff)
{
	char *path = _getenv("PATH");
	char **dirs = NULL;
	char *cwd = NULL, *path_dir = NULL;
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
		/* _printf("cwd = %s\n", cwd); */
		dirs = splitwords(path, ':');
		for (i = 0; dirs[i]; i++)
		{
			chdir(dirs[i]);
			/* _printf("Nuevo directorio = %s\n", dirs[i]); */
			/* _printf("looking for *args=%s\n", *args); */
			if (stat(*args, &st) == 0)
			{
				path_dir = dirs[i];
				_printf("Found in %s \n", path_dir);
				chdir(cwd);
				break;
			}
		}
		_printf("After for\n path_dir = %s\n", path_dir);
		if (path_dir == NULL)
		{
			_printf("No se pudo encontrar paila\n");
		}
		else
		{
			_printf("args[0] = %s\n", args[0]);
			args[0] = putPath(args[0], path_dir);
			_printf("luego args[0] = %s\n", args[0]);
		}
	}
	
	if (args[0][0] == '/' && execve(args[0], args, NULL) == -1)
	{
		execve_not_working(args, argv, buff);
	}
	_printf("vamos a liberar dirs\n");
	print_words(dirs);
	free_words(dirs);
	_printf("ahora cwd\n");
	free(cwd);
}

void execve_not_working(char **args, char **argv, char *buff)
{
	/* _printf("(%u) liberaremos args[0]\n", getpid()); */

	free_words(args);

	free(buff);

	perror(argv[0]);

}

void check_inputs(char **buff, size_t *buffSize, char **args)
{
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/
	if (getline(buff, buffSize, stdin) == EOF
	    || _strcmp(*buff, "exit") == 0)
	{
		if (isatty(0) && _strcmp(*buff, "exit") != 0)
			write(1, "\n", 1); /*print only in terminal*/
		free(*buff);
		free_words(args);
		exit(0);
	}
	buff[0][_strlen(buff[0]) - 1] = '\0'; /*Remove new line*/
	/* _printf("(%u) recibimos linea:\n%s\n", getpid(), *buff); */
}

void create_child(pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		childError(child_pid);
	/* if (*child_pid != 0) */
	/* { */
	/* 	_printf("(%u) My son is alive, his name is %u\n", getpid(), *child_pid); */
	/* } */
	/* else */
	/* { */
	/* 	_printf("(%u) Yes! I'm alive! my father is %u\n", getpid(), getppid()); */
	/* } */
}

void childError(pid_t *child)
{
	_printf("Child %u not created\n", *child);
	exit(1);
}
