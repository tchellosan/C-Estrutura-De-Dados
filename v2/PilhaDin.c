#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct no{
	REGISTRO reg;
	struct no *prox;
} NO;

typedef struct{
	NO* topo;
} PILHA;

void setInfo(REGISTRO* reg, char info[]);

void inicializarPILHA(PILHA* p){
	p->topo = NULL;
}

int tamanhoPILHA(PILHA* p){
	NO* atual;
	int tamanho = 0;

	atual = p->topo;

	while(atual){
		tamanho++;
		atual = atual->prox;
	}

	return tamanho;
}

void exibirPILHA(PILHA* p){
	NO* atual;

	atual = p->topo;

	while(atual){
		printf("Chave: %d, Info: %s\n", atual->reg.chave, atual->reg.info);
		atual = atual->prox;
	}
}

void push(PILHA* p, REGISTRO reg){
	NO* novo = (NO*) malloc(sizeof(NO));
	novo->reg = reg;
	novo->prox = p->topo;
	p->topo = novo;
}

bool pop(PILHA* p, REGISTRO* reg){
	NO* remover = p->topo;

	if (!remover) return false;

	*reg = remover->reg;
	p->topo = p->topo->prox;

	free(remover);

	return true;
}

int main(int argc, char const *argv[]){

	PILHA f;
	REGISTRO reg;

	inicializarPILHA(&f);

	reg.chave = 10;
	setInfo(&reg, "Registro");	
	push(&f, reg);

	reg.chave = 20;
	setInfo(&reg, "Registro");
	push(&f, reg);

	reg.chave = 30;
	setInfo(&reg, "Registro");
	push(&f, reg);

	reg.chave = 40;
	setInfo(&reg, "Registro");
	push(&f, reg);

	printf("\nQtde. elementos PILHA: %i\n", tamanhoPILHA(&f));
	exibirPILHA(&f);

	printf("\n");

	while(pop(&f, &reg)){
		printf("Removido ===> Chave: %d, Info: %s\n", reg.chave, reg.info);
	}

	printf("\n");
	return 0;
}

void setInfo(REGISTRO* reg, char info[]){
	char chaveTexto[3];
	sprintf(chaveTexto, "%i", reg->chave);
	strcpy(reg->info, info);
	strcat(reg->info, ": ");
	strcat(reg->info, chaveTexto);
}