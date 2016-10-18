#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void operaNumero (t_pilha *pilha, int *i, char string[]) {
	int primeiro, segundo;

	primeiro = pop(pilha);
	segundo  = pop(pilha);
	switch (string[*i]) {
		case '+':
			push(pilha, segundo+primeiro);
			break;
		case '-':
			push(pilha, segundo-primeiro);
			break;
		case '*':
			push(pilha, segundo*primeiro);
			break;
		case '/':
			push(pilha, segundo/primeiro);
			break;
		case 'c':
			for (*i=primeiro; *i > 0; (*i)--)
				push(pilha, segundo);
			break;
	}
}

void empilhaNumero (t_pilha *pilha, int *i, char string[]) {
	int n;

	push(pilha, (int) string[(*i)++]-'0');
	if (string[*i] >= 48 && string[*i] <= 57) {
		while (string[*i] != ' ') {
			n = pop(pilha)*10 + string[(*i)++]-'0';
			push(pilha, n);
		}
	}
}

void calculaExpressao (char e_posfixa[]) {
	t_pilha *pilha = getPilha(50); /*implementar alocacao dinamica*/
	int i=0, primeiro, segundo;

	while (e_posfixa[i] != '\0') {
		if (e_posfixa[i] == ' ') 
			i++;
		if (e_posfixa[i] == '+' || e_posfixa[i] == '-' || e_posfixa[i] == '*' || e_posfixa[i] == '/') {
			operaNumero (pilha, &i, e_posfixa);
			i++;
		}
		else
			empilhaNumero (pilha, &i, e_posfixa);
	}
	i = (int) pop(pilha);
	printf("=%d\n", i);
	getchar();
	liberaPilha(pilha);
}

int desemPilha (t_pilha *pilha, char parentese, char saida[], int *j) {
	char c;
	int valida=1;

	while (pilha->vetor[pilha->topo] != parentese ) {
		c = (char) pop (pilha);
		saida[(*j)++] = c;
		saida[(*j)++] = ' ';
	}
	c = (char) pop(pilha);
}

void imprimePilha (t_pilha *pilha) {
	int i = pilha->topo;
	for (i; i > -1; i--) {
		printf("i = %d;", i);
		printf("item = %d\n", pilha->vetor[i]);
	}
} /*liberaPilha()?*/

void posfixaExpressao (char expressao[], int *tamanho, char saida[]) {
	t_pilha *pilha = getPilha(30); /*implementar alocacao dinamica*/
	char c;
	int i=0, j=0;

	while (expressao[i] != '\0') {
	    switch (expressao[i]) {
	        case '+':
	        case '-':
				while (pilha->vetor[pilha->topo] == '+' || pilha->vetor[pilha->topo] == '-' || 
					   pilha->vetor[pilha->topo] == '*' || pilha->vetor[pilha->topo] == '/') {
					c = (char) pop(pilha);
					saida[j++] = c;
					saida[j++] = ' ';
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
			case ' ':
				i++;
				break;
			default:
				saida[j++] = expressao[i];
				if (expressao[i+1] < 48 || expressao[i+1] > 57)
					saida[j++] = ' ';
				i++;
	    }
	}
	while (!pilhaVazia(pilha)) {
		c = (char) pop(pilha);
		saida[j++] = c;
		saida[j++] = ' ';
	}
	saida[--j] = '\0';

	printf("%s", saida);
	getchar();
	liberaPilha(pilha);
}

int validaExpressao (char expressao[], int* tamanho) {
	int valida=1, i=0;
	char c;

	for (i; expressao[i] != '\0'; ++i) { /*conta quantos parenteses existem na expressao*/
		if (expressao[i] == '(' || expressao[i] == ')' || expressao[i] == '[' || 
			expressao[i] == ']' || expressao[i] == '{' || expressao[i] == '}')
			(*tamanho)++;
	}

	t_pilha *pilha = getPilha(*tamanho);

	if (*tamanho%2) /*se 'tamanho' for impar a expressao sempre sera invalida*/
		valida=0;

	i=0;
	while (valida && expressao[i] != '\0') {
		if (expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{') {
			push(pilha, (int) expressao[i]);
			}

		if (expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}') {
			if (pilhaVazia(pilha)) {
				valida = 0;
			}
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
	liberaPilha(pilha);

	return valida;
}

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
	int i, tamanho=0;

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
	int i=0, primeiro, segundo;

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