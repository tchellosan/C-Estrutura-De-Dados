#include <stdio.h>
#include <malloc.h>

#define NUM_REG	11
#define TRUE	1
#define FALSE	0

typedef	int	bool;
typedef int TIPOCHAVE;

struct REGISTRO{
	TIPOCHAVE chave;
	int info;
};

typedef struct no{
	struct REGISTRO reg;
	struct no *esq, *dir;
	int h;
} NO, *PONT;

PONT iniciar(){
	return NULL;
}

PONT criarNo(struct REGISTRO reg){
	PONT novo = (PONT) malloc(sizeof(NO));
	novo->reg = reg;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->h = 0;

	return novo;
}

int altura(PONT no){
	if (!no)
		return -1;
	return no->h;
}

int max(int a, int b){
	if (a > b)
		return a;

	return b;
}

PONT direita(PONT r){
	PONT no;
	no 		= r->esq;
	r->esq 	= no->dir;
	no->dir = r;

	r->h = max(altura(r->dir), altura(r->esq)) + 1;
	no->h = max(altura(no->esq), r->h) + 1;

	return no;
}

PONT esquerda(PONT r){
	PONT no;
	no 		= r->dir;
	r->dir 	= no->esq;
	no->esq = r;

	r->h = max(altura(r->esq), altura(r->dir)) + 1;
	no->h = max(altura(no->dir), r->h) + 1;

	return no;
}

PONT esquerdaDireita(PONT r){
	r->esq = esquerda(r->esq);
	return direita(r);
}

PONT direitaEsquerda(PONT r){
	r->dir = direita(r->dir);
	return esquerda(r);
}

PONT inserirNo(PONT r, struct REGISTRO reg){
	if (!r)
		return criarNo(reg);

	if (reg.chave < r->reg.chave){
		r->esq = inserirNo(r->esq, reg);
		if ((altura(r->esq) - altura(r->dir)) == 2) {
			if (reg.chave < r->esq->reg.chave)
				r = direita(r);
			else
				r = esquerdaDireita(r);
		}
	} else if (reg.chave > r->reg.chave){
		r->dir = inserirNo(r->dir, reg);
		if ((altura(r->dir) - altura(r->esq)) == 2) {
			if (reg.chave > r->dir->reg.chave)
				r = esquerda(r);
			else
				r = direitaEsquerda(r);
		}
	}

	r->h = max(altura(r->esq), altura(r->dir)) + 1;

	return r;
}

void exibir(PONT r) {
	if (!r)
		return;

	printf("\n%i\th:%i ", r->reg.chave, r->h);
	exibir(r->esq);
	exibir(r->dir);
}

int main(int argc, char const *argv[]){
	PONT r;
	int inc[NUM_REG] = {15, 27, 49, 10, 8, 67, 59, 9, 13, 20, 14};
	struct REGISTRO reg[NUM_REG];

	r = iniciar();

	for (int i = 0; i < 11; ++i) {
		reg[i].chave = inc[i];
		r = inserirNo(r, reg[i]);
	}
	
	printf("\nArvore AVL:\n");
	exibir(r);
	printf("\n");

	return 0;
}