#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct{
	int topo1;
	int topo2;
	REGISTRO reg[MAX];
} PILHA_DUPLA;

void setInfo(REGISTRO* reg, char info[]);

void inicializarPilhaDupla(PILHA_DUPLA* p){
	p->topo1 = -1;
	p->topo2 = MAX;
}

bool pilhaDuplaCheia(PILHA_DUPLA* p){
	if (p->topo1 == (p->topo2 - 1)) return true;
	return false;
}

int tamanhoPilhaDupla(PILHA_DUPLA* p, int pilha){
	int qtdePilha;

	switch(pilha){
		case PILHA_1:
		qtdePilha = p->topo1 + 1;
		break;

		case PILHA_2:
		qtdePilha = MAX - p->topo2;		
		break;

		case PILHA_TOTAL:
		qtdePilha = (p->topo1 + 1) + (MAX - p->topo2);
		break;

		default:
		qtdePilha = 0;
	}

	return qtdePilha;
}

void exibirPilhaDupla(PILHA_DUPLA* p, int pilha){
	int atual;

	if (pilha == PILHA_TOTAL || pilha == PILHA_1){
		printf("\nPilha 1:\n");
		atual = p->topo1;
		while(atual >= 0){
			printf("Chave: %d, Info: %s\n", p->reg[atual].chave, p->reg[atual].info);
			atual--;
		}		
	}

	if (pilha == PILHA_TOTAL || pilha == PILHA_2){
		printf("\nPilha 2:\n");
		atual = p->topo2;
		while(atual < MAX){
			printf("Chave: %d, Info: %s\n", p->reg[atual].chave, p->reg[atual].info);
			atual++;
		}		
	}
}

bool push(PILHA_DUPLA* p, REGISTRO reg, int pilha){
	if (pilhaDuplaCheia(p)) return false;

	switch(pilha){
		case PILHA_1:
		p->reg[++p->topo1] = reg;
		return true;		

		case PILHA_2:
		p->reg[--p->topo2] = reg;
		return true;				
	}

	return false;
}

bool pop(PILHA_DUPLA* p, REGISTRO* reg, int pilha){
	switch(pilha){
		case PILHA_1:
		if (p->topo1 > -1){
			*reg = p->reg[p->topo1--];
			return true;			
		}
		break;

		case PILHA_2:
		if (p->topo2 < MAX){
			*reg = p->reg[p->topo2++];
			return true;			
		}
		break;

	}

	return false;			
}

int main(int argc, char const *argv[]){

	PILHA_DUPLA p;
	REGISTRO reg;

	inicializarPilhaDupla(&p);

	reg.chave = 10;
	setInfo(&reg, "Registro");	
	push(&p, reg, PILHA_1);

	reg.chave = 20;
	setInfo(&reg, "Registro");
	push(&p, reg, PILHA_2);

	reg.chave = 30;
	setInfo(&reg, "Registro");
	push(&p, reg, PILHA_1);

	reg.chave = 40;
	setInfo(&reg, "Registro");
	push(&p, reg, PILHA_2);

	printf("\nQtde. elementos: %i\n", tamanhoPilhaDupla(&p, PILHA_1));
	exibirPilhaDupla(&p, PILHA_1);

	printf("\nQtde. elementos: %i\n", tamanhoPilhaDupla(&p, PILHA_2));
	exibirPilhaDupla(&p, PILHA_2);

	printf("\nQtde. elementos: %i\n", tamanhoPilhaDupla(&p, PILHA_TOTAL));
	exibirPilhaDupla(&p, PILHA_TOTAL);		

	printf("\n");

	while(pop(&p, &reg, PILHA_2)){
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