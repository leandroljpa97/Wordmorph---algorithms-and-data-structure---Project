/******************************************************************************
 *
 * Nome do ficheiro: heap.c
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Cria e aloca a estrutura do acervo, realiza todas as funcoes necessarias
 *	  e associadas a fila de prioridades que foi impletada através de um acervo.
 *	  Liberta toda a memoria associada.      
 *
 *****************************************************************************/

#ifndef _ACERVOS_H
#define _ACERVOS_H

#include "defs.h"

typedef struct _heap heap;

heap * nova_heap (int _tamanho, int (*maior) (Item, Item));
void   FixUp(heap * h, int k);
void   FixDown(heap * h, int k);
void   PQinsert(heap * h, Item I);
Item   PQdelmax(heap * h);
int    retorna_posicao(heap *h, int i);
int    PQempty(heap * _h);
void   liberta_heap(heap * h);

#endif
