#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

t_pilha* getPilha (int tamanho) {
	t_pilha *pilha = (t_pilha *) malloc (sizeof (t_pilha));
	pilha->vetor    = (int *) malloc (tamanho*sizeof(int));
	pilha->tamanho = tamanho;
	pilha->topo    = -1;
	return pilha;
}

int pilhaCheia(t_pilha* pilha) {
	return (pilha->topo == pilha->tamanho-1);
}

void push (t_pilha* pilha, int valor) {
	if (!pilhaCheia(pilha)) {
		pilha->topo++;
		pilha->vetor[pilha->topo] = valor;
	}
	else {
		printf("PILHA SOBRECARREGADA\n");
		getchar();
		getchar();
	}
}

void imprimePilha (t_pilha *pilha) {
	system ("clear");
	int i = pilha->topo;
	for (i; i > -1; i--) {
		printf("i = %d\n", i);
		printf("item = %d\n", pilha->vetor[i]);
	}
}

int drawMenu (int *n) {

	system("clear");
	printf ("\n1. RESOLVER EXPRESSAO\n");
	printf ("2. CALCULADORA\n");
	printf ("3. SAIR\n\n");
	do {
		scanf ("%d", n);
		if ( (*n > 3) || (*n < 1) )
			printf ("ENTRADA INVALIDA\n");		/*n eh passado a td funcao do menu para que este possa ser desenhado a qualquer momento*/
	} while ( (*n > 3) || (*n < 1) );
	
	return *n;
}

void funcao1 (int *n) {
	t_pilha *pilha = getPilha (5);
	
	push (pilha, 1);
	push (pilha, 8);
	push (pilha, 6);
	push (pilha, 2);
	push (pilha, 3);
	push (pilha, 5);

	imprimePilha (pilha);
	getchar();
	getchar();

	drawMenu(n);
}

void funcao2 (int *n) {
	drawMenu(n);
}