#include <stdio.h>

#define MAX 5

typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE chave;
};

struct PILHA {
	REGISTRO reg[MAX];
	int topo;
};

void iniciarPilha(PILHA* p) {
	p->topo = -1;
}

void reiniciarPilha(PILHA* p) {
	iniciarPilha(p);
}

int obterTamanho(PILHA* p) {
	return p->topo + 1;
}

void exibirPilha(PILHA* p) {

	printf("\n\nQtde. Elementos Pilha: %i", obterTamanho(p));
	printf("\n[ ");

	for(int i = p->topo; i >= 0; i--) {
		printf("%i, ", p->reg[i].chave);
	}

	printf(" ]\n");
}

bool push(PILHA* p, REGISTRO reg) {
	if (obterTamanho(p) == MAX){
		printf("\nPILHA CHEIA: \t\t\tChave [%i] nao incluida", reg.chave);
		return false;
	}

	p->reg[++p->topo] = reg;

	printf("\nRegistro incluido: \t\tChave [%i]", reg.chave);
	return true;
}

bool pop(PILHA* p, REGISTRO* reg) {
	if (obterTamanho(p) == 0){
		printf("\nPilha vazia\n");
		return false;
	}

	reg->chave =  p->reg[p->topo].chave;
	p->topo--;

	return true;
}

int main(){
	REGISTRO r;
	PILHA p;

	iniciarPilha(&p);
	exibirPilha(&p);

	r.chave = 5;
	push(&p, r);
	r.chave = 8;
	push(&p, r);
	r.chave = 1;
	push(&p, r);
	r.chave = 9;
	push(&p, r);
	r.chave = 90;
	push(&p, r);
	r.chave = 52;
	push(&p, r);
	r.chave = 47;
	push(&p, r);
	r.chave = 25;
	push(&p, r);	
	exibirPilha(&p);
	
	while(pop(&p, &r)) {
		printf("\nRegistro excluido: \t\tChave [%i]", r.chave);
	}

	reiniciarPilha(&p);
	exibirPilha(&p);

	return 0;
}