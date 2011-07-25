#include <stdio.h>
#include <string.h>

int main (int argc, char **argv, char **envp)
{
	printf("tenta escrever em segmento de código\n");

ops:
	strcpy((char *) &&ops, "ops");

	return 0;
}

