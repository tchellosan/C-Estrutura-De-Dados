#include <stdio.h> 
#include <malloc.h> 
#include <stdarg.h>

typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE chave;
	int info;
};

struct ELEMENTO {
	REGISTRO reg;
	ELEMENTO* prox;
};

struct PILHA {
	ELEMENTO* topo;
};

//	PROTOTIPO DE FUNCOES
void	iniciarPilha	(PILHA*);
bool	reiniciarPilha	(PILHA*);
int		obterTamanho	(PILHA*);
void 	exibirPilha		(PILHA*);
bool 	push			(PILHA*, REGISTRO);
bool 	pop				(PILHA*, REGISTRO*); 

bool pop(PILHA* p, REGISTRO* reg = NULL) {
	if (!p->topo) {
		return false;
	}
	
	ELEMENTO* atual = p->topo;

	if (reg)
		*reg = atual->reg;

	p->topo = atual->prox;
	free(atual);
	return true;
}

//	FUNCAO PRINCIPAL
int main(){

	REGISTRO reg;
	PILHA p;

	iniciarPilha(&p);
	exibirPilha(&p);

	reg.chave = 5;
	push(&p, reg);
	reg.chave = 1;
	push(&p, reg);
	reg.chave = 3;
	push(&p, reg);
	reg.chave = 25;
	push(&p, reg);

	printf("\n");
	exibirPilha(&p);

//	while(pop(&p, &reg)) {
//		printf("\nRegistro excluido: \t\tChave [%i]", reg.chave);
//	}

	reiniciarPilha(&p);
	exibirPilha(&p);

	return 0;
}

//	FUNCOES
void iniciarPilha(PILHA* p) {
	p->topo = NULL;
	printf("\nPilha iniciada\n");
}

bool reiniciarPilha(PILHA* p) {
	while(pop(p));
	printf("\nPilha re-iniciada\n");	
	return true;
}

int obterTamanho(PILHA* p) {
	ELEMENTO* atual = p->topo;
	int qtde = 0;

	while(atual) {
		qtde++;
		atual = atual->prox;
	}

	return qtde;
}

void exibirPilha(PILHA* p) {
	ELEMENTO* atual = p->topo;

	printf("\nQtde Elementos Pilha: %i", obterTamanho(p));
	printf("\n[ ");	
	while(atual) {
		printf("%i, ", atual->reg.chave);	
		atual = atual->prox;
	}
	printf(" ]\n");	
}

bool push(PILHA* p, REGISTRO reg) {
	ELEMENTO* novo = (ELEMENTO*) malloc(sizeof(ELEMENTO));
	novo->reg = reg;
	novo->prox = p->topo;
	p->topo = novo;

	printf("\nElemento incluido: \t\tChave[%i]", novo->reg.chave);

	return true;
}
/*
bool pop(PILHA* p, int qtde_arg = 0, ...) {
	if (!p->topo) {
		printf("\nNao possivel excluir, pilha vazia!\n");
		return false;
	}
	
	ELEMENTO* atual = p->topo;
	REGISTRO* reg = NULL;

	va_list args;
	va_start(args, qtde_arg);

	for (int i = 0; i < qtde_arg; ++i) 	{
		reg = va_arg(args, REGISTRO*);
		*reg = atual->reg;
	}

	va_end(args);

	p->topo = atual->prox;
	free(atual);
	return true;
}
*/