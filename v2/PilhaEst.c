#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct{
	int topo;
	REGISTRO reg[MAX];
} PILHA;

void setInfo(REGISTRO* reg, char info[]);

void inicializarPILHA(PILHA* p){
	p->topo = -1;
}

bool pilhaCheia(PILHA* p){
	if (p->topo == (MAX -1)) return true;
	return false;
}

int tamanhoPILHA(PILHA* p){
	return (p->topo + 1);
}

void exibirPILHA(PILHA* p){
	int atual = p->topo;

	while(atual >= 0){
		printf("Chave: %d, Info: %s\n", p->reg[atual].chave, p->reg[atual].info);
		atual--;
	}
}

bool push(PILHA* p, REGISTRO reg){
	if (pilhaCheia(p)) return false;
	p->reg[++p->topo] = reg;
	return true;
}

bool pop(PILHA* p, REGISTRO* reg){
	if (p->topo < 0) return false;
	*reg = p->reg[p->topo--];
	return true;
}

int main(int argc, char const *argv[]){

	PILHA p;
	REGISTRO reg;

	inicializarPILHA(&p);

	reg.chave = 10;
	setInfo(&reg, "Registro");	
	push(&p, reg);

	reg.chave = 20;
	setInfo(&reg, "Registro");
	push(&p, reg);

	reg.chave = 30;
	setInfo(&reg, "Registro");
	push(&p, reg);

	reg.chave = 40;
	setInfo(&reg, "Registro");
	push(&p, reg);

	printf("\nQtde. elementos PILHA: %i\n", tamanhoPILHA(&p));
	exibirPILHA(&p);

	printf("\n");

	while(pop(&p, &reg)){
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