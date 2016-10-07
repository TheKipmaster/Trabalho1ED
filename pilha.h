#ifndef PILHA_H
#define PILHA_H

typedef struct pilha {
	int topo;
	int *vetor;
	int tamanho;
} t_pilha;

int 	 drawMenu (int *n);

void 	 funcao1 (int *n);
void 	 funcao2 (int *n);

t_pilha* getPilha (int tamanho);
void     liberaPilha (t_pilha* pilha);

void     push (t_pilha* pilha, int valor);
int      pop (t_pilha* pilha);

void     imprimePilha (t_pilha *pilha);

int      pilhaVazia(t_pilha* pilha);
int      pilhaCheia(t_pilha* pilha);

#endif