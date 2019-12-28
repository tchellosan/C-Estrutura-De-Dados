#include <stdio.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct no {
	REGISTRO reg;
	struct no *prox;
} NO;

typedef struct{
	NO *cabeca;
} LISTA;

void iniciarLista(LISTA *l){
	l->cabeca = (NO*)malloc(sizeof(NO));
	l->cabeca->prox = l->cabeca;
}

void exibirLista(LISTA *l){
	NO* atual = l->cabeca->prox;

	while(atual != l->cabeca){
		printf("\n[%d]", atual->reg.chave);
		atual = atual->prox;
	}
}

NO* primeiroElemento(LISTA *l){
	return (l->cabeca == l->cabeca->prox) ? NULL : l->cabeca->prox;
}

NO* ultimoElemento(LISTA *l){
	NO* atual = l->cabeca->prox;

	if (atual == l->cabeca)
		return NULL;

	while(atual->prox != l->cabeca){
		atual = atual->prox;
	}
	return atual;
}

NO* enesimoElemento(LISTA *l, int n){
	NO* atual = l->cabeca->prox;
	int i = 0;

	while(atual != l->cabeca && i < n){
		atual = atual->prox;
		i++;
	}		

	if (atual == l->cabeca)
		return NULL;
	else 
		return atual;
}

int tamanhoLista(LISTA *l){
	NO* atual = l->cabeca->prox;
	int i = 0;

	while(atual != l->cabeca){
		i++;
		atual = atual->prox;
	}

	return i;
}

NO* buscaSeqOrd(LISTA* l, TIPOCHAVE chave, NO** ant){
	NO* atual = l->cabeca->prox;
	*ant = l->cabeca;

	while(atual != l->cabeca){
		if (atual->reg.chave >= chave)
			break;

		*ant = atual;
		atual = atual->prox;
	}

	if (atual != l->cabeca && chave == atual->reg.chave)
		return atual;

	return NULL;
}

bool inserirElementoLista(LISTA *l, REGISTRO reg){
	NO *ant;
	NO *novo = buscaSeqOrd(l, reg.chave, &ant);

	if (novo)
		return false;

	novo = (NO*) malloc(sizeof(NO));
	novo->reg = reg;
	novo->prox = ant->prox;
	ant->prox = novo;

	return true;
}

void inserirElementoListaFim(LISTA *l, REGISTRO reg){
	NO* novo = (NO*) malloc(sizeof(NO));
	NO* ult = ultimoElemento(l);

	novo->reg = reg;

	if(!ult){
		novo->prox = l->cabeca->prox;
		l->cabeca->prox = novo;
	} else {
		novo->prox = ult->prox;
		ult->prox = novo;
	}
}

bool excluirElementoLista(LISTA *l, TIPOCHAVE chave){
	NO* ant;
	NO* excluir = buscaSeqOrd(l, chave, &ant);

	if (!excluir)
		return false;

	ant->prox = excluir->prox;

	free(excluir);
	return true;
}

void destruirLista(LISTA *l){
	NO* cabeca;

	while(l->cabeca->prox != l->cabeca){
		cabeca = l->cabeca->prox->prox;
		free(l->cabeca->prox);
		l->cabeca->prox = cabeca;
	}
}

int main(int argc, char const *argv[]) {

	LISTA l;
	REGISTRO reg;
	iniciarLista(&l);

	iniciarLista(&l);
	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	exibirLista(&l);

	reg.chave = 20;
	if (inserirElementoLista(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);
	reg.chave = 42;
	if (inserirElementoLista(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);	
	reg.chave = 10;
	if (inserirElementoLista(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);
	reg.chave = 30;
	if (inserirElementoLista(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);	
	reg.chave = 40;
	if (inserirElementoLista(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);			
	reg.chave = 50;
	inserirElementoListaFim(&l, reg);
	printf("\nRegistro incluido. Chave [%d]", reg.chave);			


	printf("\n");

	reg.chave = 30;
	if (excluirElementoLista(&l, reg.chave))
		printf("\nRegistro excluido. Chave [%d]", reg.chave);			
	reg.chave = 10;
	if (excluirElementoLista(&l, reg.chave))
		printf("\nRegistro excluido. Chave [%d]", reg.chave);				
	reg.chave = 42;
	if (excluirElementoLista(&l, reg.chave))
		printf("\nRegistro excluido. Chave [%d]", reg.chave);					
	reg.chave = 50;
	if (excluirElementoLista(&l, reg.chave))
		printf("\nRegistro excluido. Chave [%d]", reg.chave);					
	
	reg.chave = 10;
	inserirElementoListaFim(&l, reg);
	printf("\nRegistro incluido. Chave [%d]", reg.chave);				
/*
	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	for (int i = 0; i < tamanhoLista(&l); ++i) {
		printf("\nElemento%d: [%d]", i,enesimoElemento(&l, i)->reg.chave);
	}
*/
//	destruirLista(&l);
/*
	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	for (int i = 0; i < tamanhoLista(&l); ++i) {
		printf("\nElemento%d: [%d]", i,enesimoElemento(&l, i)->reg.chave);
	}
*/

	printf("\n");
	printf("\nPrimeiro elemento: [%d]", primeiroElemento(&l)->reg.chave);
	printf("\nUltimo elemento: [%d]", ultimoElemento(&l)->reg.chave);
	printf("\n");

	printf("\n\n");
	return 0;
}