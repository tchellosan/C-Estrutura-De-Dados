#include <stdio.h>

#define MAX 50
#define NAO_ENCONTRADO -1

typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct {
	REGISTRO reg[MAX+1];
	int nroElem;
} LISTA;

void iniciarLista(LISTA* l) {
	l->nroElem = 0;
} 

void reiniciarLista(LISTA* l) {
	iniciarLista(l);
} 

int obterTamanho(LISTA* l) {
	return l->nroElem;
}

void exibirLista(LISTA* l) {
	printf("\n\nQtde. Elementos Lista: %i\n", l->nroElem);
	printf("Lista: [");
	for(int i = 0; i < l->nroElem; i++) {
		printf("%i ", l->reg[i].chave);
	}
	printf("]\n");
}

/*
int buscarElementoListaSeq(LISTA* l, TIPOCHAVE ch) {
	for(int i = 0; i < l->nroElem; i++) {
		if (l->reg[i].chave == ch) {
			return i;
		} 
	}
	return NAO_ENCONTRADO;
}

int buscarElementoListaSentinela(LISTA* l, TIPOCHAVE ch) {
  l->reg[l->nroElem].chave = ch;

  int pos = 0;

  while(ch != l->reg[pos].chave){
    pos++;
  }

  if (pos == l->nroElem)
    return NAO_ENCONTRADO;
  
  return pos;
}
*/

int buscarElementoListaBin(LISTA* l, TIPOCHAVE ch) {
  int esq = 0, meio = 0;
  int dir = l->nroElem - 1;

  while(esq <= dir) {
    meio = (esq + dir) / 2;

    if (l->reg[meio].chave == ch) {
      return meio;
    } else if (ch > l->reg[meio].chave) {
      esq = meio + 1;
    } else {
      dir = meio - 1;
    }
  }

  return NAO_ENCONTRADO;
}

bool inserirElementoLista(LISTA* l, REGISTRO reg, int pos) {
	int j;

	if((l->nroElem >= MAX) || (pos < 0) || (pos > l->nroElem)) {
		printf("\nELEMENTO NAO INCLUIDO: Posicao [%i] invalida. Chave: %i", pos, reg.chave);
		return false;
	}

	for(j = l->nroElem; j > pos; j--)
		l->reg[j] = l->reg[j-1];
	
	l->reg[pos] = reg;
	l->nroElem++;
	
	printf("\nELEMENTO INCLUIDO: Posicao [%i]. Chave: %i", pos, reg.chave);
	return true;
}

bool inserirElementoListaOrd(LISTA* l, REGISTRO reg) {
	if (l->nroElem >= MAX)
		return false;

	l->reg[l->nroElem].chave = reg.chave;

  int pos = 0;

  if (l->nroElem > 0)  {
    if (reg.chave < l->reg[l->nroElem-1].chave)  {
      while(l->reg[pos].chave < reg.chave)
        pos++;
    } else {
      pos = l->nroElem;      
    }
  }

  if ((l->reg[pos].chave == reg.chave) && (pos < l->nroElem))
    return false;

  return (inserirElementoLista(l, reg, pos));
}

bool inserirElementoListaOrd2(LISTA* l, REGISTRO reg) {
  if (l->nroElem >= MAX) return false;

  int pos = l->nroElem;

  while(pos > 0 && reg.chave < l->reg[pos-1].chave) {
    l->reg[pos].chave = l->reg[pos-1].chave;
    pos--;
  }

  l->reg[pos].chave = reg.chave;
  l->nroElem++;

  printf("\nELEMENTO INCLUIDO: Posicao [%i]. Chave: %i", pos, reg.chave);
  return true;
}


bool excluirElementoLista(LISTA* l, TIPOCHAVE ch) {
	int pos;

	if ((pos = buscarElementoListaBin(l, ch)) == NAO_ENCONTRADO) {
		printf("\nELEMENTO NAO ENCONTRADO: Chave: %i", ch);
		return false;
	}

	for(int i = pos ; i < l->nroElem - 1; i++)
		l->reg[i] = l->reg[i+1];

	l->nroElem--;

	printf("\nELEMENTO EXCLUIDO: Posicao [%i]. Chave: %i", pos, ch);
	return true;
}

int main() {

	REGISTRO reg;

	LISTA l;
	iniciarLista(&l);

	reg.chave = 12;
	inserirElementoListaOrd2(&l, reg);
	
  reg.chave = 200;
  inserirElementoListaOrd2(&l, reg);
  reg.chave = 27;
  inserirElementoListaOrd2(&l, reg);
  reg.chave = -4;
  inserirElementoListaOrd2(&l, reg);
  reg.chave = 90;
  inserirElementoListaOrd2(&l, reg);
  exibirLista(&l);

  reg.chave = 10;
  excluirElementoLista(&l, reg.chave);
  reg.chave = 30;
  excluirElementoLista(&l, reg.chave);	
  reg.chave = 27;
  excluirElementoLista(&l, reg.chave);		
  exibirLista(&l);

  reg.chave = 10;
  inserirElementoListaOrd2(&l, reg);
  exibirLista(&l);

  reiniciarLista(&l);
  exibirLista(&l);

  return 0;
}
