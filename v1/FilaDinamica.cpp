#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE codigo;
	char nome[30];
	double saldo;
};

struct CLIENTE {
	REGISTRO reg;
	CLIENTE* prox;
};

struct FILA {
	CLIENTE* primeiro;
	CLIENTE* ultimo;
};

void iniciarFila(FILA* f) {
	f->primeiro = NULL;
	f->ultimo = NULL;
}

int qtdeElementosFila(FILA* f) {
	CLIENTE* cliente = f->primeiro;
	int qtde = 0;
	while(cliente){
		qtde++;
		cliente = cliente->prox;
	}
	return qtde;
}

void exibirElementosFila(FILA* f) {
	CLIENTE* cliente = f->primeiro;

	while(cliente){
		printf("\nCodigo: %i\tNome: %s\tSaldo: R$ %.2f", cliente->reg.codigo, cliente->reg.nome, cliente->reg.saldo);
		cliente = cliente->prox;
	}
}

bool inserirElementosFila(FILA* f, REGISTRO reg) {
	CLIENTE* novo = (CLIENTE*) malloc(sizeof(CLIENTE));
	novo->reg = reg;
	novo->prox = NULL;

	if (f->primeiro == NULL)
		f->primeiro = novo;
	else 
		f->ultimo->prox = novo;	

	f->ultimo = novo;

	return true;
}

bool excluirElementosFila(FILA* f, REGISTRO* reg = NULL) {
	if (f->primeiro == NULL)
		return false;

	CLIENTE* cliente = f->primeiro;

	if(reg)
		*reg = cliente->reg;
	
	f->primeiro = cliente->prox;
	free(cliente);

	if (!f->primeiro)
		f->ultimo = NULL;

	return true;
}

void reiniciarFila(FILA* f) {
	while(excluirElementosFila(f));
}

int main() {
	REGISTRO reg;
	FILA f;

	iniciarFila(&f);
	printf("\nFila iniciada\n");
	printf("\nQtde. Elementos Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
	printf("\n");

	reg.codigo = 1;
	strcpy(reg.nome, "Marcelo");
	reg.saldo = 1500.15;
	if (inserirElementosFila(&f, reg))
		printf("\nCliente incluido");

	if (excluirElementosFila(&f, &reg))
		printf("\nCliente removido");	

	printf("\nQtde. Elementos Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
	printf("\n");

	reg.codigo = 2;
	strcpy(reg.nome, "Dayana");
	reg.saldo = 3256.27;
	if (inserirElementosFila(&f, reg))
		printf("\nCliente incluido");

/*
	reg.codigo = 3;
	strcpy(reg.nome, "Lucca");
	reg.saldo = 5000.55;
	if (inserirElementosFila(&f, reg))
		printf("\nCliente incluido");

	printf("\nQtde. Elementos Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
	printf("\n");

	if (excluirElementosFila(&f, &reg))
		printf("\nCliente removido");	

	printf("\nQtde. Elementos Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
	printf("\n");

	reg.codigo = 4;
	strcpy(reg.nome, "Renata");
	reg.saldo = 6000.60;
	if (inserirElementosFila(&f, reg))
		printf("\nCliente incluido");

	reg.codigo = 5;
	strcpy(reg.nome, "Rafaela");
	reg.saldo = 7200.70;
	if (inserirElementosFila(&f, reg))
		printf("\nCliente incluido");

	if (excluirElementosFila(&f, &reg))
		printf("\nCliente removido");	
	if (excluirElementosFila(&f, &reg))
		printf("\nCliente removido");		

	printf("\nQtde. Elementos Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
	printf("\n");

	reg.codigo = 6;
	strcpy(reg.nome, "Nisauro");
	reg.saldo = 8500.10;
	if (inserirElementosFila(&f, reg))
		printf("\nCliente incluido");

	reg.codigo = 7;
	strcpy(reg.nome, "Quiteria");
	reg.saldo = 9000.27;
	if (inserirElementosFila(&f, reg))
		printf("\nCliente incluido");

*/

	printf("\nQtde. Elementos Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
	printf("\n");
/*
	reiniciarFila(&f);
	printf("\nFila re-iniciada\n");
	printf("\nQtde. Elementos Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
	printf("\n");
*/
	return 0;
}