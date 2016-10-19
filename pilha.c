#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

t_pilha* getPilha (int tamanho) {
	t_pilha *pilha = (t_pilha *) malloc (sizeof (t_pilha));
	pilha->vetor    = (int *) malloc (tamanho*sizeof(int));
	pilha->tamanho = tamanho;
	pilha->topo    = -1;
	return pilha;
}

void liberaPilha (t_pilha* pilha) {
	free(pilha->vetor);
	free(pilha);
}

int pilhaCheia (t_pilha* pilha) {
	return (pilha->topo == pilha->tamanho-1);
}

int pilhaVazia (t_pilha* pilha) {
	return (pilha->topo == -1);
}

void push (t_pilha* pilha, int valor) {
	if (!pilhaCheia(pilha)) {
		pilha->vetor[++pilha->topo] = valor;
	}
	else {
		printf("OVERFLOW\n");
		liberaPilha(pilha);
		exit(1);
	}
}

int pop (t_pilha *pilha) {
	if (pilhaVazia(pilha)) {
		printf ("UNDERFLOW\n");
		liberaPilha(pilha);
		exit(1);
	}
	else
		return pilha->vetor[pilha->topo--];
}