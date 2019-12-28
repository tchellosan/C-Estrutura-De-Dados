#include <stdio.h>

#include "Constantes.c"

typedef struct {
	REGISTRO reg;
	int prox;
} NO;

typedef struct{
	NO no[MAX];
	int inicio;
	int dispo;
} LISTA;

void iniciarLista(LISTA *l){
	l->inicio = FIM_LISTA;
	l->dispo = 0;

	for (int i = 0; i < MAX - 1; ++i)
		l->no[i].prox = i + 1;

	l->no[MAX - 1].prox = FIM_LISTA;	
}

void exibirLista(LISTA *l){
	int i = l->inicio;

	while(i != FIM_LISTA){
		printf("\ni:%d [%d]", i, l->no[i].reg.chave);
		i = l->no[i].prox;
	}
}

int tamanhoLista(LISTA *l){
	int tam = 0;
	int i = l->inicio;

	while(i != FIM_LISTA){
		tam++;
		i = l->no[i].prox;
	}

	return tam;
}

int buscaSeqOrd(LISTA *l, TIPOCHAVE chave, int *ant){
	int i = l->inicio;
	*ant = NAO_ENCONTRADO;

	while(i != FIM_LISTA){
		if (l->no[i].reg.chave >= chave)
			break;

		*ant = i;
		i = l->no[i].prox;
	}

	if ((i != FIM_LISTA) && (l->no[i].reg.chave == chave))
		return i;

	return NAO_ENCONTRADO;
}

int obterNo(LISTA *l){
	int pos = l->dispo;

	if (pos != FIM_LISTA){
		l->dispo = l->no[pos].prox;
	}

	return pos;
}

void liberarNo(LISTA *l, int i){
	l->no[i].prox = l->dispo;
	l->dispo = i;
}

bool excluirElemento(LISTA *l, TIPOCHAVE chave){
	int ant, i;
	i = buscaSeqOrd(l, chave, &ant);

	if (i == NAO_ENCONTRADO)
		return false;

	if (ant == -1)
		l->inicio = l->no[i].prox;
	else
		l->no[ant].prox = l->no[i].prox;

	liberarNo(l, i);
	return true;
}

bool inserirElementoOrdenado(LISTA *l, REGISTRO reg){
	int ant, i;

	// Lista cheia
	if (l->dispo == FIM_LISTA)
		return false;

	i = buscaSeqOrd(l, reg.chave, &ant);

	// Registro duplicado
	if (!(i == NAO_ENCONTRADO))
		return false;

	i = obterNo(l);
	l->no[i].reg = reg;

	if (l->inicio == FIM_LISTA || ant == NAO_ENCONTRADO){
		l->no[i].prox = l->inicio;
		l->inicio = i;		
	} else {
		l->no[i].prox = l->no[ant].prox;
		l->no[ant].prox = i;
	}

	return true;
}

int main(int argc, char const *argv[]) {

	REGISTRO reg;
	LISTA l;

	int pos, ant;

	iniciarLista(&l);
	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	exibirLista(&l);

	reg.chave = 20;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);
	reg.chave = 42;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);	
	reg.chave = 10;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);
	reg.chave = 30;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);	
	reg.chave = 40;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);			

	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	exibirLista(&l);

	printf("\n");

	reg.chave = 30;
	if ((pos = buscaSeqOrd(&l, reg.chave, &ant)) == NAO_ENCONTRADO)
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	else
		printf("\nEncontrado. Posicao: [%d] Chave[%d]", pos, reg.chave);

	reg.chave = 35;
	if ((pos = buscaSeqOrd(&l, reg.chave, &ant)) == NAO_ENCONTRADO)
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	else
		printf("\nEncontrado. Posicao: [%d] Chave[%d]", pos, reg.chave);

	printf("\n");
	printf("\nExcluir: ");
	reg.chave = 30;
	if (excluirElemento(&l, reg.chave))
		printf("\nRegistro excluido. Chave[%d]", reg.chave);
	else
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	reg.chave = 10;
	if (excluirElemento(&l, reg.chave))
		printf("\nRegistro excluido. Chave[%d]", reg.chave);
	else
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	reg.chave = 20;
	if (excluirElemento(&l, reg.chave))
		printf("\nRegistro excluido. Chave[%d]", reg.chave);
	else
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);				
	reg.chave = 42;
	if (excluirElemento(&l, reg.chave))
		printf("\nRegistro excluido. Chave[%d]", reg.chave);
	else
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);		
	reg.chave = 30;
	if (excluirElemento(&l, reg.chave))
		printf("\nRegistro excluido. Chave[%d]", reg.chave);
	else
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	

	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	exibirLista(&l);

	printf("\n");

	reg.chave = 15;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);
	reg.chave = 20;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);	
	reg.chave = 25;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);
	reg.chave = 99;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);	
	reg.chave = 102;
	if (inserirElementoOrdenado(&l, reg))
		printf("\nRegistro incluido. Chave [%d]", reg.chave);			

	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	exibirLista(&l);

	printf("\n");

	return 0;
}