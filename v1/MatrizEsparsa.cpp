#include <stdio.h>
#include <malloc.h>

typedef struct tempNo {
	float valor;
	int coluna;
	struct tempNo* prox;
} NO;

typedef NO* PONT;

typedef struct {
	PONT* A;
	int linhas;
	int colunas;
} MATRIZ;


void iniciarMatriz(MATRIZ* m, int lin, int col) {
	m->linhas = lin;
	m->colunas = col;

	m->A = (PONT*) malloc(lin*sizeof(PONT)); 

	for (int i = 0; i < lin; ++i)
		m->A[i] = NULL;
}

bool inserirMatriz(MATRIZ* m, int lin, int col, float valor) {
	if ((lin < 0 || lin >= m->linhas) || (col < 0 || col >= m->colunas)) {
		printf("\nFora dos limites da matriz [ (%i) %i x (%i) %i ]", 
			m->linhas, m->linhas - 1, m->colunas, m->colunas - 1);
		return false;
	} 

	PONT ant = NULL;
	PONT atual = m->A[lin];

	while(atual != NULL && col > atual->coluna ) {
		ant = atual;
		atual = atual->prox;
	}

	if (atual != NULL && atual->coluna == col) 	{
		if (valor == 0) {
			if (ant == NULL)	
				m->A[lin] = atual->prox;
			else				
				ant->prox = atual->prox;
			free(atual);
		} else {
			atual->valor = valor;
		}
	} else {
		PONT novo = (PONT) malloc(sizeof(NO));
		novo->valor = valor;
		novo->coluna = col;
		novo->prox = atual;
		if (ant == NULL)	
			m->A[lin] = novo;
		else				
			ant->prox = novo;
	}
	return true;
}

bool buscarValorMatriz(MATRIZ* m, int lin, int col, float* valor) {
	if ((lin < 0 || lin >= m->linhas) || (col < 0 || col >= m->colunas))
		return false;	

	PONT atual = m->A[lin];
	while(atual)
		atual = atual->prox;

	if (!(atual != NULL && atual->coluna == col))
		return false;

	*valor = atual->valor;
	return true;
}

void exibirValorMatriz(MATRIZ* m) {
	for (int i = 0; i < m->linhas; ++i) {
		PONT atual = m->A[i];

		if (atual)
			printf("\n");

		while(atual) {
			printf("[ E %i,%i = %.2f ] ", i, atual->coluna, atual->valor);
			atual = atual->prox;
		}
	}
}

int main(int argc, char const *argv[])  {

	MATRIZ m;

	iniciarMatriz(&m, 3, 4);
	printf("\nMatriz Esparsa iniciada");

	if (inserirMatriz(&m, 0, 1, 5.1))
		printf("\nValor inserido");
	if (inserirMatriz(&m, 0, 2, 5.2))
		printf("\nValor inserido");
	if (inserirMatriz(&m, 0, 3, 5.3))
		printf("\nValor inserido");

	if (inserirMatriz(&m, 2, 1, 3))
		printf("\nValor inserido");
	if (inserirMatriz(&m, 2, 3, 4))
		printf("\nValor inserido");	
	if (inserirMatriz(&m, 1, 2, 1.2))
		printf("\nValor inserido");	

	printf("\n\nMatriz Esparsa:\n");
	exibirValorMatriz(&m);

	if (inserirMatriz(&m, 2, 3, 0))
		printf("\nValor inserido");	
	if (inserirMatriz(&m, 1, 2, 0))
		printf("\nValor inserido");	
	if (inserirMatriz(&m, 0, 2, 0))
		printf("\nValor inserido");		

	printf("\n\nMatriz Esparsa:\n");
	exibirValorMatriz(&m);

	printf("\n");

	return 0;
}