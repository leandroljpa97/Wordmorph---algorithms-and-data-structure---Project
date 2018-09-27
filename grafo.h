/******************************************************************************
 *
 * Nome do ficheiro: grafo.h
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Cria, aloca, preenche e liberta todos os grafos que sejam necessários      
 *
 *****************************************************************************/

#ifndef _GRAFO_H
#define _GRAFO_H

#include "defs.h"
#include "dicionario.h"
#include "lista_adjacencias.h"

lista_adj *** criar_grafos(dicionario * _dic, int _max_prob, int _max_mutacoes[]);
lista_adj *** aloca_grafos(int * _ocorrencias, int _max_prob);
void 		  compara_palavras(lista_adj *** _grafo, int _max_mutacoes[], int tamanho, char * pal1, char * pal2, int indice_p1, int indice_p2);
void 		  preencher_grafo(lista_adj *** _grafo, int num_mutacoes, int _indice_p1, int _indice_p2, int tamanho);
void 		  liberta_memoria(lista_adj *** _grafo, dicionario * _dic, int _max_prob);

#endif
