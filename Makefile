CC = gcc
CFLAGS = -Wall -ansi -O3

wordmorph: main.o ficheiros.o dicionario.o lista_adjacencias.o grafo.o heap.o
	$(CC) $(CFLAGS) -o wordmorph main.o ficheiros.o dicionario.o lista_adjacencias.o grafo.o heap.o

main.o: main.c defs.h ficheiros.h dicionario.h lista_adjacencias.h grafo.h heap.h
	$(CC) -c $(CFLAGS) main.c

ficheiros.o: ficheiros.c ficheiros.h defs.h dicionario.h lista_adjacencias.h heap.h
	$(CC) -c $(CFLAGS) ficheiros.c

dicionario.o: dicionario.c dicionario.h defs.h
	$(CC) -c $(CFLAGS) dicionario.c

lista_adjacencias.o: lista_adjacencias.c  lista_adjacencias.h defs.h dicionario.h
	$(CC) -c $(CFLAGS) lista_adjacencias.c

grafo.o: grafo.c  grafo.h defs.h dicionario.h lista_adjacencias.h
	$(CC) -c $(CFLAGS) grafo.c

heap.o: heap.c  heap.h defs.h
	$(CC) -c $(CFLAGS) heap.c

clean::
	rm -f *.o core a.out wordmorph *~