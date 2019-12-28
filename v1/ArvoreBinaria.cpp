#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define NUM_OCURRS 10

// ARVORE BINARIA
typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE chave;
	int info;
};

struct NO {
	REGISTRO reg;
	NO *esq, *dir;
};

typedef NO* ARVORE;

// PILHA CONTAGEM
struct ELEMENTO {
	NO* end_no;
	ELEMENTO* prox;
};

struct PILHA {
	ELEMENTO* topo;
};

void iniciarPilha(PILHA* p) {
	p->topo = NULL;
}

void push(PILHA* p, NO* no) {
	ELEMENTO* novo = (ELEMENTO*) malloc(sizeof(ELEMENTO));
	novo->end_no = no;
	novo->prox = p->topo;
	p->topo = novo;
}

NO* pop(PILHA* p) {
	if (!p->topo)
		return NULL;

	ELEMENTO* atual = p->topo;
	p->topo = atual->prox;
	NO* end_no = atual->end_no;	
	free(atual);
	return end_no;
}

void iniciarArvore(ARVORE* raiz) {
	*raiz = NULL;
}

bool inserirNo(ARVORE* no_atual, REGISTRO reg) {

	while(*no_atual != NULL) {
		if (reg.chave > (*no_atual)->reg.chave) {
			no_atual = &((*no_atual)->dir);
		} else if (reg.chave < (*no_atual)->reg.chave) {
			no_atual = &((*no_atual)->esq);
		}
	}

	NO* novo = (NO*) malloc(sizeof(NO));
	novo->reg = reg;
	novo->esq = NULL;
	novo->dir = NULL;
	*no_atual = novo;

	return true;
}

NO* buscarNo(ARVORE* raiz, TIPOCHAVE chave, NO** pai = NULL) {
	NO* atual = *raiz;

	if (pai)
		*pai = NULL;

	while(atual != NULL) {
		if (chave == atual->reg.chave)
			return atual;

		if (pai)
			*pai = atual;

		if (chave > atual->reg.chave)
			atual = atual->dir;
		else 
			atual = atual->esq;
	}	

	return NULL;
}

int contarNo(ARVORE* raiz) {
	int qtde = 0;

	PILHA p;
	iniciarPilha(&p);

	NO* atual = *raiz;

	do {
		while(atual) {
			qtde++;

			if (atual->dir)
				push(&p, (atual->dir));

			atual = (atual->esq);
		}
	} while (atual = pop(&p));

	return qtde;
}

void exibirArvore(ARVORE* raiz) {
	PILHA p;
	iniciarPilha(&p);

	NO* atual = *raiz;

	printf("[ ");
	do {
		while(atual) {
			//printf("\nChave: [%i]", atual->reg.chave);
			printf("%i, ", atual->reg.chave);
			
			if (atual->dir)
				push(&p, (atual->dir));

			atual = (atual->esq);
		}
	} while (atual = pop(&p));
	printf("]");
}

bool removerNo(ARVORE* no_atual, TIPOCHAVE chave) {
	NO* pai_no_remover = NULL;
	NO* no_remover = NULL;

	if (!(no_remover = buscarNo(no_atual, chave, &pai_no_remover)))
		return false;

	if (no_remover->esq != NULL) {
		NO* pai_no_promo = NULL;
		NO* no_promo = no_remover->esq;

		while(no_promo->dir) {
			pai_no_promo = no_promo;
			no_promo = no_promo->dir;				
		}

		if (pai_no_promo) {
			pai_no_promo->dir = no_promo->esq;
			no_promo->esq = no_remover->esq;
		}
		
		no_promo->dir = no_remover->dir;

		if (pai_no_remover) {
			if (no_promo->reg.chave > pai_no_remover->reg.chave)
				pai_no_remover->dir = no_promo;
			else
				pai_no_remover->esq = no_promo;
		} else {
			*no_atual = no_promo;	
		}
	} else {
		if (pai_no_remover) {
			if (no_remover->reg.chave > pai_no_remover->reg.chave)
				pai_no_remover->dir = no_remover->dir;
			else
				pai_no_remover->esq = no_remover->dir;
		} else {
			*no_atual = no_remover->dir;
		}
	}

	free(no_remover);
	return true;
}

int main(int argc, char const *argv[]) {
	ARVORE raiz;
	iniciarArvore(&raiz);

	REGISTRO reg[NUM_OCURRS];
	//int chave[12] = {23,12,35,10,5,4,20,37,48,25,80,30};
	//int chave[NUM_OCURRS] = {18, 8, 2, 14, 16, 10, 9, 12, 11};
	int chave[NUM_OCURRS] = {15, 8, 2, 12, 1, 6, 4, 23, 20, 30};

	for (int i = 0; i < NUM_OCURRS; ++i) {
		reg[i].chave = chave[i];
		inserirNo(&raiz, reg[i]);
	}

	printf("\nQuatidade Nos: %i", contarNo(&raiz));
	printf("\n");
	exibirArvore(&raiz);
	printf("\n");
/*
	NO* reg_busca;
	reg_busca = buscarNo(&raiz, 10);
	if (reg_busca != NULL)
		printf("\nChave encontrada: [%i]", reg_busca->reg.chave);
	else
		printf("\nChave nao encontrada");

	reg_busca = buscarNo(&raiz, 15);
	if (reg_busca != NULL)
		printf("\nChave [%i] encontrada", reg_busca->reg.chave);
	else
		printf("\nChave nao encontrada");	
*/

	removerNo(&raiz, 1);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(&raiz));
	printf("\n");
	exibirArvore(&raiz);
	printf("\n");

	removerNo(&raiz, 23);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(&raiz));
	printf("\n");
	exibirArvore(&raiz);
	printf("\n");

	removerNo(&raiz, 15);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(&raiz));
	printf("\n");
	exibirArvore(&raiz);
	printf("\n");	

	removerNo(&raiz, 12);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(&raiz));
	printf("\n");
	exibirArvore(&raiz);
	printf("\n");		


	printf("\n");
	return 0;
}