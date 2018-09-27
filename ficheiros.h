/******************************************************************************
 *
 * Nome do ficheiro: ficheiros.h
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Ficheiro que trata tudo o que esteja relacionado com os problemas, 
 *    nomeadamente, leitura dos ficheiros, verificar que estao corretos, 
 *	  resolver os problemas e, por fim, escrever o ficheiro de saída      
 *
 *****************************************************************************/

#ifndef _FICHEIROS_H
#define _FICHEIROS_H

#include "defs.h"
#include "dicionario.h"
#include "lista_adjacencias.h"
#include "heap.h"
 
char * verificar_ficheiros(char * _ficheiro_in_dic, char * _ficheiro_in_prob, char * _ficheiro_out);
void   ler1_problemas(FILE * _fp, int * max_prob, int max_mutacoes[]);
void   ler2_resolve_problemas(FILE *  _fp_prob, FILE * fp_out, dicionario *_dic, lista_adj *** grafo);
int    maior_peso(Item a, Item b);
int    procura(char ** _palavras, char * pal, int peq, int maior);
void   dijkstra(lista_adj *** grafo, int tam_palavra, heap * _fila_p, int _num_vertices, int _indice_fonte, int _indice_destino, int _peso_max);
void   escrever_ficheiro(FILE * fp, char ** _palavras, int idx, int custo);
void   escever_ficheiro_sem_caminho(FILE * _fp_out, char ** _palavras, int indice_fonte, int indice_destino);

#endif