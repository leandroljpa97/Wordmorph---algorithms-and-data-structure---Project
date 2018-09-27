/******************************************************************************
 *
 * Nome do ficheiro: lista_adjacencias.c
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Cria e aloca a estrutura da aresta e da lista de adjacencias. Realiza todas as funcoes necessarias
 *	  e associadas a estas estruturas. Liberta toda a memoria associada      
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_adjacencias.h"

struct _aresta
{
    int indice_adjacente;	/* Indíce adjacente a este vértice */ 
    int peso;				/* Peso associado a cada vértice */
};

struct _lista_adj
{
	Item this;
  	lista_adj * next;
};

/******************************************************************************
 * aloca_aresta()
 *
 * Argumentos: _indice - indice adjacente do vértice
 			   peso - peso do vértice
 * Retorna: aresta *
 * Efeitos: Cria e inicializa a aresta
 *
 * Descrição: funcao que aloca a estrutura da aresta e inicializa todos as suas variaveis
 *
 *****************************************************************************/

aresta * aloca_aresta(int _indice, int peso)
{ 
  	aresta * a = NULL;

  	a = (aresta *) malloc(sizeof(aresta));
  	
  	if(a == NULL)
  		exit(0);

  	a->indice_adjacente = _indice;
  	a->peso = peso;
  
  	return a;
}

/******************************************************************************
 * retorna_indice_adj()
 *
 * Argumentos: a - ponteiro para a estrutura da aresta
 * Retorna: int
 * Efeitos: Nenhum  
 *
 * Descrição: funcao auxiliar que retorna o valor do indice adjacente
 *
 *****************************************************************************/

int retorna_indice_adj(aresta * a)
{
  return a->indice_adjacente;
}

/******************************************************************************
 * retorna_peso_vertice()
 *
 * Argumentos: a - ponteiro para a estrutura da aresta
 * Retorna: int
 * Efeitos: Nenhum  
 *
 * Descrição: funcao auxiliar que retorna o valor do peso
 *
 *****************************************************************************/

int retorna_peso_vertice(aresta * a)
{
  return a->peso;
}

/******************************************************************************
 * cria_no()
 *
 * Argumentos: next - ponteiro para a lista de adjacencias
 			   this - ponteiro para o elemento genérico
 * Retorna: lista_adj *
 * Efeitos: Cria e inicializa o novo nó
 *
 * Descrição: funcao que cria e aloca o nó da lista e retorna o ponteiro para o novo 
 *			  nó para que este possa ser colocado na lista de adjacencias correspondente
 *
 *****************************************************************************/

lista_adj * cria_no(lista_adj * next, Item this)
{
  	lista_adj * new = NULL;
                                        
  	new = (lista_adj *) malloc(sizeof(lista_adj));

  	if(new == NULL)
    	return NULL;

  	new->this = this;
  	new->next = next;

  	return new;
}

/******************************************************************************
 * obter_item()
 *
 * Argumentos: no - ponteiro para a lista de adjacencias
 * Retorna: Item
 * Efeitos: Nenhum
 *
 * Descrição: funcao auxiliar que retorna o elemento da lista
 *
 *****************************************************************************/

Item obter_item(lista_adj * no)
{
  	if(no == NULL)
    	return NULL;

  	return no->this;
}

/******************************************************************************
 * obter_next()
 *
 * Argumentos: no - ponteiro para a lista de adjacencias
 * Retorna: lista_adj *
 * Efeitos: Nenhum
 *
 * Descrição: funcao auxiliar que retorna o ponteiro para o proximo elemento da lista
 *
 *****************************************************************************/

lista_adj * obter_next(lista_adj * no)
{
	return ((no == NULL) ? NULL : no->next);
}

/******************************************************************************
 * liberta_item()
 *
 * Argumentos: this - ponteiro para o elemento genérico
 * Retorna: (void)
 * Efeitos: Liberta memória do elemento genérico
 *
 * Descrição: funcao que faz free do elemento genérico da lista (this) 
 *
 *****************************************************************************/

void liberta_item(Item this)
{
  	free(this);
}

/******************************************************************************
 * liberta_lista()
 *
 * Argumentos: head - ponteiro para o início da lista de adjacencias
 * Retorna: (void)
 * Efeitos: libertar toda a memoria
 *
 * Descrição: funcao que faz free de toda as listas de adjacencias
 *
 *****************************************************************************/

void liberta_lista(lista_adj * head , void (* free_item)(Item))
{
 	  lista_adj * next = NULL;
 	  lista_adj * aux = NULL;

  	for(aux = head; aux != NULL; aux = next)
    {
      	next = aux->next;

      	free_item(aux->this);

      	free(aux);
    }

  	return;
}