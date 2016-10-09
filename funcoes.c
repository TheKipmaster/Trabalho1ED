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
		getchar();
		getchar();
		/*liberaPilha()!*/
		exit(1);
	}
}

int pop (t_pilha *pilha) {
	if (pilhaVazia(pilha)) {
		printf ("UNDERFLOW\n");
		getchar();
		getchar();
		/*liberaPilha()!*/
		exit(1);
	}
	else
		return pilha->vetor[pilha->topo--];
}

void desemPilha (t_pilha *pilha, char parentese, char saida[], int *j) {
	char c;

	while (pilha->vetor[pilha->topo] != parentese) {
		c = (char) pop (pilha);
		saida[(*j)++] = c;
	}
	c = (char) pop(pilha);
}

void imprimePilha (t_pilha *pilha) {
	system ("clear");
	int i = pilha->topo;
	for (i; i > -1; i--) {
		printf("i = %d\n", i);
		printf("item = %d\n", pilha->vetor[i]);
	}
} /*liberaPilha()?*/

char posfixaExpressao (char expressao[], int *tamanho) {
	t_pilha *pilha = getPilha(30); /*implementar alocacao dinamica*/
	char saida[50], c;
	int i=0, j=0;

	while (expressao[i] != '\0') {
	    switch (expressao[i]) {
	        case '+':
	        case '-':
				while (pilha->vetor[pilha->topo] == '+' || pilha->vetor[pilha->topo] == '-' || pilha->vetor[pilha->topo] == '*' || pilha->vetor[pilha->topo] == '/') {
					c = (char) pop(pilha);
					saida[j] = c;
					j++;
					printf("-/+\n");
				}
				push(pilha, (int) expressao[i++]);
				break;
			case '*':
			case '/':
				while (pilha->vetor[pilha->topo] == '/' || pilha->vetor[pilha->topo] == '*') {
					c = (char) pop(pilha);
					saida[j] = c;
					j++;
				}
				push(pilha, (int) expressao[i++]);
				break;
			case '(':
			case '[':
			case '{':
				push(pilha, (int) expressao[i++]);
				break;
			case ')':
				desemPilha(pilha, '(', saida, &j);
				i++;
				break;
			case ']':
				desemPilha(pilha, '[', saida, &j);
				i++;
				break;
			case '}':
				desemPilha(pilha, '{', saida, &j);
				i++;
				break;
			default:
				saida[j++] = expressao[i++];
	    }
	}
	while (!pilhaVazia(pilha)) {
		c = (char) pop(pilha);
		saida[j++] = c;
	}

	saida[j] = '\0';
	printf("%s", saida);
	getchar();

	return *saida;
}/*liberaPilha()!*/

int validaExpressao (char expressao[], int* tamanho) {
	int valida=1, i=0;
	char c;

	for (i = 0; expressao[i] != '\0'; ++i) { /*conta quantos parenteses existem na expressao*/
		if (expressao[i] == '(' || expressao[i] == ')' || expressao[i] == '[' || expressao[i] == ']' || expressao[i] == '{' || expressao[i] == '}')
			(*tamanho)++;
	}

	t_pilha *pilha = getPilha(*tamanho);

	if (*tamanho%2) /*se 'tamanho' for impar a expressao sempre sera invalida*/
		valida=0;

	while (valida && expressao[i] != '\0') {
		if (expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{')
			push(pilha, (int) expressao[i]);
		if (expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}') {
			if (pilhaVazia(pilha))
				valida = 0;
			else {
				c = (char) pop(pilha);

                switch(expressao[i]){
                    case ')':
                        if( c != '(' )
                            valida = 0;
                        break;
                    case ']':
                        if( c != '[' )
                            valida = 0;
                        break;
                    case '}':
                        if( c != '{' )
                            valida = 0;
                        break;
                }
			}
		}
		i++;
	}

	return valida;
}/*liberaPilha()!*/

int drawMenu (int *n) {

	system("clear");
	printf ("\n1. RESOLVER EXPRESSAO\n");
	printf ("2. CALCULADORA\n");
	printf ("3. SAIR\n\n");
	do {
		scanf ("%d", n);
		if ( (*n > 3) || (*n < 1) )
			printf ("ENTRADA INVALIDA\n");  	/*'n' eh passado a td funcao do menu para que este possa ser desenhado a qualquer momento*/
	} while ( (*n > 3) || (*n < 1) );
	
	return *n;
}

void funcao1 (int *n) {
	char expressao[50];
	int i, tamanho=0;

	getchar();
	system("clear");
	printf("DIGITE A EXPRESSAO A SER CALCULADA\n");
	scanf("%[^\n]", expressao);

	if (validaExpressao (expressao, &tamanho)) {
		printf("EXPRESSAO VALIDA");
		getchar();
		getchar();
		posfixaExpressao (expressao, &tamanho);
		/*calculaExpressao();*/
	}
	else {
		printf("EXPRESSAO INVALIDA. RETORNANDO AO MENU\n");
		getchar();
		getchar();
	}


	drawMenu(n);
}

void funcao2 (int *n) {
	drawMenu(n);
}