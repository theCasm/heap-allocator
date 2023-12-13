#include <stdio.h>
#include <string.h>
#include "../../src/myalloc.h"

int main(void)
{
	char *str = myalloc(19);
	strcpy(str, "Writing a string!\n");
	fputs(str, stdout);
	myfree(str);
	return 0;
}
