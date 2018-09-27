/******************************************************************************
 *
 * Nome do ficheiro: ficheiros.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ficheiros.h"

static int * st;
static int * wt;

/******************************************************************************
 * verificar_ficheiros()
 *
 * Argumentos: _ficheiro_in_dic - ponteiro para o nome do ficheiro do dicionario
 			   _ficheiro_in_prob - ponteiro para o nome do ficheiro dos problemas
 			   _ficheiro_out - ponteiro para o nome do ficheiro de saida
 * Retorna: char *
 * Efeitos: Verificar a correcao das condicoes do ficheiro de entrada  
 *
 * Descrição: funcao auxiliar que verifica a correcao das extensões dos ficheiros 
 *			  de entrada, no caso do ficheiro do dicionario tem de ser .dic e no 
 *			  caso do ficheiro dos problemas tem de ser .pal		  
 *
 *****************************************************************************/

char * verificar_ficheiros(char * _ficheiro_in_dic, char * _ficheiro_in_prob, char * _ficheiro_out)
{
	/*Estes Ponteiros vão ser usados para verificar se as extensões estão corretas*/
  	char * verifica_pal = NULL, * verifica_dic = NULL, * aux_saida = NULL;

  	verifica_dic = strstr(_ficheiro_in_dic, ".dic");
    verifica_pal = strstr(_ficheiro_in_prob, ".pal");

  	if((verifica_dic == NULL) || (verifica_pal == NULL))
    	exit(0);

    /*Aloca mais dois espaços pois a extensão tem um caráter a mais e tem de se contar com o /0*/
    _ficheiro_out = (char *) malloc((strlen(_ficheiro_in_prob) + 2) * sizeof(char));

    if(_ficheiro_out == NULL)
      exit(0);

  	strcpy(_ficheiro_out, _ficheiro_in_prob);
  	aux_saida = strstr(_ficheiro_out, ".pal");
  	strcpy(aux_saida, ".path");

  	return _ficheiro_out;
}
 
/******************************************************************************
 * ler1_problemas()
 *
 * Argumentos: _fp_prob - ponteiro para o ficheiro que contem os problemas
 			   _max_prob - inteiro que contem o problema de maior dimensao
 			   _max_mutacoes - vetor que contem o maximo de mutacoes de cada tamanho
 * Retorna: (void)
 * Efeitos: Permite preparar todo o programa  
 *
 * Descrição: funcao que le a primeira vez o ficheiro dos problemas e em que 
 *			  verificamos todos os casos possíveis, nomeadamente, se as 
 *	          palavras dadas são iguais ou caso o numero de mutacoes dado seja superior
 *			  ao numero de mutacoes que as palavras variam entre si
 *
 *****************************************************************************/

void ler1_problemas(FILE * _fp_prob, int * max_prob, int max_mutacoes[])
{	
	char pal1[DIM_MAX], pal2[DIM_MAX];
	int flag = 0, tamanho = 0, i = 0, inc = 0, mutacoes = 0;

	while(fscanf(_fp_prob, "%s %s %d", pal1, pal2, &mutacoes) == 3)
	{
		tamanho = strlen(pal1);

		if( tamanho > *max_prob)
			*max_prob = tamanho;

		if(strcmp(pal1, pal2) != 0)
		{
			if(mutacoes > max_mutacoes[tamanho-1])
			{
				flag = 0;
				inc = 0;

				for(i = 0; i < tamanho; i++)
				{
					if((pal1[i] != pal2[i]))
					{
						inc ++;

						if((inc) >= mutacoes)
						{
							max_mutacoes[tamanho - 1] = mutacoes;
							flag = 1;
							break;
						}
					}
				}

				if(flag == 0 && inc > max_mutacoes[tamanho - 1])
				{
					max_mutacoes[tamanho - 1] = inc;
				}
			}	
		}
	}
}

/******************************************************************************
 * ler2_resolve_problemas()
 *
 * Argumentos: _fp_prob - ponteiro para o ficheiro que contem os problemas
			   _fp_out - ponteiro para o ficheiro de saída
 			   _dic - ponteiro para a estrutura do dicionario
 			   _grafo - ponteiro para a tabela do grafo
 * Retorna: (void)
 * Efeitos: Resolve os problemas  
 *
 * Descrição: Uma das funcoes mais importantes de todo o programa, pois é aqui
 *			  que vamos ler pela segunda vez o ficheiro dos problemas e o vamos
 *			  resolver. Para isso vamos utilizar um acervo que irá constituir a
 *			  nossa fila de prioridades para que, posteriormente, possamos realizar
 *			  o algoritmo de dijkstra que nos irá determinar se há caminho entre as
 *			  duas palavras dadas e caso haja o caminho mais curto entre elas. Por
 *			  fim, iremos escrever o ficheiro de saída onde para isso recorremos a 
 *			  uma funcao recursiva
 *
 *****************************************************************************/

void ler2_resolve_problemas(FILE * _fp_prob, FILE * _fp_out, dicionario * _dic, lista_adj *** _grafo)
{
	char pal1[DIM_MAX], pal2[DIM_MAX];
	int i = 0, max_mut = 0, peso_max = 0, indice_fonte = 0, indice_destino = 0, num_vertices = 0, tamanho = 0, tamanho_aux = 0;
	int  * ocorrencias = NULL, * num = NULL;
	char *** palavras = NULL;
	heap * fila_p = NULL;

	palavras = retorna_palavras_dic(_dic);

	ocorrencias = retorna_ocorrencias(_dic);
		
	while(fscanf(_fp_prob, "%s %s %d", pal1, pal2, &max_mut) == 3)
	{
		/*Verifica o caso em que as palavras sejam iguais e caso o sejam 
		escreve logo que o caminho entre elas é 0*/
		if(strcmp(pal1, pal2) == 0)
		{
			fprintf(_fp_out,"%s %d\n%s\n", pal1, 0, pal2);
			continue;
		} 
			
		tamanho = strlen(pal1);

		num_vertices = ocorrencias[tamanho-1];

		peso_max = max_mut * max_mut;

		indice_fonte = procura(palavras[tamanho - 1], pal1, 0, num_vertices);
		indice_destino = procura(palavras[tamanho - 1], pal2, 0, num_vertices);

		fila_p = nova_heap(num_vertices, maior_peso);
			
		if(tamanho_aux != tamanho)
		{
			if(tamanho_aux != 0)
			{
				free(wt);
				free(st);
			}
			
			wt = (int *) malloc(num_vertices * sizeof(int));
			st = (int *) malloc(num_vertices * sizeof(int));
				
			if(wt == NULL || st == NULL)
				exit(0);
		}
			
		for(i = 0; i < num_vertices; i++)
		{
			wt[i] = MAX_PESO;
			st[i] = -1;
				
			num = (int* ) malloc(sizeof(int));
			
			if(num == NULL)
				exit(0);

			*num = i;

			PQinsert(fila_p,(Item)num);
		}

		dijkstra(_grafo, tamanho - 1, fila_p, num_vertices, indice_fonte, indice_destino, peso_max);

		if(wt[indice_destino] == MAX_PESO)
			escever_ficheiro_sem_caminho(_fp_out, palavras[tamanho - 1], indice_fonte, indice_destino);
		else
			escrever_ficheiro(_fp_out, palavras[tamanho - 1], indice_destino, wt[indice_destino]);

		fprintf(_fp_out, "\n");

		tamanho_aux = tamanho;

		liberta_heap(fila_p);
	}

	free(wt);
	free(st);
}

/******************************************************************************
 * maior_peso()
 *
 * Argumentos: a - ponteiro para o primeiro vértice que queremos comparar
 			   b - ponteiro para o segundo vértice que queremos comparar
 * Retorna: int
 * Efeitos: Verificar as distancias ao vértice fonte  
 *
 * Descrição: funcao que retorna se a distancia entre o primeiro vertice ao 
 *			  vértice fonte é maior do que a distancia do segundo vértice a 
 *			  esse mesmo vértice. Esta funcao esta associada a estrutura do acervo
 *
 *****************************************************************************/

int maior_peso(Item a, Item b)
{
  	int a1 = 0, b1 = 0;

  	a1 = *((int *)a);
  	b1 = *((int *)b);

  	return (wt[a1] > wt[b1]);
}

/******************************************************************************
 * procura()
 *
 * Argumentos: _palavras - ponteiro para a tabela de palavras desse tamanho
 			   pal - ponteiro para a palavra que pretendemos procurar
 			   peq - inteiro com o indice da primeira palavra
 			   maior - inteiro com o indice da ultima palavra
 * Retorna: int
 * Efeitos: Retorna o indice da palavra 
 *
 * Descrição: funcao que realiza procura binária de uma palavra numa tabela e
 *			  retorna o seu indice
 *
 *****************************************************************************/

int procura(char ** _palavras, char * pal, int peq, int maior)
{
	int m = 0;

	maior--;

	while(strcmp(_palavras[maior], _palavras[peq]) >= 0)
	{
		 m = (peq + maior) / 2;

		if(strcmp(pal, _palavras[m]) == 0) 
			return m;

		if(strcmp(pal, _palavras[m]) < 0) 
			maior = m - 1;
		else 
			peq = m + 1;
	}

	return -1;
}

/******************************************************************************
 * dijkstra()
 *
 * Argumentos: _grafo - ponteiro para a tabela com o grafo
 			   tam_palavra - inteiro com o tamanho das palavras
 			   _fila_p - ponteiro para o acervo
 			   _num_vertices - numero de vertices que ha desse tamanho
 			   _indice_fonte - indice da palavra fonte
 			   _indice_destino - indice da palavra de destino
 			   _peso_max - peso máximo permitido (dado pelo numero maximo de mutacoes)
 * Retorna: (void)
 * Efeitos: Encontra o caminho  
 *
 * Descrição: funcao que implementa o algoritmo de dijkstra, sendo que este verifica
 *			  se há caminho e caso haja qual o caminho mais curto
 *
 *****************************************************************************/

void dijkstra(lista_adj *** _grafo, int tam_palavra, heap * _fila_p, int _num_vertices, int _indice_fonte, int _indice_destino, int _peso_max)
{
 	int w = 0, idx = 0;
 	lista_adj * t = NULL;
 	aresta * aresta_aux = NULL;

 	wt[_indice_fonte] = 0;
 	st[_indice_fonte] = _indice_fonte;

 	FixUp(_fila_p, _indice_fonte);
 		
 	while(!PQempty(_fila_p))
 	{	 
 		if(wt[idx = *((int*)PQdelmax(_fila_p))] != MAX_PESO)
 		{
 			if(idx == _indice_destino)
 				return;
 			
 			for(t = _grafo[tam_palavra][idx]; t != NULL; t = obter_next(t))
 			{
 				aresta_aux = (aresta *)obter_item(t);

 				if((retorna_peso_vertice(aresta_aux) <= (_peso_max)) && wt[w = retorna_indice_adj(aresta_aux)] > (wt[idx] + retorna_peso_vertice(aresta_aux)))
 				{
 					wt[w] =  wt[idx] + retorna_peso_vertice(aresta_aux);					
 					FixUp(_fila_p, retorna_posicao(_fila_p, w));
 					st[w] = idx;
 				}
 			}
 		}
 	}
 }

/******************************************************************************
 * escrever_ficheiro()
 *
 * Argumentos: _fp_out - ponteiro para o ficheiro de saída
 			   _palavras - ponteiro para a tabela de palavras desse tamanho
 			   idx - inteiro com o indice do vertice de destino (ao início)
 			   custo - inteiro com o custo do caminho
 * Retorna: (void)
 * Efeitos: Escreve o ficheiro de saída  
 *
 * Descrição: funcao recursiva que escreve o ficheiro de saída
 *
 *****************************************************************************/

void escrever_ficheiro(FILE * _fp_out, char ** _palavras, int idx, int custo)
{
	/*Condição de paragem da recursividade quando atigindo o vértice fonte*/
 	if(st[idx]==idx)
 	{
 		fprintf(_fp_out,"%s %d\n", _palavras[idx], custo);
 		return;
 	}
 		
 	escrever_ficheiro(_fp_out, _palavras, st[idx], custo);
 	fprintf(_fp_out,"%s\n", _palavras[idx]);
 	return;
}

/******************************************************************************
 * escever_ficheiro_sem_caminho()
 *
 * Argumentos: _fp_out - ponteiro para o ficheiro de saída
 			   _palavras - ponteiro para a tabela de palavras desse tamanho
 			   indice_fonte - inteiro com o indice do vertice fonte
 			   indice_destino - inteiro com o indice do vertice destino
 * Retorna: (void)
 * Efeitos: Escreve o ficheiro de saída caso nao haja caminho  
 *
 * Descrição: funcao que escreve o ficheiro de saída caso nao haja caminho
 *
 *****************************************************************************/

void escever_ficheiro_sem_caminho(FILE * _fp_out, char ** _palavras, int indice_fonte, int indice_destino)
{
	fprintf(_fp_out,"%s %d\n%s\n", _palavras[indice_fonte], -1, _palavras[indice_destino]);
 	
 	return;
}