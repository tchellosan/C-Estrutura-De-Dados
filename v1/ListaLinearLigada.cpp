///////////////////////////////////////////////////////////////////////
//	FUNCOES IMPLENTADAS												 //	
///////////////////////////////////////////////////////////////////////
//	
//	void 	iniciarLista			(LISTA* l)
//	void 	reiniciarLista			(LISTA* l)
//	int 	obterTamanho			(LISTA* l)
//	void 	exibirLista				(LISTA* l)
// 	int 	buscarElementoListaOrd	(LISTA* l, TIPOCHAVE ch)
//	int 	obterTamanho			(LISTA* l)
//	bool 	inserirElementoListaOrd	(LISTA* l, REGISTRO reg, int i)
//	bool 	excluirElementoLista	(LISTA* l, TIPOCHAVE chave)
//	void	devolverNo				(LISTA* l, int j)
//
///////////////////////////////////////////////////////////////////////

#include <stdio.h>

#define MAX 50
#define NAO_ENCONTRADO -1
#define INEXISTENTE -1

typedef int TIPOCHAVE;

typedef struct{
	TIPOCHAVE chave;
	// outros campos
} REGISTRO;

typedef struct{
	REGISTRO reg;
	int prox;
} ELEMENTO;

typedef struct{
	ELEMENTO A[MAX];
	int inicio;
	int dispo;
} LISTA;

void iniciarLista(LISTA* l) {
	for (int i = 0; i < MAX-1; ++i){
		l->A[i].prox = i+1;
	}

	l->A[MAX-1].prox = INEXISTENTE;
	l->inicio = INEXISTENTE;
	l->dispo = 0;
}

void reiniciarLista(LISTA* l) {
	iniciarLista(l);
}

int obterTamanho(LISTA* l) {
	int i = l->inicio;
	int tam = 0;
	
	while(i != INEXISTENTE){
		tam++;
		i = l->A[i].prox;
	}
	return tam;
}

void exibirLista(LISTA* l){
	int i = l->inicio;
	
	printf("\n\nQtde. Elementos Lista: %i", obterTamanho(l));

	printf("\n");
	printf("\ni: %i", l->inicio);
	printf("\nd: %i", l->dispo);

	printf("\n");
	
	while(i != INEXISTENTE){
		printf("\ni:%i\t v:%i\t prox: %i", i, l->A[i].reg.chave, l->A[i].prox);
		i = l->A[i].prox;
	}
	
	printf("\n");
}

int buscarElementoListaOrd(LISTA* l, TIPOCHAVE ch){
	int i = l->inicio;

	while(i != INEXISTENTE && ch > l->A[i].reg.chave)
		i = l->A[i].prox;

	if(i != INEXISTENTE && ch == l->A[i].reg.chave)
		return i;

	return NAO_ENCONTRADO;
}

int obterNo(LISTA* l) {
	int resultado = l->dispo;

	if (l->dispo != INEXISTENTE)
		l->dispo = l->A[l->dispo].prox;

	return resultado;
}

bool inserirElementoListaOrd(LISTA* l, REGISTRO reg) {

	if (l->dispo == INEXISTENTE) {
		printf("\nLISTA CHEIA: \t\t\tChave [%i] nao incluida", reg.chave);
		return false;
	}

	int i = l->inicio;
	int ant = INEXISTENTE;

	while(i != INEXISTENTE && reg.chave > l->A[i].reg.chave) {
		ant = i;
		i = l->A[i].prox;
	}

	if (i != INEXISTENTE && reg.chave == l->A[i].reg.chave) {
		printf("\nREGISTRO DUPLICADO: \t\tChave [%i] ja existe", reg.chave);
		return false;
	}

	i = obterNo(l);
	l->A[i].reg = reg;

	if (ant == INEXISTENTE) {
		l->A[i].prox = l->inicio;
		l->inicio = i;		
	} else {
		l->A[i].prox = l->A[ant].prox;
		l->A[ant].prox = i;
	}

	printf("\nREGISTRO INCLUIDO: \t\tChave [%i]", reg.chave);
	return true;
}
void devolverNo(LISTA* l, int j) {
	l->A[j].prox = l->dispo;
	l->dispo = j;
}

bool excluirElementoLista(LISTA* l, TIPOCHAVE chave) {
	int i = l->inicio;
	int ant = INEXISTENTE;

	while(i != INEXISTENTE && chave > l->A[i].reg.chave) {
		ant = i;
		i = l->A[i].prox;
	}

	if (i == INEXISTENTE || chave != l->A[i].reg.chave) {
		printf("\nREGISTRO NAO ENCONTRADO: \tChave [%i]", chave);
		return false;
	}

	if (ant == INEXISTENTE) {
		l->inicio = l->A[i].prox;
	} else {
		l->A[ant].prox = l->A[i].prox;
	}

	devolverNo(l, i);
	printf("\nREGISTRO EXCLUIDO: \t\tChave [%i]", chave);
	return true;
}

int main(){

	REGISTRO reg;

	LISTA l;
	iniciarLista(&l);
	exibirLista(&l);

	reg.chave = 5;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 9;//
	inserirElementoListaOrd(&l, reg);	
	reg.chave = 7;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 7;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 8;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 1;
	inserirElementoListaOrd(&l, reg);
	reg.chave = 15;
	inserirElementoListaOrd(&l, reg);

	exibirLista(&l);

	reg.chave = 7;
	printf("\nChave: [%i]\t\t\tPosicao: [%i]", reg.chave, buscarElementoListaOrd(&l, reg.chave));
	reg.chave = 1;
	printf("\nChave: [%i]\t\t\tPosicao: [%i]", reg.chave, buscarElementoListaOrd(&l, reg.chave));
	reg.chave = 22;
	printf("\nChave: [%i]\t\t\tPosicao: [%i]", reg.chave, buscarElementoListaOrd(&l, reg.chave));

	printf("\n");
	reg.chave = 22;
	excluirElementoLista(&l, reg.chave);	
	reg.chave = 7;
	excluirElementoLista(&l, reg.chave);		
	exibirLista(&l);

	reg.chave = 6;
	inserirElementoListaOrd(&l, reg);
	exibirLista(&l);


	reiniciarLista(&l);
	exibirLista(&l);

	return 0;
}