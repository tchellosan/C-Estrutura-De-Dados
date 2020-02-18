#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct no{
	REGISTRO reg;
	struct no *prox;
	struct no *ant;
} NO;

typedef struct{
	NO* inicio1;
	NO* inicio2;
} DEQUE;

void setInfo(REGISTRO* reg, char info[]);

void inicializarDEQUE(DEQUE* d){
	d->inicio1 = NULL;
	d->inicio2 = NULL;
}

int tamanhoDEQUE(DEQUE* d){
	NO* atual;
	int tamanho = 0;

	atual = d->inicio1;

	while(atual){
		tamanho++;
		atual = atual->prox;
	}

	return tamanho;
}

void exibirDEQUE(DEQUE* d){
	NO* atual;

	atual = d->inicio1;

	while(atual){
		printf("Chave: %d, Info: %s\n", atual->reg.chave, atual->reg.info);
		atual = atual->prox;
	}
}

void inserirDEQUE(DEQUE* d, REGISTRO reg, int inicio){
	NO* novo = (NO*) malloc(sizeof(NO));
	novo->reg = reg;

	switch(inicio){
		case INICIO_1:
			novo->prox = d->inicio1;
			novo->ant = NULL;

			if (d->inicio1) d->inicio1->ant = novo;
			else d->inicio2 = novo;

			d->inicio1 = novo;	
			break;

		case INICIO_2:
			novo->ant = d->inicio2;
			novo->prox = NULL;

			if (d->inicio2) d->inicio2->prox = novo;
			else d->inicio1 = novo;

			d->inicio2 = novo;	
			break;
	}
}

bool removerDEQUE(DEQUE* d, REGISTRO* reg, int inicio){
	NO* remover;

	if (!d->inicio1 || !d->inicio2) return false;

	switch(inicio){
		case INICIO_1:		
			remover = d->inicio1;
			*reg = remover->reg;
			d->inicio1 = d->inicio1->prox;
			free(remover);
			if (!d->inicio1) d->inicio2 = NULL;
			else d->inicio1->ant = NULL;
			break;

		case INICIO_2:
			remover = d->inicio2;
			*reg = remover->reg;
			d->inicio2 = d->inicio2->ant;
			free(remover);
			if (!d->inicio2) d->inicio1 = NULL;
			else d->inicio2->prox = NULL;
			break;
	}

	return true;
}

int main(int argc, char const *argv[]){

	DEQUE d;
	REGISTRO reg;

	inicializarDEQUE(&d);

	reg.chave = 10;
	setInfo(&reg, "Registro");	
	inserirDEQUE(&d, reg, INICIO_1);

	reg.chave = 20;
	setInfo(&reg, "Registro");
	inserirDEQUE(&d, reg, INICIO_2);

	reg.chave = 30;
	setInfo(&reg, "Registro");
	inserirDEQUE(&d, reg, INICIO_1);

	reg.chave = 40;
	setInfo(&reg, "Registro");
	inserirDEQUE(&d, reg, INICIO_2);

	printf("\nQtde. elementos DEQUE: %i\n", tamanhoDEQUE(&d));
	exibirDEQUE(&d);

	printf("\n");

	while(removerDEQUE(&d, &reg, INICIO_2)){
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