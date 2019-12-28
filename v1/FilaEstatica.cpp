#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5

typedef int TIPOCHAVE;

struct CLIENTE {
	TIPOCHAVE codigo;
	char nome[30];
	double saldo;
};

struct FILA {
	CLIENTE cliente[MAX];
	int inicio;
	int qtdeclientes;
};

void iniciarFila(FILA* f) {
	f->inicio = 0;
	f->qtdeclientes = 0;

	if (f->inicio >= MAX) {
		printf("\nVariavel [inicio] nao pode ser maior ou igual a MAX\n");
		exit(0);
	}

	if (f->qtdeclientes > MAX) {
		printf("\nVariavel [qtdeclientes] nao pode ser maior que MAX\n");
		exit(0);
	}	
}

void reiniciarFila(FILA* f) {
	iniciarFila(f);
}

int qtdeElementosFila(FILA* f) {
	return f->qtdeclientes;
}

void exibirElementosFila(FILA* f) {
	int qtdeImpressao, i;

	for (qtdeImpressao = 0, i = f->inicio; qtdeImpressao < f->qtdeclientes; qtdeImpressao++, i++) {
		printf("\nCodigo: %i\tNome: %s\tSaldo: R$ %.2f", f->cliente[i].codigo, f->cliente[i].nome, f->cliente[i].saldo);
		i = (i + 1) % MAX;
	}
}

bool inserirElementosFila(FILA* f, CLIENTE cliente) {
	if (qtdeElementosFila(f) >= MAX) {
		printf("\nFila cheia, nao foi possivel incluir o cliente: %i - %s", cliente.codigo, cliente.nome);
		return false;
	}

	int pos = (f->inicio + f->qtdeclientes) % MAX;

	f->cliente[pos] = cliente;
	f->qtdeclientes++;

	return true;
}

bool excluirElementosFila(FILA* f, CLIENTE* cliente) {
	if (qtdeElementosFila(f) == 0) {
		printf("\nFila vazia");
		return false;
	}

	*cliente = f->cliente[f->inicio];

	f->inicio = (f->inicio + 1) % MAX;
	f->qtdeclientes -= 1;

	return true;
}


int main() {
	CLIENTE cliente;
	FILA f;

	iniciarFila(&f);
	printf("\nFila iniciada\n");

	cliente.codigo = 1;
	strcpy(cliente.nome, "Marcelo");
	cliente.saldo = 1500.15;
	if (inserirElementosFila(&f, cliente))
		printf("\nCliente incluido");

	cliente.codigo = 2;
	strcpy(cliente.nome, "Dayana");
	cliente.saldo = 3256.27;

	if (inserirElementosFila(&f, cliente))
		printf("\nCliente incluido");

	cliente.codigo = 3;
	strcpy(cliente.nome, "Lucca");
	cliente.saldo = 5000.55;
	if (inserirElementosFila(&f, cliente))
		printf("\nCliente incluido");

	cliente.codigo = 4;
	strcpy(cliente.nome, "Renata");
	cliente.saldo = 6000.60;
	if (inserirElementosFila(&f, cliente))
		printf("\nCliente incluido");

	cliente.codigo = 5;
	strcpy(cliente.nome, "Rafaela");
	cliente.saldo = 7200.70;
	if (inserirElementosFila(&f, cliente))
		printf("\nCliente incluido");

	cliente.codigo = 6;
	strcpy(cliente.nome, "Nisauro");
	cliente.saldo = 8500.10;
	if (inserirElementosFila(&f, cliente))
		printf("\nCliente incluido");

	if (excluirElementosFila(&f, &cliente))
		printf("\nCliente excluido");	
	if (excluirElementosFila(&f, &cliente))
		printf("\nCliente excluido");	

	cliente.codigo = 7;
	strcpy(cliente.nome, "Quiteria");
	cliente.saldo = 9000.27;
	if (inserirElementosFila(&f, cliente))
		printf("\nCliente incluido");
/*
	if (excluirElementosFila(&f, &cliente))
		printf("\nCliente excluido");	
	if (excluirElementosFila(&f, &cliente))
		printf("\nCliente excluido");	
	if (excluirElementosFila(&f, &cliente))
		printf("\nCliente excluido");	
	if (excluirElementosFila(&f, &cliente))
		printf("\nCliente excluido");	
	if (excluirElementosFila(&f, &cliente))
		printf("\nCliente excluido");	
*/
	printf("\n\nQtde. clientes Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
/*
	reiniciarFila(&f);
	printf("\n\nFila re-iniciada\n");

	printf("\nQtde. clientes Fila: %i\n", qtdeElementosFila(&f));
	exibirElementosFila(&f);
*/
	printf("\n");
	return 0;
}