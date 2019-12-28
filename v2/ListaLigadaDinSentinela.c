#include <stdio.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct no {
	REGISTRO reg;
	struct no *prox;
} NO;

typedef struct{
	NO *inicio;
	NO *sentinela;
} LISTA;

void iniciarLista(LISTA *l){
	l->sentinela = (NO*)malloc(sizeof(NO));
	l->inicio = l->sentinela;
}

void exibirLista(LISTA *l){
	NO* atual = l->inicio;

	while(atual != l->sentinela){
		printf("\n[%d]", atual->reg.chave);
		atual = atual->prox;
	}
}

NO* primeiroElemento(LISTA *l){
	return (l->inicio == l->sentinela) ? NULL : l->inicio;
}

NO* ultimoElemento(LISTA *l){
	NO* atual = l->inicio;

	if (atual == l->sentinela)
		return NULL;

	while(atual->prox != l->sentinela){
		atual = atual->prox;
	}
	return atual;
}

NO* enesimoElemento(LISTA *l, int n){
	NO* atual = l->inicio;
	int i = 0;

	while(atual != l->sentinela && i < n){
		atual = atual->prox;
		i++;
	}		

	if (atual == l->sentinela)
		return NULL;
	else 
		return atual;
}

int tamanhoLista(LISTA *l){
	NO* atual = l->inicio;
	int i = 0;

	while(atual != l->sentinela){
		i++;
		atual = atual->prox;
	}

	return i;
}

NO* buscaSeqOrd(LISTA* l, TIPOCHAVE chave, NO** ant){
	NO* atual = l->inicio;
	*ant = NULL;

	while(atual){
		if (atual->reg.chave >= chave)
			break;

		*ant = atual;
		atual = atual->prox;
	}

	if (atual != l->sentinela && chave == atual->reg.chave)
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

	if (ant == NULL){
		novo->prox = l->inicio;
		l->inicio = novo;
	} else {
		novo->prox = ant->prox;
		ant->prox = novo;
	}

	return true;
}

void inserirElementoListaFim(LISTA *l, REGISTRO reg){
	NO* novo = (NO*) malloc(sizeof(NO));
	NO* ult = ultimoElemento(l);

	novo->reg = reg;
	novo->prox = l->sentinela;

	if(!ult)
		l->inicio = novo;
	else
		ult->prox = novo;
}

bool excluirElementoLista(LISTA *l, TIPOCHAVE chave){
	NO* ant;
	NO* excluir = buscaSeqOrd(l, chave, &ant);

	if (!excluir)
		return false;

	if(!ant)
		l->inicio = excluir->prox;
	else
		ant->prox = excluir->prox;

	free(excluir);
	return true;
}

void destruirLista(LISTA *l){
	NO* inicio;

	while(l->inicio != l->sentinela){
		inicio = l->inicio->prox;
		free(l->inicio);
		l->inicio = inicio;
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

/*
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

	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	for (int i = 0; i < tamanhoLista(&l); ++i) {
		printf("\nElemento%d: [%d]", i,enesimoElemento(&l, i)->reg.chave);
	}
*/
//	destruirLista(&l);

	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	for (int i = 0; i < tamanhoLista(&l); ++i) {
		printf("\nElemento%d: [%d]", i,enesimoElemento(&l, i)->reg.chave);
	}


/*
	printf("\n");
	printf("\nPrimeiro elemento: [%d]", primeiroElemento(&l)->reg.chave);
	printf("\nUltimo elemento: [%d]", ultimoElemento(&l)->reg.chave);
	printf("\n");
*/

	printf("\n\n");
	return 0;
}