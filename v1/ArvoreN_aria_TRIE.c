#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define TRUE 		1
#define FALSE		0
#define N_ALFABETO	26

#define MAX			40

typedef int bool;
typedef bool TIPORET;

typedef struct no {
	struct no *filhos[N_ALFABETO];
	TIPORET fim;
} NO;

typedef NO* PONT;

char	palavra[100];
char	qtde;

PONT criarNo() {
	PONT p = (PONT) malloc(sizeof(NO));
	p->fim = FALSE;
	for (int i = 0; i < N_ALFABETO; ++i) {
		p->filhos[i] = NULL;
	}
	return p;
}

PONT iniciarTrie() {
	return (criarNo());
}

int mapearIndice(char c) {
	return ((int)c - (int)'a');
}

void inserirTrie(PONT raiz, char *chave) {
	int nivel;
	int compr = strlen(chave);
	int i;

	PONT p = raiz;
	for (nivel = 0; nivel < compr; nivel++) {
		i = mapearIndice(chave[nivel]);
		if (!p->filhos[i])
			p->filhos[i] = criarNo();
		p = p->filhos[i];
	}
	p->fim = TRUE;
}

bool buscarTrie(PONT raiz, char *chave) {
	int nivel;
	int compr = strlen(chave);
	int i;

	PONT p = raiz;
	for (nivel = 0; nivel < compr; nivel++) {
		i = mapearIndice(chave[nivel]);
		if (!p->filhos[i])
			return FALSE;
		p = p->filhos[i];
	}
	return (p->fim);
}

void imprimirPalavra(PONT p, int cc, int pos) {
	palavra[pos] = (char)(97 + cc);

	if (p->fim) {
		palavra[pos + 1] = '\0';
		printf("\n%s", palavra);	
		qtde++;	
	}

	for (int c = 0; c < N_ALFABETO; c++) {
		if (p->filhos[c])
			imprimirPalavra(p->filhos[c], c, pos + 1);
	}
}

void listarTrie(PONT raiz) {
	if (raiz == NULL)
		return;

	PONT p = raiz;

	qtde = 0;

	for (int c = 0; c < N_ALFABETO; c++) {
		if (p->filhos[c]) {
			int pos = 0;
			printf("\n\n===============================");
			printf("\nLETRA %c", (char) (c + 65));
			printf("\n===============================");
			imprimirPalavra(p->filhos[c], c, pos);
		}
	}

	printf("\n\n===============================");
	printf("\nQtde. Palavras: %i", qtde);
	printf("\n===============================");
}

int main(int argc, char const *argv[]) {

	PONT r = iniciarTrie(); 

	char* dicionario[MAX];

	dicionario[0]  = "a";
	dicionario[1]  = "able";
	dicionario[2]  = "abrupt";
	dicionario[3]  = "about";
	dicionario[4]  = "above";
	dicionario[5]  = "absent";
	dicionario[6]  = "absorb";
	dicionario[7]  = "abuse";
	dicionario[8]  = "accept";
	dicionario[9]  = "accident";
	dicionario[10] = "accompany";
	dicionario[11] = "accomplish";
	dicionario[12] = "according";
	dicionario[13] = "account";
	dicionario[14] = "accuse";
	dicionario[15] = "acquire";
	dicionario[16] = "handlebars";
	dicionario[17] = "handlebar";
	dicionario[18] = "tape";
	dicionario[19] = "frame";
	dicionario[20] = "wheel";
	dicionario[21] = "rim";
	dicionario[22] = "tire";
	dicionario[23] = "hub";
	dicionario[24] = "spokes";
	dicionario[25] = "pedal";
	dicionario[26] = "pedal";
	dicionario[27] = "crank";
	dicionario[28] = "toe";
	dicionario[29] = "clips";
	dicionario[30] = "bottom";
	dicionario[31] = "bracket";
	dicionario[32] = "brake";
	dicionario[33] = "gears";
	dicionario[34] = "gearshift";
	dicionario[35] = "chain";
	dicionario[36] = "valve";
	dicionario[37] = "stem";
	dicionario[38] = "inner";
	dicionario[39] = "tube";

	for (int i = 0; i < MAX; ++i) {
		inserirTrie(r, dicionario[i]);
	}

	listarTrie(r);

	printf("\n\n");
	return 0;
}

//gcc ArvoreN_aria_TRIE.c -o ArvoreN_aria_TRIE