#include <stdio.h>
#include <string.h>

int main (int argc, char **argv, char **envp)
{
	printf("tenta saltar para segmento de dados\n");

	char *x = "ops";

	goto *((void *) x);

	return 0;
}

