#include <stdio.h>
#include <string.h>

int main (int argc, char **argv, char **envp)
{
	printf("tenta escrever em segmento somente leitura\n");

	strcpy("dest","src");

	return 0;
}

