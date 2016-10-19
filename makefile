CC=gcc

OBJ1=expressao.o
OBJ2=pilha.o
BIN=Calculadora_Polonesa

all: main

pilha.o: funcoes.h pilha.c
	${CC} -c -g pilha.c -lm

expressao.o: funcoes.h expressao.c
	${CC} -c -g expressao.c -lm

main: main.c ${OBJ1} ${OBJ2}
	${CC} -g -ansi -Wall -o ${BIN} main.c ${OBJ1} ${OBJ2} -lm

clean: ${BIN} ${OBJ1}
	rm -rf ${BIN} ${OBJ1} ${OBJ2}