CC=gcc

OBJ=funcoes.o
BIN=pilha

all: main

funcoes.o: pilha.h funcoes.c
	${CC} -c -g funcoes.c -lm

main: main.c ${OBJ}
	${CC} -g -ansi -Wall -o ${BIN} main.c ${OBJ} -lm

clean: ${BIN} ${OBJ}
	rm -rf ${BIN} ${OBJ}