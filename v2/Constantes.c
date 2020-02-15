#define MAX				10
#define true			1
#define false			0
#define NAO_ENCONTRADO	-1
#define FIM_LISTA		-1

typedef int TIPOCHAVE;
typedef int bool;

typedef struct{
	TIPOCHAVE chave;
	char info[50];
} REGISTRO;