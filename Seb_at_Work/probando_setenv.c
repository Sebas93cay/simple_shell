#include "../headershell.h"

int main(int argc, char **argv, char **env)
{

	_printf("----env = %p  ---&envn = %p \n", env, &env);
	_printf("environ = %p  &environ = %p\n", environ, &environ);

	/* environ = malloc(sizeof(char *) * 3); */
	/* environ[0] = strdup("hola"); */
	/* environ[1] = strdup("bien"); */
	/* environ[2] = NULL; */
	_printf("**********************************************\n");
	environ = words_cpy(environ);
	_printenv();
	_printf("**********************************************\n");


	_setenv("LAVAR", "51", 0);
	_setenv("LAVAR2", "52", 0);
	_setenv("PATH", "EL NUEVO PATH", 0);
	_printenv();
	_printf("**********************************************\n");

	_setenv("PATH", "EL NUEVO PATH", 1);
	_setenv("LAVAR2", "53", 1);
	_printenv();
	_printf("**********************************************\n");

	_unsetenv("LAVAR2");
	_printenv();
	_printf("**********************************************\n");

	_unsetenv("PATH");
	_printenv();


	free_words(environ);
#if 0
	unsetenv("LAVAR");
	_printf("**********************************************\n");
	_printenv();
	unsetenv("LAVAR2");
	_printf("**********************************************\n");
	_printenv();

	_printf("**********************************************\n");
	_printf("**********************************************\n");
	_printenv();
	_setenv("LAVAR", "51", 0);
	_setenv("LAVAR2", "52", 0);
	_printf("**********************************************\n");
	_printenv();
	unsetenv("LAVAR");
	_printf("**********************************************\n");
	_printenv();
	unsetenv("LAVAR2");
	_printf("**********************************************\n");
	_printenv();
	_printf("main---- &env = %p\n", &env);
	_printf("main &environ = %p\n", &environ);
#endif

	return (0);
}
