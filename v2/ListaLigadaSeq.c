#include <stdio.h>

#include "Constantes.c"

typedef struct{
	//REGISTRO reg[MAX];
	// Sentinela
	REGISTRO reg[MAX+1];
	int nroElem;
} LISTA;

void iniciarLista(LISTA *l){
	l->nroElem = 0;
}

int tamanhoLista(LISTA *l){
	return l->nroElem;
}

void exibirLista(LISTA *l){
	int i;
	printf("\nLista Linear Sequencial: \n");

	for (i = 0; i < l->nroElem; i++)
		printf("\ni:%d [%d] ", i, l->reg[i].chave);
}

bool primeiroElemento(LISTA *l, REGISTRO *reg){
	if (l->nroElem == 0)
		return false;

	*reg = l->reg[0];
	return true;		
}

bool ultimoElemento(LISTA *l, REGISTRO *reg){
	if (l->nroElem == 0)
		return false;

	*reg = l->reg[l->nroElem - 1];
	return true;		
}

bool buscarElemento(LISTA *l, REGISTRO *reg, int pos){
	if (l->nroElem == 0 || (pos < 0 || pos > l->nroElem - 1))
		return false;

	*reg = l->reg[pos];
	return true;		
}

void destruirLista(LISTA *l){
	iniciarLista(l);
}

bool inserirElemento(LISTA *l, REGISTRO reg, int pos){
	if (l->nroElem >= MAX || (pos < 0 || pos > l->nroElem))
		return false;

	if (l->nroElem > 0 && pos < l->nroElem){
		for (int i = l->nroElem; i >= (pos + 1) ; i--)	
			l->reg[i] = l->reg[i - 1];
	}

	l->reg[pos] = reg;
	l->nroElem++;

	return true;
}

bool inserirElementoOrdenado(LISTA *l, REGISTRO reg){
	if (l->nroElem >= MAX)
		return false;

	l->reg[l->nroElem].chave = reg.chave;

	int i = 0;
	
	while(l->reg[i].chave < reg.chave)
		i++;

	if (l->reg[i].chave == reg.chave && i < l->nroElem)
		return false;

	return inserirElemento(l, reg, i);
}

int buscaSequencial(LISTA *l, TIPOCHAVE chave){
	int i = 0;
	while(i < l->nroElem){
		if (l->reg[i].chave == chave)
			return i;
		i++;
	}
	return NAO_ENCONTRADO;
}

//	LISTA DEVE ESTAR ORDENADA
int buscaSentinela(LISTA *l, TIPOCHAVE chave){
	int i = 0;
	l->reg[l->nroElem].chave = chave;
	while(l->reg[i].chave < chave)
		i++;

	if ((i > l->nroElem - 1) || (l->reg[i].chave != chave))
		return NAO_ENCONTRADO;

	return i;
}

//	LISTA DEVE ESTAR ORDENADA
int buscaBinaria(LISTA *l, TIPOCHAVE chave){
	int inf, sup, meio;
	inf = 0;
	sup = l->nroElem - 1;

	while(inf <= sup){
		meio = (inf + sup) / 2;

		if (l->reg[meio].chave == chave){
			return meio;
		} else {
			if (l->reg[meio].chave < chave)
				inf = meio + 1;
			else 
				sup = meio - 1;
		}
	}
	return NAO_ENCONTRADO;
}

bool excluirElemento(LISTA *l, TIPOCHAVE chave){
	int pos, i;

	if ((pos = buscaSequencial(l, chave)) == NAO_ENCONTRADO)
		return false;

	for(i = pos; i < l->nroElem - 1;i++)
		l->reg[i] = l->reg[i + 1];

	l->nroElem--;
	return true;
}

int main(int argc, char const *argv[]){

	REGISTRO reg;
	LISTA l;
	int pos;

	iniciarLista(&l);

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
	printf("\nBusca Sequencial: ");

	reg.chave = 30;
	if ((pos = buscaSequencial(&l, reg.chave)) == NAO_ENCONTRADO)
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	else
		printf("\nEncontrado. Posicao: [%d] Chave[%d]", pos, reg.chave);

	reg.chave = 35;
	if ((pos = buscaSequencial(&l, reg.chave)) == NAO_ENCONTRADO)
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	else
		printf("\nEncontrado. Posicao: [%d] Chave[%d]", pos, reg.chave);

	printf("\n");
	printf("\nBusca Sentinela: ");
	reg.chave = 42;
	if ((pos = buscaSentinela(&l, reg.chave)) == NAO_ENCONTRADO)
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	else
		printf("\nEncontrado. Posicao: [%d] Chave[%d]", pos, reg.chave);

	printf("\n");
	printf("\nBusca Binaria: ");
	reg.chave = 20;
	if ((pos = buscaBinaria(&l, reg.chave)) == NAO_ENCONTRADO)
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	
	else
		printf("\nEncontrado. Posicao: [%d] Chave[%d]", pos, reg.chave);

	printf("\n");
	printf("\nExcluir: ");
	reg.chave = 35;
	if (excluirElemento(&l, reg.chave))
		printf("\nRegistro excluido. Chave[%d]", reg.chave);
	else
		printf("\nRegistro nao encontrado. Chave[%d]", reg.chave);	

	printf("\n\nQtde. Elementos: %d\n", tamanhoLista(&l));
	exibirLista(&l);

	printf("\n");
	return 0;
}