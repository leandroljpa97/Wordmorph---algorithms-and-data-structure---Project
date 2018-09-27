/******************************************************************************
 *
 * Nome do ficheiro: lista_adjacencias.h
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Programa Principal      
 *
 *****************************************************************************/

#ifndef _LISTA_ADJANCENCIAS_H
#define _LISTA_ADJANCENCIAS_H

#include "defs.h"
#include "dicionario.h"

typedef struct _aresta aresta;
typedef struct _lista_adj lista_adj;

aresta 	    * aloca_aresta(int _indice, int peso);
int 		  retorna_indice_adj(aresta * a);
int 		  retorna_peso_vertice(aresta * a);
lista_adj   * cria_no(lista_adj * next, Item this);
Item 		  obter_item(lista_adj * no);
lista_adj   * obter_next(lista_adj * no);
void 		  liberta_item(Item this);
void 		  liberta_lista(lista_adj * head , void (* free_item)(Item));

#endif
