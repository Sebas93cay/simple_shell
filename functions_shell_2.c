#include "headershell.h"

void __attribute__ ((constructor)) premain()
{
	environ = words_cpy(environ);
}


void ignore_signal(int sig)
{
	write(1, "\n", 1);
	if (isatty(0))
		_printf("#cisfun$ "); /*print only in terminal*/
	signal(sig, SIG_IGN);
	signal(sig, ignore_signal);
}

