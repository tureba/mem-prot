#include <stdio.h>
#include <string.h>

int main (int argc, char **argv, char **envp)
{
	printf("tenta escrever em segmento inexistente\n");

	char x[10];
	int n = 1000000;

	strcpy(x + n, "ops");

	return 0;
}

