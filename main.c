#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

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