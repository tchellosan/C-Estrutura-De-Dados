#include <stdio.h>
#include <malloc.h>

#define true 	1
#define false 	0

typedef int TIPOCHAVE;
typedef int bool;

struct REGISTRO {
	TIPOCHAVE chave;
	int info;
};

typedef struct no {
	struct REGISTRO reg;
	struct no *primFilho, *proxIrmao;
} NO;

typedef NO* PONT;

PONT criarNo(struct REGISTRO reg) {
	PONT novo = (PONT) malloc(sizeof(NO));
	novo->reg = reg;
	novo->primFilho = NULL;
	novo->proxIrmao = NULL;
	return novo;
}

PONT iniciar(struct REGISTRO reg) {
	return criarNo(reg);
}

PONT buscarChave(PONT raiz, TIPOCHAVE chave) {
	if (!raiz) 
		return  NULL;

	if (chave == raiz->reg.chave)
		return raiz;

	PONT p = raiz->primFilho;

	while(p) {
		PONT resp = buscarChave(p, chave);
		if (resp)
			return resp;

		p = p->proxIrmao;
	}
	return NULL;
}

bool buscarPai(PONT raiz, TIPOCHAVE chave, PONT* pai) {
	if (!raiz) 
		return false;

	PONT p = raiz->primFilho;

	while(p) {
		if (chave == p->reg.chave) {
			*pai = raiz;
			return true;
		}

		if (buscarPai(p, chave, pai))
			return true;
		else
			p = p->proxIrmao;
	}
	return false;
}

bool inserirNo(PONT raiz, struct REGISTRO reg, TIPOCHAVE chavePai) {
	PONT pai = buscarChave(raiz, chavePai);
	if (!pai)
		return false;

	PONT filho = criarNo(reg);
	
	if (!pai->primFilho)
		pai->primFilho = filho;
	else {
		PONT p = pai->primFilho;
		
		while(p->proxIrmao)
			p = p->proxIrmao;

		p->proxIrmao = filho;
	}

	return true;
}

bool liberarNo(PONT no) {
	if (!no)
		return false;

	PONT p = no->primFilho;

	while(p) {
		PONT q = p->proxIrmao;
		liberarNo(p);
		p = q;
	}

//	no->primFilho = NULL;
//	no->proxIrmao = NULL;
	free(no);
	return true;
}

bool excluirNo(PONT* raiz, TIPOCHAVE chave) {
	if (*raiz == NULL)
		return false;

	PONT excluir = buscarChave(*raiz, chave);
	if (excluir == NULL)
		return false;

	if (*raiz == excluir) {
		*raiz = NULL;
	} else {
		PONT pai = NULL;
		buscarPai(*raiz, chave, &pai);

		PONT p = pai->primFilho;

		if (chave == p->reg.chave) {
			pai->primFilho = p->proxIrmao;
		} else {
			while(excluir != p->proxIrmao) {
				p = p->proxIrmao;
			}
			p->proxIrmao = excluir->proxIrmao;
		}
	}

	liberarNo(excluir);
	return true;
}

void exibirArvore(PONT raiz) {
	if (!raiz)
		return;

	printf("%d (", raiz->reg.chave);
	PONT p = raiz->primFilho;

	while(p) {
		exibirArvore(p);
		p = p->proxIrmao;
	}
	printf(") ");
}

int main(int argc, char const *argv[]) {
	struct REGISTRO reg;
	PONT raiz = NULL;

	reg.chave = 8;
	raiz = iniciar(reg);

	reg.chave = 15;
	inserirNo(raiz, reg, 8);
	reg.chave = 23;
	inserirNo(raiz, reg, 8);
	reg.chave = 2;
	inserirNo(raiz, reg, 8);
	reg.chave = 20;
	inserirNo(raiz, reg, 15);
	reg.chave = 10;
	inserirNo(raiz, reg, 15);
	reg.chave = 28;
	inserirNo(raiz, reg, 15);
	reg.chave = 36;
	inserirNo(raiz, reg, 2);
	reg.chave = 7;
	inserirNo(raiz, reg, 2);
	exibirArvore(raiz);		

	excluirNo(&raiz, 10);
//	excluirNo(&raiz, 28);
//	excluirNo(&raiz, 36);
	
//	excluirNo(&raiz, 8);

	printf("\n");
	exibirArvore(raiz);		

	return 0;
}