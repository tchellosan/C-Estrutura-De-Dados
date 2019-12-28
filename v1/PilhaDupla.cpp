#include <stdio.h>

#define MAX 	5
#define MIN 	-1

#define PILHA_1	1 
#define PILHA_2	2

typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE chave;
	int info;
};

struct PILHADUPLA {
	REGISTRO reg[MAX];
	int topo1;
	int topo2;
};

void start(PILHADUPLA* pd) {
	pd->topo1 = MIN;
	pd->topo2 = MAX;
}


void restart(PILHADUPLA* pd) {
	start(pd);
}

int count(PILHADUPLA* pd, int qtde_pilha = 0) { 
	switch (qtde_pilha) {
		case PILHA_1:
		return (pd->topo1 + 1);

		case PILHA_2:
		return (MAX - pd->topo2);

		default:
		return (pd->topo1 + 1) + (MAX - pd->topo2);
	}
}

void display(PILHADUPLA* pd, int pilha = 0) {
	int imprimir_pilha = pilha;

	if (pilha == 0)
		imprimir_pilha = PILHA_1;

	if (imprimir_pilha == PILHA_1) {
		printf("\nPilha 1\n[ ");

		for (int i = pd->topo1; i > MIN; --i) {
			printf("%i, ", pd->reg[i].chave);
		}

		printf("]\n");
	}

	if (pilha == 0)
		imprimir_pilha = PILHA_2;

	if (imprimir_pilha == PILHA_2) {
		printf("\nPilha 2\n[ ");

		for (int i = pd->topo2; i < MAX; ++i) {
			printf("%i, ", pd->reg[i].chave);
		}	

		printf("]\n");
	}

}

bool push(PILHADUPLA* pd, REGISTRO reg, int inserir = PILHA_1) { 
	if (count(pd) == MAX) {
		printf("\nPilha cheia. Elemento NAO incluido: chave [%i]", reg.chave);
		return false;
	}

	if (inserir == PILHA_1) 
		pd->reg[++pd->topo1] = reg;
	else
		pd->reg[--pd->topo2] = reg;

	return true;
}

bool pop(PILHADUPLA* pd, REGISTRO* reg, int excluir = PILHA_1) { 
	switch(excluir) {
		case PILHA_2: 
		if (count(pd, PILHA_2) > 0)
			*reg = pd->reg[pd->topo2++];
		else {
			printf("\nPilha [2] vazia.");
			return false;
		}

		break;

		default:
		if (count(pd, PILHA_1) > 0)
			*reg = pd->reg[pd->topo1--];
		else {
			printf("\nPilha [1] vazia.");
			return false;
		}

		break;
	}

	return true;
}

int main(int argc, char const *argv[]) {
	REGISTRO reg;
	PILHADUPLA pd;

	start(&pd);
	printf("\nPilha Dupla iniciada");
	printf("\nQtde. Elementos Pilha: %i\n", count(&pd));

	reg.chave = 10;
	if (push(&pd, reg))
		printf("\nElemento incluido: chave [%i]", reg.chave);
	reg.chave = 20;
	if (push(&pd, reg))
		printf("\nElemento incluido: chave [%i]", reg.chave);
	reg.chave = 30;
	if (push(&pd, reg))
		printf("\nElemento incluido: chave [%i]", reg.chave);

	printf("\n\nQtde. Elementos [PILHA 1]: %i\n", count(&pd, PILHA_1));
	display(&pd, PILHA_1);

	reg.chave = 40;
	if (push(&pd, reg, PILHA_2))
		printf("\nElemento incluido: chave [%i]", reg.chave);
	reg.chave = 50;
	if (push(&pd, reg, PILHA_2))
		printf("\nElemento incluido: chave [%i]", reg.chave);
	reg.chave = 60;
	if (push(&pd, reg, PILHA_2))
		printf("\nElemento incluido: chave [%i]", reg.chave);
	reg.chave = 70;
	if (push(&pd, reg, PILHA_2))
		printf("\nElemento incluido: chave [%i]", reg.chave);	

	printf("\n\nQtde. Elementos [PILHA 2]: %i\n", count(&pd, PILHA_2));
	display(&pd, PILHA_2);

	restart(&pd);
	printf("\nPilha Dupla re-iniciada");
	printf("\nQtde. Elementos Pilha: %i\n", count(&pd));


	if (pop(&pd, &reg))
		printf("\nElemento exlcuido: chave [%i]", reg.chave);
	if (pop(&pd, &reg))
		printf("\nElemento exlcuido: chave [%i]", reg.chave);
	if (pop(&pd, &reg))
		printf("\nElemento exlcuido: chave [%i]", reg.chave);

	if (pop(&pd, &reg))
		printf("\nElemento exlcuido: chave [%i]", reg.chave);
	if (pop(&pd, &reg, PILHA_2))
		printf("\nElemento exlcuido: chave [%i]", reg.chave);	
	if (pop(&pd, &reg, PILHA_2))
		printf("\nElemento exlcuido: chave [%i]", reg.chave);		
	if (pop(&pd, &reg, PILHA_2))
		printf("\nElemento exlcuido: chave [%i]", reg.chave);	

	printf("\n\nQtde. Elementos [TOTAL]: %i\n", count(&pd));
	display(&pd);

	return 0;
}