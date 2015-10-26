#include "libbb.h"

//usage:#define newcmd_trivial_usage	"None"
//usage:#define newcmd_full_usage	"None"

int newcmd_main(int argc, char *argv[])
{
	int i;
	
	printf("newcmd called:\n");
	for(i = 0; i < argc; i++)
	{
		printf("arg[%d] = %s\n", i, argv[i]);
	}

	return 0;
}
