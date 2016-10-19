#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

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
	t_pilha *pilha = getPilha(50);
	int i=0;

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


void posfixaExpressao (char expressao[], int *tamanho, char saida[]) {
	t_pilha *pilha = getPilha(30);
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