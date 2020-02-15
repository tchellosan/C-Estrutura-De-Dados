#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct no{
	REGISTRO reg;
	struct no *prox;
} NO;

typedef struct{
	NO* inicio;
	NO* fim;
} FILA;

void setInfo(REGISTRO* reg, char info[]);

void inicializarFila(FILA* f){
	f->inicio = NULL;
	f->fim = NULL;
}

int tamanhoFila(FILA* f){
	NO* atual;
	int tamanho = 0;

	atual = f->inicio;

	while(atual){
		tamanho++;
		atual = atual->prox;
	}

	return tamanho;
}

void exibirFila(FILA* f){
	NO* atual;

	atual = f->inicio;

	while(atual){
		printf("Chave: %d, Info: %s\n", atual->reg.chave, atual->reg.info);
		atual = atual->prox;
	}
}

void inserirFila(FILA* f, REGISTRO reg){
	NO* novo;
	novo = (NO*) malloc(sizeof(NO));
	novo->reg = reg;
	novo->prox = NULL;

	if (f->fim){
		f->fim->prox = novo;
	} else{
		f->inicio = novo;
	}

	f->fim = novo;
}

bool removerFila(FILA* f, REGISTRO* reg){
	NO* remover;

	remover = f->inicio;

	if (!remover) return false;

	*reg = remover->reg;
	f->inicio = remover->prox;
	free(remover);

	if (!f->inicio)	 f->fim = NULL;

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

	while(removerFila(&f, &reg)){
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