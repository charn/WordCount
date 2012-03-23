#Makefile for sanalaskuri
#CC = gcc -g -DDEBUG -ansi -pedantic -Wall
CC = gcc -ansi -pedantic -Wall
all: sanalaskuri
sanalaskuri: sanalaskuri.o bintree.o dynchar.o
	$(CC) -o sanalaskuri sanalaskuri.o bintree.o dynchar.o
sanalaskuri.o: bintree.h
	$(CC) -c sanalaskuri.c
bintree.o: bintree.h
	$(CC) -c bintree.c
dynchar.o: dynchar.h
	$(CC) -c dynchar.c
clean:
	rm -f *.o && rm -f sanalaskuri
