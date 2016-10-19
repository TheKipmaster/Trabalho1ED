#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct pilha {
	int topo;
	int *vetor;
	int tamanho;
} t_pilha;

int 	 drawMenu (int *n);
void 	 funcao1  (int *n);
void 	 funcao2  (int *n);

int      pilhaVazia (t_pilha *pilha);
int      pilhaCheia (t_pilha *pilha);

void     push (t_pilha *pilha, int valor);
int      pop  (t_pilha *pilha);

t_pilha* getPilha     (int tamanho);
void     liberaPilha  (t_pilha *pilha);

int		 desemPilha   (t_pilha *pilha, char parentese, char saida[], int *j);

int		 validaExpressao  (char expressao[], int *tamanho);
void	 posfixaExpressao (char expressao[], int *tamanho, char saida[]);
void 	 calculaExpressao (char e_posfixa[]);

void 	 empilhaNumero (t_pilha *pilha, int *i, char string[]);
void	 operaNumero   (t_pilha *pilha, int *i, char string[]);

#endif