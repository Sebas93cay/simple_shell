#include "headershell.h"

void __attribute__ ((constructor)) premain()
{
	environ = words_cpy(environ);
}
