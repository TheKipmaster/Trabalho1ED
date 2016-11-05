#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct pilha {
	int topo;
	int *vetor;
	int tamanho;
} t_pilha;

/**
 * Desenha o menu e valida a entrada do usuário quanto ao seus ítens.
 */
int 	 drawMenu (int *n);
/**
 * Usa as funções de manipulação de pilhas e as presentes 
 * no arquivo 'expressao.c' para validar, transformar para
 * forma posfixa e então resolver uma expressão dada.
 */
void 	 funcao1  (int *n);
/**
 * Usa as funções de manipulação de pilhas e as presentes no arquivo 
 * 'expressao.c' para criar a calculadora descrita pelo trabalho.
 */
void 	 funcao2  (int *n);

int      pilhaVazia (t_pilha *pilha);
int      pilhaCheia (t_pilha *pilha);

void     push (t_pilha *pilha, int valor);
int      pop  (t_pilha *pilha);

t_pilha* getPilha     (int tamanho);
void     liberaPilha  (t_pilha *pilha);
/**
 * Recebe um caractere de fechamento de escopo e 
 * retira elementos da pilha até encontrá-lo.
 */
int		 desemPilha   (t_pilha *pilha, char parentese, char saida[], int *j);

/**
 * Recebe uma expressão no formato string e valida ela quanto aos delimitadores
 * de escopo. Retorna '1' caso seja válida e '0' caso contrário.
 */
int		 validaExpressao  (char expressao[], int *tamanho);
/**
 * Após validada, converte a espressão para a notação posfixa, adicionando
 * espaços para facilitar a resolução dela pela função 'calculaExpressao'.
 */
void	 posfixaExpressao (char expressao[], int *tamanho, char saida[]);
/**
 * Resolve a expressão posfixa dada, usando os espaços adicionados pela função
 * 'posfixaExpressao' para saber onde um número acaba e outro começa.
 */
void 	 calculaExpressao (char e_posfixa[]);


/**
 * Empilha os números da string. Transforma números do tipo char com 
 * várias casas em um único inteiro correspondente, quando for o caso.
 */
void 	 empilhaNumero (t_pilha *pilha, int *i, char string[]);
/**
 * Faz as operações nos elementos da pilha e coloca o resultado em seu topo.
 */
void	 operaNumero   (t_pilha *pilha, int *i, char string[]);

#endif