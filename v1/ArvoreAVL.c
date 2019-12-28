#include <stdio.h>
#include <malloc.h>

#define TRUE	1
#define	FALSE	0

#define NUM_REG	11

typedef int bool;
typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE chave;
	int info;
};

typedef struct no {
	struct REGISTRO reg;
	struct no *esq;
	struct no *dir;
	int h;
} NO, *PONT; 

void iniciar(PONT* r) {
	*r = NULL;
}

PONT criarNo(struct REGISTRO reg){
	PONT novo 	= (PONT) malloc(sizeof(NO));
	novo->reg 	= reg;
	novo->esq 	= NULL;
	novo->dir 	= NULL;
	novo->h		= 0;

	return novo;
}

int balanceamento(PONT r) {
	int esq, dir;

	esq = (!r->esq) ? -1 : r->esq->h;
	dir = (!r->dir) ? -1 : r->dir->h;

	return esq - dir;
}

PONT rotacionarDir(PONT r) {
	PONT no 	= r->esq;
	r->esq 	= no->dir;
	no->dir		= r;
	r->h		= no->h - 1;

	return no;
}

PONT rotacionarEsq(PONT r) {
	PONT no 	= r->dir;
	r->dir 	= no->esq;
	no->esq		= r;
	r->h		= no->h - 1;

	return no;
}

PONT rotacionarDir2(PONT r) {
	PONT no 	= r->esq;
	r->esq 	= no->dir;
	no->dir		= r;
	r->h		-= 1;
	no->h		+= 1;

	return no;
}

PONT rotacionarEsq2(PONT r) {
	PONT no 	= r->dir;
	r->dir 	= no->esq;
	no->esq		= r;
	r->h		-= 1;
	no->h		+= 1;

	return no;
}

PONT inserirNO(PONT r, PONT novo) {
	if (!r)
		return novo;

	if (novo->reg.chave < r->reg.chave) { 
		r->esq = inserirNO(r->esq, novo);
		r->h = r->esq->h + 1;
	} else {
		r->dir = inserirNO(r->dir, novo);
		r->h = r->dir->h + 1;
	}

	int peso_r = balanceamento(r);

	if (peso_r == 2) {
		if (balanceamento(r->esq) < 0)
			r->esq = rotacionarEsq2(r->esq);
		r = rotacionarDir(r);
	} else if (peso_r == -2) {
		if (balanceamento(r->dir) > 0) 
			r->dir = rotacionarDir2(r->dir);
		r = rotacionarEsq(r);
	}

	return r;
}

bool inserirRegistro(PONT* r, struct REGISTRO reg) {
	*r = inserirNO(*r, criarNo(reg));
	return TRUE;
}

bool exclruiRegistro(PONT* r, struct REGISTRO reg) {

	return TRUE;
}

void exibir(PONT r) {
	if (!r)
		return;

	printf("\n%i\th:%i ", r->reg.chave, r->h);
//	printf("%i ", r->reg.chave);	
//	printf("(");

//	printf("E:");
	exibir(r->esq);
//	printf("D:");
	exibir(r->dir);

//	printf(") ");
}

int main(int argc, char const *argv[]) {
	PONT r;
	int inc[NUM_REG] = {15, 27, 49, 10, 8, 67, 59, 9, 13, 20, 14};
	struct REGISTRO reg[NUM_REG];

	iniciar(&r);

//	for (int i = 0; i < 11; ++i) {
//		reg[i].chave = inc[i];
//		inserirRegistro(&r, reg[i]);
//	}

	for (int i = 0; i < 11; ++i) {
		reg[i].chave = inc[i];
		r = inserirNO(r, criarNo(reg[i]));
	}
	
	printf("\nArvore AVL:\n");
	exibir(r);
	printf("\n");

	return 0;
}