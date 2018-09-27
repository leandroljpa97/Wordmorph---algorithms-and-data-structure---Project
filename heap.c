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
 *	  Liberta toda a memoria associada      
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

struct _heap {
    int (*maior) (Item, Item);      /* Funcao associada */
    int num_elementos;				/* Numero de elementos na heap */
    int tamanho;					/* Tamanho maximo da heap */
    int * posicao;                	/* Vetor que diz a posicao de cada vertice na fila de prioridades */
    Item *fila_p;               	/* Vetor de items */
};

/******************************************************************************
 * nova_heap()
 *
 * Argumentos: tamanho - inteiro que contem o tamanho da fila de prioridades
 			   maior - funcao que compara os Item
 * Retorna: heap *
 * Efeitos: Cria e inicializa o acervo
 *
 * Descrição: funcao que aloca a estrutura do acervo e inicializa todos as suas variaveis
 *
 *****************************************************************************/

heap * nova_heap (int tamanho, int (*maior) (Item, Item))
{
    heap * h = NULL;

    h = (heap *) malloc(sizeof(heap));

    if (h == ((heap *) NULL)) 
      exit(0);

    h->num_elementos = 0;

    h->maior = maior;

    h->tamanho = tamanho;

    h->posicao = (int *) malloc(tamanho * sizeof(int));
    h->fila_p = (Item *) malloc(tamanho * sizeof(Item));

    if (h->posicao == NULL || h->fila_p == ((Item *) NULL))
      exit(0);

    return (h); 
}

/******************************************************************************
 * FixUp()
 *
 * Argumentos: h - ponteiro para a estrutura do acervo
 			   k - inteiro que contem o indice da palavra que vamos alterar a sua prioridade
 * Retorna: (void)
 * Efeitos: Altera a prioridade
 *
 * Descrição: funcao que a partir do vertice que ocupa a posicao k, vai comparando com o seu 'vertice-pai' 
 *			  e fazendo trocas ate que a condicao de acervo (dada por h->maior) esteja a ser cumprida 
 *
 *****************************************************************************/

void FixUp(heap * h, int k)
{
    Item t = NULL;
    int aux = 0;

    /* Os dois elementos nao estao bem ordenados é necessario ordena-los */
    while ((k > 0) && (h->maior) ((h->fila_p)[(k - 1) / 2], (h->fila_p)[k]))
    {
      t = (h->fila_p)[k];
      aux = (h->posicao)[*(int*)h->fila_p[k]];

      (h->fila_p)[k] = (h->fila_p)[(k - 1) / 2];
      (h->posicao)[*(int*)h->fila_p[k]] = (h->posicao)[*(int*)h->fila_p[(k - 1) / 2]];
      
      (h->fila_p)[(k - 1) / 2] = t;
      (h->posicao)[*(int*)h->fila_p[(k - 1) / 2]] = aux;
  
      k = (k - 1) / 2;
    }

}

/******************************************************************************
 * FixDown()
 *
 * Argumentos: h - ponteiro para a estrutura do acervo
 			   k - inteiro que contem o indice da palavra que vamos alterar a sua prioridade
 * Retorna: (void)
 * Efeitos: Altera a prioridade
 *
 * Descrição: funcao que a partir do vertice que ocupa a posicao k, vai comparando com o seu 
 *			  'vertice-filho' e fazendo trocas ate que a condicao de acervo (dada por h->maior) 
 *			  esteja a ser cumprida 
 *
 *****************************************************************************/

void FixDown(heap * h, int k)
{
    int j = 0, aux = 0;
    Item t = NULL;

    while ((2 * k + 1) < h->num_elementos) 
    {
      j = 2 * k + 1;

      if (((j + 1) < h->num_elementos) && (h->maior) (h->fila_p[j], h->fila_p[j + 1]))
        j++;
    
      /* Condição acervo satisfeita */
      if (!(h->maior) (h->fila_p[k], h->fila_p[j])) 
        return;
    
      /* Os dois elementos nao estao bem ordenados é necessario ordena-los */
      t = (h->fila_p)[k];
      aux =(h->posicao)[*(int*)h->fila_p[k]];
      
      (h->fila_p)[k] = (h->fila_p)[j];
      (h->posicao)[*(int*)h->fila_p[k]] = (h->posicao)[*(int*)h->fila_p[j]];
      
      (h->fila_p)[j] = t;
      (h->posicao)[*(int*)h->fila_p[j]] = aux;

      k = j;
    }
}

/******************************************************************************
 * PQinsert()
 *
 * Argumentos: h - ponteiro para a estrutura do acervo
 			   I - ponteiro para o novo elemento
 * Retorna: (void)
 * Efeitos: Insere na fila de prioridade
 *
 * Descrição: funcao que insere novo elemento no fim, a insercao é direta, assim sendo,
 *			  não é preciso fazer fixUp pois quando se invoca esta funcao todos os 
 *			  vertices tem peso maximo 
 *
 *****************************************************************************/

void PQinsert(heap * h, Item I)
{
    if (h->num_elementos  <= h->tamanho)
 	  {
		  h->fila_p[h->num_elementos] = I;
		  (h->posicao)[h->num_elementos] = h->num_elementos;
		  h->num_elementos++;
	  }
}

/******************************************************************************
 * PQdelmax()
 *
 * Argumentos: h - ponteiro para a estrutura do acervo
 * Retorna: Item
 * Efeitos: Retira o vértice de maior prioridade
 *
 * Descrição: funcao que retorna o elemento mais prioritario do acervo. Para isso, 
 *			  troca esse elemento (elemento da posicao 0), com o da ultima posicao.
 *			  Por fim, faz fixDown ao elemento que se encontra na posicao 0
 *
 *****************************************************************************/

Item PQdelmax(heap * h)
{
    Item t = NULL;
    int aux = 0;

    if (h->num_elementos > 0)
    {
   	  t = (h->fila_p)[0];
   	  aux = (h->posicao)[*(int*)h->fila_p[0]];

   	  (h->fila_p)[0] = (h->fila_p)[h->num_elementos - 1];
   	  (h->posicao)[*(int*)h->fila_p[0]] = h->posicao[*(int*)h->fila_p[h->num_elementos - 1]];
   	  
   	  (h->fila_p)[h->num_elementos - 1] = t;
   	  (h->posicao)[*(int*)h->fila_p[h->num_elementos - 1]] = aux;   

   	  h->num_elementos--;
   	  
      FixDown(h, 0);
   	  
      return t;
    }

    return NULL;
}

/******************************************************************************
 * retorna_posicao()
 *
 * Argumentos: h - ponteiro para a estrutura do acervo
 			   i - inteiro que contem o indice da posicao que queremos retornar
 * Retorna: int
 * Efeitos: Nenhum
 *
 * Descrição: funcao que retorna a posicao ocupada na heap por um determinado 
 *            vertice, dado pelo inteiro 'i'funcao que retorna a posicao ocupada 
 *			  na heap por um determinado vertice, dado pelo inteiro 'i'
 *
 *****************************************************************************/

int retorna_posicao(heap * h, int i)
{
    return h->posicao[i];
}

/******************************************************************************
 * PQempty()
 *
 * Argumentos: h - ponteiro para a estrutura do acervo
 * Retorna: int
 * Efeitos: Verifica se a fila de prioridade está vazia ou nao
 *
 * Descrição: funcao que verifica se a heap esta vazia (retornando 1 se for o caso)
 *
 *****************************************************************************/

int PQempty(heap * h)
{
	if(h->num_elementos == 0)
		return 1;
	
	else return 0;
}

/******************************************************************************
 * liberta_heap()
 *
 * Argumentos: h - ponteiro para a estrutura do acervo
 * Retorna: (void)
 * Efeitos: Liberta toda a memória associada ao acervo
 *
 * Descrição: funcao que faz free de toda a estrutura da heap esta funcao 
 *			  é invocada sempre que se acaba de resolver um problema
 *
 *****************************************************************************/

void liberta_heap(heap * h)
{
	int i = 0;

	for(i = 0; i < h->tamanho; i++)
	{
		free(h->fila_p[i]);
	}

	free(h->fila_p);
	free(h->posicao);
	free(h);
}