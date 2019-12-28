#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
	int info;
} REGISTRO;

typedef struct ELEMENTO {
	REGISTRO reg;
	struct ELEMENTO* prox;
} NO;

typedef struct {
	NO* cabeca;
} LISTA;

void iniciarLista(LISTA* l) {
	l->cabeca = (NO*) malloc(sizeof(NO));
	l->cabeca->prox = l->cabeca;
}

void reiniciarLista(LISTA* l) {
	NO* atual = l->cabeca->prox;

	while(atual != l->cabeca) {
		NO* apagar = atual;
		printf("\nMemoria liberada: \t\tChave: [%i]", apagar->reg.chave);
		atual = atual->prox;
		free(apagar);
	}

	l->cabeca->prox = l->cabeca;
}

int obterTamanho(LISTA* l) {
	int tam = 0;
	NO* no = l->cabeca->prox;
	while(no != l->cabeca) {
		tam++;
		no = no->prox;
	}
	return tam;
}

void exibirLista(LISTA* l) {
	NO* no = l->cabeca->prox;

	printf("\n\nQtde. Elementos Lista: %i", obterTamanho(l));

	printf("\n[ ");

	while(no != l->cabeca) {
		printf("%i, ", no->reg.chave);
		no = no->prox;
	}

	printf(" ]\n");
}

NO* buscarNoSentinela(LISTA* l, TIPOCHAVE chave) {
	NO* no = l->cabeca->prox;
	l->cabeca->reg.chave = chave;

	while(no->reg.chave != chave)
		no->prox;

	if (no != l->cabeca)
		return no;

	return NULL;
}

NO* buscarNoSentinelaOrdenada(LISTA* l, TIPOCHAVE chave) {
	NO* no = l->cabeca->prox;
	l->cabeca->reg.chave = chave;

	while(no->reg.chave < chave)
		no->prox;

	if (no != l->cabeca && no->reg.chave == chave)
		return no;

	return NULL;
}

NO* buscarElementoLista(LISTA* l, TIPOCHAVE chave, NO** ant) {
	NO* atual = l->cabeca->prox;
	l->cabeca->reg.chave = chave;

	while(atual->reg.chave < chave) {
		*ant = atual;
		atual = atual->prox;
	}

	if (atual != l->cabeca && atual->reg.chave == chave)
		return atual;

	return NULL;
}


bool inserirElementoListaOrd(LISTA* l, REGISTRO reg) {
	NO* ant = l->cabeca;
	NO* atual = buscarElementoLista(l, reg.chave, &ant);

	if (atual)
		return false;

	NO* novo = (NO*) malloc(sizeof(NO));
	novo->reg = reg;
	novo->prox = ant->prox;
	ant->prox = novo;

	printf("\nRegistro Incluido: \t\tChave [%i]", reg.chave);
	return true;
}

bool excluirElementoLista(LISTA* l, TIPOCHAVE chave) {
	NO* ant = l->cabeca;
	NO* atual = buscarElementoLista(l, chave, &ant);

	if (!atual) {
		printf("\nElemento nao encontrado: \tChave: %i", chave);
		return false;
	}

	ant->prox = atual->prox;
	free(atual);

	printf("\nRegistro Excluido: \t\tChave [%i]", chave);
	return true;
}

int main() {

	REGISTRO reg;

	LISTA l;
	iniciarLista(&l);
	exibirLista(&l);

	reg.chave = 5;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 9;
	inserirElementoListaOrd(&l, reg);	
	reg.chave = 7;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 7;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 8;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 1;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 15;
	inserirElementoListaOrd(&l, reg);
	
	exibirLista(&l);

	excluirElementoLista(&l, 8);
	excluirElementoLista(&l, 22);
	excluirElementoLista(&l, 1);

	exibirLista(&l);

	reiniciarLista(&l);
	exibirLista(&l);

	return 0;
}