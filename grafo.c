/******************************************************************************
 *
 * Nome do ficheiro: grafo.c
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Cria, aloca, preenche e liberta todos os grafos que sejam necessários      
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"

/******************************************************************************
 * criar_grafos()
 *
 * Argumentos: _dic - ponteiro para a estrutura do dicionario
 			   _max_prob - inteiro que contem o problema de maior dimensao
 			   _max_mutacoes - vetor que contem o maximo de mutacoes de cada tamanho
 * Retorna: lista_adj ***
 * Efeitos: Cria os grafos
 *
 * Descrição: funcao que cria a tabela tridimensional para o grafo e que chama 
 *			  a funcao que compara as palavras desse tamanho
 *
 *****************************************************************************/

lista_adj *** criar_grafos(dicionario * _dic, int _max_prob, int _max_mutacoes[])
{
	int i = 0, j = 0, tamanho = 0;
	lista_adj *** _grafos = NULL;
	int * _ocorrencias = NULL;
	char *** palavras = NULL;

	palavras = retorna_palavras_dic(_dic);

	_ocorrencias = retorna_ocorrencias(_dic);

	_grafos = aloca_grafos(_ocorrencias, _max_prob);
	
	for(tamanho = 0; tamanho < _max_prob; tamanho++)
	 	if(_ocorrencias[tamanho] != 0)
	 	{
	 		for(i = 0; i < _ocorrencias[tamanho]; i++)
				for(j = i + 1; j < _ocorrencias[tamanho]; j++)
					compara_palavras(_grafos, _max_mutacoes, tamanho, palavras[tamanho][i], palavras[tamanho][j], i, j);
	 	}
	 		
	return _grafos;
}

/******************************************************************************
 * aloca_grafos()
 *
 * Argumentos: _ocorrencias - vetor que contem o numero de ocorrencias de cada tamanho
 			   _max_prob - inteiro que contem o problema de maior dimensao
 * Retorna: lista_adj ***
 * Efeitos: Aloca a tabela tridimensional  
 *
 * Descrição: funcao que aloca todo a tabela tridimensional utilizado para isso o 
 *			  _max_prob e o vetor de ocorrencias
 *
 *****************************************************************************/

lista_adj *** aloca_grafos(int * _ocorrencias, int _max_prob)
{
	int i = 0;
	lista_adj *** grafos = NULL;

	grafos = (lista_adj ***) malloc(_max_prob * sizeof(lista_adj **));

	if(grafos == NULL)
		exit(0);

	for(i = 0; i < _max_prob; i++)
	{
	  	if(_ocorrencias[i] == 0)
  		 grafos[i] = NULL;
  		else
  		{ 
		 grafos[i] = (lista_adj **) calloc(_ocorrencias[i], sizeof(lista_adj *));

		 if(grafos[i] == NULL)
			 exit(0);
		}
	}

	return grafos;
}

/******************************************************************************
 * compara_palavras()
 *
 * Argumentos: _fp_prob - ponteiro para o ficheiro que contem os problemas
 			   _max_prob - inteiro que contem o problema de maior dimensao
 			   _max_mutacoes - vetor que contem o maximo de mutacoes de cada tamanho
 * Retorna: (void)
 * Efeitos: Ve se duas palavras são adjacentes  
 *
 * Descrição: funcao que compara as duas palavras, calcula o numero de mutacoes
 *			  que estas diferem e preenche o grafo caso estas sejam adjacentes
 *
 *****************************************************************************/

void compara_palavras(lista_adj *** _grafo, int _max_mutacoes[], int tamanho, char * pal1, char * pal2, int indice_p1, int indice_p2)
{
	int i = 0, num_mutacoes = 0;

	int tam_palavra = tamanho + 1;

	for(i = 0; i < tam_palavra; i++)
	{
		if(pal1[i] != pal2[i])
			/*Esta condicao verifica se o numero de mutacoes ja é superior 
			ao numero maximo de mutacoes que ha desse tamanho*/
			if(++num_mutacoes > _max_mutacoes[tamanho])
				return;
	}

	preencher_grafo(_grafo, num_mutacoes, indice_p1, indice_p2, tamanho); 
}

/******************************************************************************
 * preencher_grafo()
 *
 * Argumentos: _grafos - ponteiro para a tabela do grafo
 			   num_mutacoes - inteiro que contem numero de mutacoes que as duas palavras variam
 			   indice_p1 - inteiro que contem o indice da primeira palavra
 			   indice_p2 - inteiro que contem o indice da segunda palavra
 			   tamanho - inteiro que contem o tamanho da palavra
 * Retorna: (void)
 * Efeitos: Preenche o grado  
 *
 * Descrição: funcao que cria as duas arestas com o indice adjacente correspondente 
 *            dessa palavra e o seu peso e coloca-a na lista de adjacencias correspondente
 *
 *****************************************************************************/

void preencher_grafo(lista_adj *** _grafos, int num_mutacoes, int indice_p1, int indice_p2, int tamanho)
{
	aresta * a1 = NULL, * a2 = NULL;

	int peso = num_mutacoes * num_mutacoes;

	a1 = aloca_aresta(indice_p2, peso);
	_grafos[tamanho][indice_p1] = cria_no(_grafos[tamanho][indice_p1], a1);

	a2 = aloca_aresta(indice_p1, peso);
	_grafos[tamanho][indice_p2] = cria_no(_grafos[tamanho][indice_p2], a2);
}

/******************************************************************************
 * liberta_memoria()
 *
 * Argumentos: _grafos - ponteiro para a tabela do grafo
 			   _dic - ponteiro para a estrutura do dicionario
 			   _max_prob - inteiro que contem o problema de maior dimensao
 * Retorna: (void)
 * Efeitos: Liberta toda a memória relacionada com o grafo  
 *
 * Descrição: funcao que liberta toda a memoria do grafo, incluindo todas as 
 *			  listas de adjacencias, usando para isso o _max_prob e o vetor 
 *			  de ocorrencias presente na estrutura do dicionario 
 *
 *****************************************************************************/

void liberta_memoria(lista_adj *** _grafos, dicionario * _dic, int _max_prob)
{
  	int j = 0, i = 0;

	int * _ocorrencias = retorna_ocorrencias(_dic);

  	for(i = 0; i < _max_prob; i++)
  	{
  		if(_ocorrencias[i] != 0)
  		{
  			for(j = 0; j < _ocorrencias[i]; j++)
  			{
  				liberta_lista(_grafos[i][j], liberta_item);
  			}
    			

  			free (_grafos[i]);
  		}
  	}

  	free(_grafos);
}