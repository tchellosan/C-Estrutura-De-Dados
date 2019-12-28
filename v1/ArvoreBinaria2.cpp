#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define NUM_OCURRS 10

typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE chave;
	int info;
};

struct NO {
	REGISTRO reg;
	NO *esq, *dir;
};

typedef NO* PONT;

PONT iniciarArvore() {
	return NULL;
}

PONT criarNo(REGISTRO reg) {
	PONT novo = (PONT) malloc(sizeof(NO));
	novo->reg = reg;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

PONT inserirNo(PONT raiz, PONT no) {
	if (raiz == NULL)
		return no;

	if (no->reg.chave > raiz->reg.chave)
		raiz->dir = inserirNo(raiz->dir, no);
	else if (no->reg.chave < raiz->reg.chave)
		raiz->esq = inserirNo(raiz->esq, no);

	return raiz;
}

PONT buscarNo(PONT raiz, TIPOCHAVE chave) {
	if (raiz == NULL) return NULL;

	if (raiz->reg.chave == chave)
		return raiz;

	if (chave > raiz->reg.chave)
		return buscarNo(raiz->dir, chave);

	return buscarNo(raiz->esq, chave);

}

int contarNo(PONT raiz) {
	if (raiz == NULL) return 0;

	return 1 + contarNo(raiz->esq) + contarNo(raiz->dir);
}

void exibirArvore(PONT raiz) {
	if (raiz != NULL) {
		printf(" %i,", raiz->reg.chave);
//		printf("%i", raiz->reg.chave);
//		printf(" (", raiz->reg.chave);
		exibirArvore(raiz->esq);
		exibirArvore(raiz->dir);
//		printf(") ", raiz->reg.chave);
	}
}

PONT buscarNo2(PONT raiz, TIPOCHAVE chave, PONT *pai) {
	PONT atual = raiz;
	*pai = NULL;

	while(atual) {
		if (atual->reg.chave == chave)
			return atual;

		*pai = atual;
		if (chave < atual->reg.chave)
			atual = atual->esq;
		else
			atual = atual->dir;
	}
	return NULL;
}

PONT removerNo(PONT raiz, TIPOCHAVE chave) {
	PONT pai, no, p, q;

	no = buscarNo2(raiz, chave, &pai);

	if (no == NULL)
		return raiz;

	if (!no->esq || !no->dir) {
		if (!no->esq)
			q = no->dir;
		else
			q = no->esq;
	} else {
		p = no;
		q = no->esq;

		while(q->dir){
			p = q;
			q = q->dir;
		}

		if (p != no) {
			p->dir = q->esq;
			q->esq = no->esq;
		}
		q->dir = no->dir;
	}

	if (!pai) {
		free(no);
		return q;
	}

	if (chave < pai->reg.chave) 
		pai->esq = q;
	else 
		pai->dir = q;

	free(no);
	
	return raiz;
}

int main(int argc, char const *argv[]) {
	PONT raiz = iniciarArvore();

	REGISTRO reg[NUM_OCURRS];
	//int chave[12] = {23,12,35,10,5,4,20,37,48,25,80,30};
	int chave[NUM_OCURRS] = {15, 8, 2, 12, 1, 6, 4, 23, 20, 30};

	for (int i = 0; i < NUM_OCURRS; ++i) {
		reg[i].chave = chave[i];
		raiz = inserirNo(raiz, criarNo(reg[i]));
	}

	printf("\nQuatidade Nos: %i", contarNo(raiz));
	printf("\n");
	exibirArvore(raiz);
	printf("\n");
/*
	NO* reg_busca;
	reg_busca = buscarNo(raiz, 10);
	if (reg_busca != NULL)
		printf("\nChave encontrada: [%i]\n", reg_busca->reg.chave);
	else
		printf("\nChave nao encontrada");

	reg_busca = buscarNo(raiz, 15);
	if (reg_busca != NULL)
		printf("\nChave [%i] encontrada\n", reg_busca->reg.chave);
	else
		printf("\nChave nao encontrada");	
*/
/*
	raiz = removerNo(raiz, 1);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(raiz));
	printf("\n");
	exibirArvore(raiz);
	printf("\n");
*/
	raiz = removerNo(raiz, 1);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(raiz));
	printf("\n");
	exibirArvore(raiz);
	printf("\n");

	raiz = removerNo(raiz, 23);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(raiz));
	printf("\n");
	exibirArvore(raiz);
	printf("\n");

	raiz = removerNo(raiz, 15);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(raiz));
	printf("\n");
	exibirArvore(raiz);
	printf("\n");		
	
	raiz = removerNo(raiz, 12);
	printf("\n");
	printf("\nQuatidade Nos: %i", contarNo(raiz));
	printf("\n");
	exibirArvore(raiz);
	printf("\n");		

	printf("\n");
	return 0;
}