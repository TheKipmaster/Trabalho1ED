#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int drawMenu (int *n) {

	system("clear");
	printf ("\n1. RESOLVER EXPRESSAO\n");
	printf ("2. CALCULADORA\n");
	printf ("3. SAIR\n\n");
	do {
		scanf ("%d", n);
		if ( (*n > 3) || (*n < 1) )
			printf ("ENTRADA INVALIDA\n");  	/*'n' eh passado a td funcao do menu para que*/
	} while ( (*n > 3) || (*n < 1) );           /*este possa ser desenhado a qualquer momento*/
	
	return *n;
}

void funcao1 (int *n) {
	char expressao[50], saida[50];
	int tamanho=0;

	getchar();
	system("clear");
	printf("DIGITE A EXPRESSAO A SER CALCULADA\n");
	scanf("%[^\n]", expressao);

	if (validaExpressao (expressao, &tamanho)) {
		printf("EXPRESSAO VALIDA");
		getchar();
		getchar();
		posfixaExpressao (expressao, &tamanho, saida);
		calculaExpressao(saida);
	}
	else {
		printf("EXPRESSAO INVALIDA. RETORNANDO AO MENU\n");
		getchar();
		getchar();
	}
	drawMenu(n);
}

void funcao2 (int *n) {
	t_pilha *pilha = getPilha(30);
	char entrada[10];
	int i=0, primeiro;

	do {
		system("clear");
		printf("MODO CALCULADORA. DIGITE 'SAIR' PARA RETORNAR AO MENU\n");
		if (pilhaVazia(pilha))
			printf("PILHA VAZIA\n");
		else {
			for (i = pilha->topo; i > -1; i--) 
				printf("%d. %d\n", i+1, pilha->vetor[pilha->topo-i]);
		}
		printf("->");
		scanf("%s", entrada);
		if (!strcmp (entrada, "+") || !strcmp (entrada, "-") || !strcmp (entrada, "/") || 
			!strcmp (entrada, "*") || !strcmp (entrada, "c") ){
			if (pilha->topo > 0) {
				i=0;
				operaNumero (pilha, &i, entrada);
			}
			else {
				printf("NUMERO DE OPERANDOS INSUFICIENTE\n");
				getchar();
				getchar();
			}
		}
		else if(!strcmp (entrada, "+!") || !strcmp (entrada, "-!") || 
			    !strcmp (entrada, "/!") || !strcmp (entrada, "*!") ){
			if (pilha->topo > 0) {
				while (pilha->topo != 0) {
					i=0;
					operaNumero (pilha, &i, entrada);
				}
			}
		}
		else {
			if (entrada[0] != '-')
				i=0;
			else
				i=1;
			empilhaNumero (pilha, &i, entrada);
			if (entrada[0] == '-') {
				primeiro = pop(pilha);
				push(pilha, -primeiro);
			}
		}
	} while (strcmp (entrada, "SAIR") && strcmp (entrada, "sair"));
	liberaPilha(pilha);

	drawMenu(n);
}

int main () {
	int n;

	drawMenu (&n);
	while (n != 3) {
		if (n == 1)
			funcao1 (&n);
		if (n == 2)
			funcao2 (&n);
	}
	system ("clear");

	return 0;
}