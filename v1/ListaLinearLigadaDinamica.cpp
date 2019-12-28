#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
	// outros campos	
} REGISTRO;

typedef struct aux {
	REGISTRO reg;
	struct aux* prox;	
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
	PONT inicio;
} LISTA;

void iniciarLista (LISTA* l) {
	l->inicio = NULL;
	printf("\nLISTA INICIADA\n");
}

void reiniciarLista (LISTA* l) {
	printf("\n\nLISTA REINICIADA");

	while(l->inicio != NULL) {
		printf("\nMemoria liberada: \t\tChave: [%i]", l->inicio->reg.chave);
		PONT end = l->inicio->prox;
		free(l->inicio);
		l->inicio = end;
	}
	printf("\n");
}

int obterTamanho (LISTA* l) {
	PONT end = l->inicio;
	int tam = 0;

	while(end != NULL) {
		tam++;
		end = end->prox;
	}
	return tam;
}

void exibirLista (LISTA* l) {
	PONT end = l->inicio;

	printf("\n\nQtde. Elementos Lista: %i", obterTamanho(l));

	printf("\n[ ");

	while(end != NULL) {
		printf("%i, ", end->reg.chave);
		end = end->prox;	
	}

	printf(" ]\n");
}

PONT buscarElementoListaOrd(LISTA* l, TIPOCHAVE ch) {
	PONT end = l->inicio;

	while(end != NULL && ch > end->reg.chave)
		end = end->prox;

	if (end != NULL && ch == end->reg.chave)
		return end;

	return NULL;
}

PONT obterPosicaoNo(LISTA* l, TIPOCHAVE chave, PONT* ant) {
	PONT atual = l->inicio;

	while(atual != NULL && chave > atual->reg.chave) {
		*ant = atual;
		atual = atual->prox;		
	}

	if (atual != NULL && chave == atual->reg.chave)
		return atual;

	return NULL;
}

bool inserirElementoListaOrd (LISTA* l, REGISTRO reg) {
	PONT ant = NULL;

	if (obterPosicaoNo(l, reg.chave, &ant) != NULL)
		return false;

	PONT novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->reg = reg;

	if (ant == NULL) {
		novo->prox = l->inicio;
		l->inicio = novo;
	} else {
		novo->prox = ant->prox;
		ant->prox = novo;
	}

	printf("\nRegistro Incluido: \t\tChave [%i]", reg.chave);
	return true;
}

bool excluirElementoLista(LISTA* l, TIPOCHAVE chave) {
	PONT ant = NULL;
	PONT atual = NULL;

	if ((atual = obterPosicaoNo(l, chave, &ant)) == NULL) {
		printf("\nElemento nao encontrado: \tChave: %i", chave);
		return false;
	}

	if (ant == NULL) {
		l->inicio = atual->prox;
	} else {
		ant->prox = atual->prox;
	}

	free(atual);

	printf("\nElemento excluido: \t\tChave: %i", chave);
	return true;
}

int main() {

	REGISTRO reg;

	LISTA l;
	iniciarLista(&l);
	exibirLista(&l);

	reg.chave = 5;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 9;//
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