#include <stdio.h>
#include "pilha.h"

int main () {
	int n;

	drawMenu (&n);
	while (n != 3) {
		if (n == 1)
			funcao1 (&n);
		if (n == 2)
			funcao2 (&n);
	}

	return 0;
}