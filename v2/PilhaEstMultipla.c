#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Constantes.c"

typedef struct{
	int base[NP+1];
	int topo[NP+1];
	REGISTRO reg[MAX];
} PILHA_MULTIPLA;

void setInfo(REGISTRO* reg, char info[]);

void inicializarPilhaMultipla(PILHA_MULTIPLA* p){
	int range = MAX / NP;
	for(int i = 0; i <= NP; i++){
		p->topo[i] = (i * range) - 1;
		p->base[i] = p->topo[i];
	}
}

bool pilhaKCheia(PILHA_MULTIPLA* p, int k){
	if(p->topo[k] == p->base[k + 1])
		return true;
	return false;
}

int tamanhoPilhaK(PILHA_MULTIPLA* p, int k){
	return (p->topo[k] - p->base[k]);
}

void exibirPilhaMultipla(PILHA_MULTIPLA* p){
	printf("\n==========================================================\n");
	for(int i = 0; i < NP; i++){
		printf("\nPILHA %d => [Qtde: %d]", i, tamanhoPilhaK(p, i));

		for(int j = p->topo[i]; j > p->base[i]; j--){
			printf("\n[%d] - Chave: %d, Info: %s", j, p->reg[j].chave, p->reg[j].info);
		}
		printf("\n");
	}
}

bool deslocaDireita(PILHA_MULTIPLA* p, int k){
	if(p->topo[k] < p->base[k + 1]){
		for(int i = p->topo[k] + 1; i > p->base[k]; i--)
			p->reg[i] = p->reg[i-1];

		p->topo[k]++;
		p->base[k]++;
		return true;
	}
	return false;
}

bool deslocaEsquerda(PILHA_MULTIPLA* p, int k){
	if(p->topo[k - 1] < p->base[k]){
		for(int i = p->base[k]; i <= p->topo[k]; i++)
			p->reg[i] = p->reg[i+1];

		p->topo[k]--;
		p->base[k]--;
		return true;
	}
	return false;
}

bool pushK(PILHA_MULTIPLA* p, REGISTRO reg, int k){
	if ((pilhaKCheia(p,k)) && (k < NP-1)){
		for(int j = NP-1; j > k; j--) 
			deslocaDireita(p,j);		
	}

	if ((pilhaKCheia(p,k)) && (k > 0)){
		for(int j = 1; j <= k; j++) 
			deslocaEsquerda(p,j);
	}	

	if (pilhaKCheia(p,k)) return false;

	p->topo[k]++;
	p->reg[p->topo[k]] = reg;

	exibirPilhaMultipla(p);

	return true;
}

bool pop(PILHA_MULTIPLA* p, REGISTRO* reg, int k){
	if (p->topo[k] > p->base[k]){
		*reg = p->reg[p->topo[k]];
		p->topo[k]--;
		return true;
	}

	return false;			
}

int main(int argc, char const *argv[]){

	PILHA_MULTIPLA p;
	REGISTRO reg;

	inicializarPilhaMultipla(&p);

	reg.chave = 10;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");

	reg.chave = 20;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");

	reg.chave = 30;
	setInfo(&reg, "Registro");	
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");

	reg.chave = 40;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");

	reg.chave = 50;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");

	reg.chave = 60;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");

	reg.chave = 70;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");

	reg.chave = 80;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 2)) printf("\nPilha cheia");	

	reg.chave = 90;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 2)) printf("\nPilha cheia");		

	reg.chave = 100;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 0)) printf("\nPilha cheia");		

	reg.chave = 110;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 1)) printf("\nPilha cheia");			

	reg.chave = 120;
	setInfo(&reg, "Registro");
	if (!pushK(&p, reg, 1)) printf("\nPilha cheia");				

	printf("\n");

	while(pop(&p, &reg, 2)){
		printf("\nRemovido ===> Chave: %d, Info: %s", reg.chave, reg.info);
	}

	exibirPilhaMultipla(&p);

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