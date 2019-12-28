#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true		1
#define	false		0

#define BRANCO		0
#define AMARELO		1
#define VERMELHO	2

typedef int	bool;
typedef int TIPOPESO;

//////////////////// *** FILA *** ////////////////////

typedef int TIPOCHAVE;

struct REGISTRO {
	TIPOCHAVE vertice;
};

typedef struct no {
	struct REGISTRO reg;
	struct no* prox;
} NO;

struct FILA {
	NO* primeiro;
	NO* ultimo;
};

void iniciarFila(struct FILA* f) {
	f->primeiro = NULL;
	f->ultimo = NULL;
}

bool inserirFila(struct FILA* f, struct REGISTRO reg) {
	NO* novo = (NO*) malloc(sizeof(NO));
	novo->reg = reg;
	novo->prox = NULL;

	if (f->primeiro == NULL)
		f->primeiro = novo;
	else 
		f->ultimo->prox = novo;	

	f->ultimo = novo;

	return true;
}

bool excluirFila(struct FILA* f, struct REGISTRO** reg) {
	if (f->primeiro == NULL)
		return false;

	NO* no = f->primeiro;

	if(reg)
		**reg = no->reg;
	
	f->primeiro = no->prox;
	free(no);

	if (!f->primeiro)
		f->ultimo = NULL;

	return true;
}

//////////////////// *** GRAFO *** ////////////////////

typedef struct adjacencia{
	int vertice;
	TIPOPESO peso;
	struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice{
	ADJACENCIA *cab;
} VERTICE;

typedef struct grafo{
	int vertices;
	int arestas;
	VERTICE *adj;
} GRAFO;

GRAFO *criarGrafo(int v){
	GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));

	g->vertices = v;
	g->arestas = 0;
	g->adj = (VERTICE *) malloc(v*sizeof(VERTICE));

	int i;
	for(i=0; i<v; i++)
		g->adj[i].cab = NULL;

	return g;
}

ADJACENCIA *criarAdj(int v, TIPOPESO peso){
	ADJACENCIA *adj = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
	adj->vertice = v;
	adj->peso = peso;
	adj->prox = NULL;
	return adj;
}

bool criarAresta(GRAFO *g, int vi, int vf, TIPOPESO p){
	if (g == NULL)
		return false;
	if (vf < 0 || vf >= g->vertices)
		return false;
	if (vi < 0 || vi >= g->vertices)
		return false;

	ADJACENCIA *novo = criarAdj(vf, p);
	novo->prox = g->adj[vi].cab;
	g->adj[vi].cab = novo;
	g->arestas++;

	return true;
}

void imprimirGrafo(GRAFO *g){
	if (g == NULL)
		return;

	printf("\n");
	printf("Vertices: [%d] Arestas: [%d]\n", g->vertices, g->arestas);
	printf("\n");

	int i;

	for(i=0; i<g->vertices; i++){
		printf("v%d: ", i);
		ADJACENCIA *adj = g->adj[i].cab;

		while(adj){
			printf("v%d(%d) ", adj->vertice, adj->peso);
			adj = adj->prox;
		}

		printf("\n");
	}
}
void visitarVerticeP(GRAFO *g, int i, int *cor){
	cor[i] = AMARELO;

	ADJACENCIA *v = g->adj[i].cab;

	while(v){

		printf("\ni:%d ", i);
		printf("v%d(%d) ", v->vertice, v->peso);

		if (cor[v->vertice] == BRANCO)
			visitarVerticeP(g, v->vertice, cor);
		v = v->prox;
	}

	cor[i] = VERMELHO;
}

void buscarProfundidade(GRAFO *g){
	int cor[g->vertices];
	int i;

	for(i=0; i<g->vertices;i++)
		cor[i] = BRANCO;

	for(i=0; i<g->vertices;i++){
		if (cor[i] == BRANCO)
			visitarVerticeP(g, i, cor);
	}
}

void visitarVerticeL(GRAFO *g, int i, int *expl){
	struct FILA f;
	iniciarFila(&f);

	expl[i] = true;

	struct REGISTRO *reg = (struct REGISTRO*) malloc(sizeof(struct REGISTRO));
	reg->vertice = i;
	inserirFila(&f, *reg);

	while(f.primeiro){
		excluirFila(&f, &reg);
		ADJACENCIA *v = g->adj[reg->vertice].cab;

		while(v){

			if (v){
				printf("\ni:%d ", i);
				printf("v%d(%d) ", v->vertice, v->peso);
			}

			if (!expl[v->vertice]){
				expl[v->vertice] = true;
				reg->vertice = v->vertice;
				inserirFila(&f, *reg);
			}

			v = v->prox;
		}
	}
	free(reg);
}

void buscarLargura(GRAFO *g){
	bool expl[g->vertices];
	int i;

	for(i=0; i<g->vertices;i++)
		expl[i] = false;

	for(i=0; i<g->vertices;i++){
		if (!expl[i])
			visitarVerticeL(g, i, expl);
	}
}


//////////////////// *** DIJKSTRA *** ////////////////////
void inicializaD(GRAFO *g, int *d, int *p, int s){
	int v;

	for(v=0; v < g->vertices; v++){
		d[v] = INT_MAX / 2;
		p[v] = -1;
	}

	d[s] = 0;
}

void relaxa(GRAFO *g, int *d, int *p, int u, int v){
	ADJACENCIA *adj = g->adj[u].cab;
	
	while(adj && adj->vertice != v)
		adj = adj->prox;

	if (adj)	{
		if (d[v] > d[u] + adj->peso)	{
			d[v] = d[u] + adj->peso;
			p[v] = u;
		}
	}
}

bool existeAberto(GRAFO *g, int *aberto){
	int i;
	for(i = 0; i < g->vertices; i++) {
		if (aberto[i]) 
			return true;		
	}
	return false;
}

int menorDist(GRAFO *g, int *aberto, int *d){
	int i;
	for(i = 0; i < g->vertices; i++){
		if (aberto[i])
			break;
	}

	if (i == g->vertices)
		return -1;

	int menor = i;

	for(i = menor + 1; i < g->vertices; i++){
		if (aberto[i] && d[menor] > d[i])
			menor = i;
	}
	return menor;
}

int *dijkstra(GRAFO *g, int s){
	int *d = (int *) malloc(g->vertices * sizeof(int));
//	int *p = (int *) malloc(g->vertices * sizeof(int));

	int p[g->vertices];
	bool aberto[g->vertices];

	inicializaD(g, d, p, s);

	int i;
	for(i = 0; i < g->vertices; i++)
		aberto[i] = true;

	while(existeAberto(g, aberto)){
		int u = menorDist(g, aberto, d);
		aberto[u] = false;

		ADJACENCIA *adj = g->adj[u].cab;

		while(adj){
			relaxa(g, d, p, u, adj->vertice);
			adj = adj->prox;
		}
	}

//	free(d);
//	free(p);	

	return d;
}

int main(int argc, char const *argv[]){
	GRAFO *g = criarGrafo(6);

	criarAresta(g, 0,1,10);
	criarAresta(g, 0,2,5);
	criarAresta(g, 2,1,3);
	criarAresta(g, 1,3,1);
	criarAresta(g, 2,3,8);
	criarAresta(g, 2,4,2);
	criarAresta(g, 4,5,6);
	criarAresta(g, 3,5,4);
	criarAresta(g, 3,4,4);

/*	
	criarAresta(g, 0,1,2);
	criarAresta(g, 1,2,4);
	criarAresta(g, 2,0,12);
	criarAresta(g, 2,4,40);
	criarAresta(g, 3,1,3);
	criarAresta(g, 4,3,8);
	criarAresta(g, 8,9,7);	
*/

	imprimirGrafo(g);

	printf("\n\nBusca Profundidade\n");
	buscarProfundidade(g);

	printf("\n\nBusca Largura\n");
	buscarLargura(g);	

	printf("\n\nBusca Dijkstra\n\n");
	int *r = dijkstra(g, 0);	

	for(int i = 0; i < g->vertices; i++)
		printf("D(v0 -> v%d = %d\n", i, r[i]);

	printf("\n\n");

	return 0;
}