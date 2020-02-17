#include <stdio.h>
#include <string.h>

#include "Constantes.c"

typedef struct{
	int inicio;
	int fim;
	REGISTRO reg[MAX];
} FILA;

void setInfo(REGISTRO* reg, char info[]);

void inicializarFila(FILA* f){
	f->inicio = -1;
	f->fim = -1;
}

int tamanhoFila(FILA* f){
	int tamanho = 0;
	int atual 	= f->inicio;

	while(atual != f->fim) {
		tamanho++;
		atual = (atual + 1) % MAX;
	}

	if (atual == f->fim && atual != -1)
		tamanho++;

	return tamanho;
}

void exibirFila(FILA* f){
	int atual = f->inicio;

	while(atual != f->fim) {
		printf("I: %d Chave: %d, Info: %s\n", atual, f->reg[atual].chave, f->reg[atual].info);
		atual = (atual + 1) % MAX;
	}

	if (atual == f->fim && atual != -1)
		printf("I: %d Chave: %d, Info: %s\n", atual, f->reg[atual].chave, f->reg[atual].info);
}

bool inserirFila(FILA* f, REGISTRO reg){
	
	if (tamanhoFila(f) >= MAX) return false;
	
	f->fim = (f->fim + 1) % MAX;
	f->reg[f->fim] = reg;

	if (f->inicio < 0) f->inicio = 0;

	return true;
}

bool removerFila(FILA* f, REGISTRO* reg){
	int remover = f->inicio;
	
	if (remover < 0) return false;

	*reg = f->reg[f->inicio];

	if (f->inicio != f->fim)
		f->inicio = (f->inicio + 1) % MAX;
	else
		inicializarFila(f);

	return true;
}

int main(int argc, char const *argv[]){

	FILA f;
	REGISTRO reg;

	inicializarFila(&f);

	reg.chave = 10;
	setInfo(&reg, "Registro");	
	inserirFila(&f, reg);

	reg.chave = 20;
	setInfo(&reg, "Registro");
	inserirFila(&f, reg);

	reg.chave = 30;
	setInfo(&reg, "Registro");
	inserirFila(&f, reg);

	reg.chave = 40;
	setInfo(&reg, "Registro");
	inserirFila(&f, reg);

	printf("\nQtde. elementos fila: %i\n", tamanhoFila(&f));
	exibirFila(&f);

	printf("\n");

	removerFila(&f, &reg);
	printf("Removido ===> Chave: %d, Info: %s\n", reg.chave, reg.info);
	
	printf("\n");

	reg.chave = 40;
	setInfo(&reg, "Registro");
	inserirFila(&f, reg);

	printf("\nQtde. elementos fila: %i\n", tamanhoFila(&f));
	exibirFila(&f);

	printf("\n");

	removerFila(&f, &reg);
	printf("Removido ===> Chave: %d, Info: %s\n", reg.chave, reg.info);

	printf("\n");

	reg.chave = 50;
	setInfo(&reg, "Registro");
	inserirFila(&f, reg);

	printf("\nQtde. elementos fila: %i\n", tamanhoFila(&f));
	exibirFila(&f);
	
	return 0;
}

void setInfo(REGISTRO* reg, char info[]){
	char chaveTexto[3];
	sprintf(chaveTexto, "%i", reg->chave);
	strcpy(reg->info, info);
	strcat(reg->info, ": ");
	strcat(reg->info, chaveTexto);
}