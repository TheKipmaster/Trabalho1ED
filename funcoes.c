#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

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
	drawMenu(n);
}

void funcao2 (int *n) {
	drawMenu(n);
}