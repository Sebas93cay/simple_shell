#include "../headershell.h"

int main(int argc, char **argv, char **env)
{
	_printf("**********************************************\n");
	_printenv();
	setenv("LAVAR", "51", 0);
	setenv("LAVAR2", "52", 0);
	_printf("**********************************************\n");
	_printenv();
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
	printf("main---- &env = %p\n", &env);
	printf("main &environ = %p\n", &environ);
	return (0);
}
