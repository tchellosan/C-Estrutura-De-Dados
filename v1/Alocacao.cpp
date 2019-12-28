#include <stdio.h>
#include <malloc.h>

int main(int argc, char const *argv[])
{
	int* y = (int*) malloc(sizeof(int));
	*y = 20;
	int z = sizeof(int);

	printf("valor de *y=%i (Qtde. bytes z=%i)\n", *y, z);
	return 0;
}