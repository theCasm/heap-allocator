#include <stdio.h>
#include <string.h>
#include "../../src/myalloc.h"

int main(void)
{
	char *str = myalloc(19);
	strcpy(str, "Writing a string!\n");
	fprintf(stdout, "%p : %s", str, str);
	myfree(str);

	str = myalloc(18);
	strcpy(str, "recycled memory!\n");
	fprintf(stdout, "%p : %s", str, str);
	return 0;
}
