#include <stdio.h>
#include <malloc.h>

#define MANUT_INICIO	0
#define MANUT_FINAL		1
#define NORMAL			0
#define INVERSO			1

typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE chave;
	char nome[10];
};

struct ELEMENTO {
	REGISTRO reg;
	ELEMENTO* prox;
	ELEMENTO* ant;
};

struct DEQUE {
	ELEMENTO* cabeca;
};

void	iniciarDeque		(DEQUE* d) {
	d->cabeca = (ELEMENTO*) malloc(sizeof(ELEMENTO));
	d->cabeca->prox = d->cabeca;
	d->cabeca->ant	= d->cabeca;
	printf("\nDeque iniciado\n");
};

int		contarElementos		(DEQUE* d) {
	int qtde = 0;
/*
	ELEMENTO* atual = d->cabeca->prox;
	while(atual != d->cabeca) {
		qtde++;
		atual = atual->prox;
	}
*/

	ELEMENTO* atual = d->cabeca->ant;
	while(atual != d->cabeca) {
		qtde++;
		atual = atual->ant;
	}

	return  qtde;
};

void	exibirElementos		(DEQUE* d, int ordem = NORMAL) {

	ELEMENTO* atual = NULL;

	switch(ordem) {
		case NORMAL:
		printf("\nExibicao NORMAL:\n");
		printf("[ ");
		atual = d->cabeca->prox;
		while(atual != d->cabeca) {
			printf("%i, ", atual->reg.chave);
			atual = atual->prox;
		}
		break;

		case INVERSO:
		printf("\nExibicao INVERSA:\n");
		printf("[ ");
		atual = d->cabeca->ant;
		while(atual != d->cabeca) {
			printf("%i, ", atual->reg.chave);
			atual = atual->ant;
		}	
		break;	
	}

	printf(" ]");
	printf("\n");
};

bool	inserirElemento		(DEQUE* d, REGISTRO reg, int pos = MANUT_INICIO) {
	ELEMENTO* novo = (ELEMENTO*) malloc(sizeof(ELEMENTO));
	novo->reg = reg;

	switch(pos) {
		case MANUT_INICIO:
		novo->prox = d->cabeca->prox;
		d->cabeca->prox->ant = novo;
		novo->ant = d->cabeca;
		d->cabeca->prox = novo;
		break;

		case MANUT_FINAL:
		novo->ant = d->cabeca->ant;
		d->cabeca->ant->prox = novo;
		novo->prox = d->cabeca;
		d->cabeca->ant = novo;
		break;

		default:
		return false;
	}

	printf("\nElemento incluido: \t\tchave[%i]", reg.chave);
	return true;
};

bool	excluirElemento		(DEQUE* d, REGISTRO* reg = NULL, int pos = MANUT_INICIO) {
	if (!contarElementos(d)) {
		return false;
	}

	ELEMENTO* liberar = NULL;

	switch(pos) {
		case MANUT_INICIO:
		liberar = d->cabeca->prox;
		d->cabeca->prox = liberar->prox;
		liberar->prox->ant = d->cabeca;
		break;

		case MANUT_FINAL:
		liberar = d->cabeca->ant;
		d->cabeca->ant = liberar->ant;
		liberar->ant->prox = d->cabeca;
		break;

		default:
		return false;
	}

	if (reg)
		*reg = liberar->reg;

	free(liberar);

	return true;
};

void	reiniciarDeque		(DEQUE* d) {
	while(excluirElemento(d));

	printf("\nDeque re-iniciado\n");
};

int main() {

	REGISTRO reg;
	DEQUE d;

	iniciarDeque(&d);

	printf("\nQtde. Elementos Deque: %i\n", contarElementos(&d));

	exibirElementos(&d);
	exibirElementos(&d, INVERSO);

	reg.chave = 1;
	inserirElemento(&d, reg, MANUT_FINAL);		
	reg.chave = 44;
	inserirElemento(&d, reg);
	reg.chave = 39;
	inserirElemento(&d, reg);
	reg.chave = 50;
	inserirElemento(&d, reg, MANUT_FINAL);	
	reg.chave = 79;
	inserirElemento(&d, reg);
	reg.chave = 90;
	inserirElemento(&d, reg);
	reg.chave = 57;
	inserirElemento(&d, reg, MANUT_FINAL);		

	printf("\n\nQtde. Elementos Deque: %i\n", contarElementos(&d));
	exibirElementos(&d);
	exibirElementos(&d, INVERSO);
/*
	if (excluirElemento(&d, &reg))
		printf("\nElemento excluido: \t\tchave[%i]", reg.chave);		
	if (excluirElemento(&d, &reg, MANUT_FINAL))
		printf("\nElemento excluido: \t\tchave[%i]", reg.chave);		
*/

	reiniciarDeque(&d);

	printf("\nQtde. Elementos Deque: %i\n", contarElementos(&d));

	exibirElementos(&d);
	exibirElementos(&d, INVERSO);

	reg.chave = 1;
	inserirElemento(&d, reg, MANUT_FINAL);		
	reg.chave = 44;
	inserirElemento(&d, reg);
	reg.chave = 39;
	inserirElemento(&d, reg);
	reg.chave = 50;
	inserirElemento(&d, reg, MANUT_FINAL);	
	reg.chave = 79;
	inserirElemento(&d, reg);
	reg.chave = 90;
	inserirElemento(&d, reg);
	reg.chave = 57;
	inserirElemento(&d, reg, MANUT_FINAL);		

	printf("\n\nQtde. Elementos Deque: %i\n", contarElementos(&d));
	exibirElementos(&d);
	exibirElementos(&d, INVERSO);

	return 0;
}

