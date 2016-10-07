#ifndef PILHA_H
#define PILHA_H

typedef struct pilha {
	int topo;
	int *item;
	int tamanho;
} t_pilha;

int drawMenu (int *n);

void funcao1 (int *n);
void funcao2 (int *n);

#endif