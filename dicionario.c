/******************************************************************************
 *
 * Nome do ficheiro: dicionario.c
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Lê, cria, aloca, ordena e liberta todas as palavras do dicionário      
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicionario.h"

struct _dicionario
{
	int * ocorrencias;		 /* Vetor que diz o numero de palavras de cada tamanho*/
	int * posicao_livre;	 /* Vetor que diz a primeira posicao livre de cada tamanho, quando se preenche a tabela do dicionario */
	char *** palavras;		 /* Tabela que contém o dicionario */
};

/******************************************************************************
 * retorna_ocorrencias()
 *
 * Argumentos: _dic - ponteiro para a estrutura do dicionario
 * Retorna: int *
 * Efeitos: Nenhum  
 *
 * Descrição: funcao auxiliar que retorna o vetor de ocorrencias
 *
 *****************************************************************************/

int * retorna_ocorrencias(dicionario * _dic)
{
	return _dic->ocorrencias;
}

/******************************************************************************
 * retorna_posicao_livre()
 *
 * Argumentos: _dic - ponteiro para a estrutura do dicionario
 * Retorna: int *
 * Efeitos: Nenhum 
 *
 * Descrição: funcao auxiliar que retorna o vetor de posicao_livre
 *
 *****************************************************************************/

int * retorna_posicao_livre(dicionario * _dic)
{
	return _dic->posicao_livre;
}

/******************************************************************************
 * retorna_palavras_dic()
 *
 * Argumentos: dic - ponteiro para a estrutura do dicionario
 * Retorna: char ***
 * Efeitos: Nenhum 
 *
 * Descrição: funcao auxiliar que retorna a tabela que contem as palavras
 *
 *****************************************************************************/

char *** retorna_palavras_dic(dicionario * _dic)
{
	return _dic->palavras;
}

/******************************************************************************
 * inicializa_dicionario()
 *
 * Argumentos: _max_prob - inteiro que contem o problema de maior dimensao
 * Retorna: dicionario *
 * Efeitos: inicializa a estrutura do dicionario 
 *
 * Descrição: funcao que cria a estrutura do dicionario e inicializa todas as suas variaveis
 *
 *****************************************************************************/

dicionario * inicializa_dicionario(int _max_prob)
{
	dicionario * _dic = NULL;

	_dic = (dicionario *)malloc(sizeof(dicionario));

	if(_dic == NULL)
		exit(0); 

	_dic->ocorrencias = inicializar_vetor(_max_prob);
	_dic->posicao_livre = inicializar_vetor(_max_prob);

	_dic->palavras = NULL; 
	return _dic;
}

/******************************************************************************
 * inicializar_vetor()
 *
 * Argumentos: _max_prob - inteiro que contem o problema de maior dimensao
 * Retorna: int *
 * Efeitos: inicializa o vetor 
 *
 * Descrição: funcao utilizada para criar os vetores pertencentes a estrutura do dicionario
 *
 *****************************************************************************/

int * inicializar_vetor(int _max_prob)
{
	int * vetor = 0;

	vetor = (int *) calloc(_max_prob, sizeof(int));

	if(vetor == NULL)
		exit(0);

  	return vetor;
}

/******************************************************************************
 * resolve_dicionario()
 *
 * Argumentos: _fp_dic - ponteiro para o ficheiro que contem o dicionario
 			   _dic - ponteiro para a estrutura do dicionario
 			   _max_prob - inteiro que contem o problema de maior dimensao
 			   _max_mutacoes - vetor que contem o maximo de mutacoes de cada tamanho
 * Retorna: (void)
 * Efeitos: resolve tudo o que esteja associado ao dicionario
 *
 * Descrição: funcao que invoca ordenadamente as funcoes necessarias a resolucao do dicionario
 *
 *****************************************************************************/

void resolve_dicionario(FILE * _fp_dic, dicionario * _dic, int _max_prob, int _max_mutacoes[])
{
  	ler1_dicionario(_fp_dic,_dic, _max_prob, _max_mutacoes);

  	_dic = alocar_dicionario(_dic, _max_prob);

    /*Colocar novamente o ponteiro do ficheiro no início do ficheiro*/
  	fseek(_fp_dic, 0, SEEK_SET);

  	ler2_dicionario(_fp_dic, _dic, _dic->posicao_livre, _max_prob, _max_mutacoes);
    
  	ordenar(_dic, _max_prob); 
}

/******************************************************************************
 * ler1_dicionario()
 *
 * Argumentos: _fp_dic - ponteiro para o ficheiro que contem o dicionario
 			   _dic - ponteiro para a estrutura do dicionario
 			   _max_prob - inteiro que contem o problema de maior dimensao
 			   _max_mutacoes - vetor que contem o maximo de mutacoes de cada tamanho
 * Retorna: (void)
 * Efeitos: permite a inicializacao do dicionario 
 *
 * Descrição: primeira vez que se le o dicionario, onde se retiram as informacoes do numero de palavras de 
 *			  cada tamanho para se puder, depois alocar o pretendido
 *
 *****************************************************************************/

void ler1_dicionario(FILE * _fp_dic, dicionario* _dic, int _max_prob, int _max_mutacoes[])
{
	char pal[DIM_MAX];
	int tamanho = 0;

	while(fscanf(_fp_dic, "%s", pal) == 1)
	{
		tamanho= strlen(pal);
		if((tamanho <= _max_prob) && (_max_mutacoes[tamanho-1] != 0))
		{
				(_dic->ocorrencias[tamanho - 1])++;
		}
			
	}
}

/******************************************************************************
 * alocar_dicionario()
 *
 * Argumentos: _dic - ponteiro para a estrutura do dicionario
 			   _max_prob - inteiro que contem o problema de maior dimensao
 * Retorna: dicionario *
 * Efeitos:  aloca todo o dicionario
 *
 * Descrição: funcao que aloca, em tabela, todas as palavras necessarias do dicionario. Porem aloca apenas memoria 
 *			  para as que sao necessarias (condicao que vai ser verificada atraves do vetor ocorrencias)
 *
 *****************************************************************************/

dicionario * alocar_dicionario(dicionario * _dic, int _max_prob)
{
  	int i = 0, j = 0;

  	_dic->palavras = (char ***) malloc(_max_prob * sizeof(char  **));

	for(i = 0; i < _max_prob; i++)
  	{
  		if(_dic->ocorrencias[i] == 0)
  			_dic->palavras[i] = NULL;
  		else
  		{
    		_dic->palavras[i] = (char **) malloc(_dic->ocorrencias[i] * sizeof(char *));

  			for(j = 0; j < _dic->ocorrencias[i]; j++)
				_dic->palavras[i][j] = (char *) malloc((i + 2) * sizeof(char));
		}
	}

  	return _dic;
}

/******************************************************************************
 * ler2_dicionario()
 *
 * Argumentos: _fp_dic - ponteiro para o ficheiro que contem o dicionario
 			   _dic - ponteiro para a estrutura do dicionario
 			   _posicao_livre - vetor que diz a primeira posicao livre de cada tamanho
 			   _max_prob - inteiro que contem o problema de maior dimensao
 			   _max_mutacoes - vetor que contem o maximo de mutacoes de cada tamanho
 * Retorna: (void)
 * Efeitos: guarda as palavras do dicionario 
 *
 * Descrição: funcao utilizada para se ler a segunda vez o dicionario onde se vai
 *			  colocar cada palavra na primeira posicao livre (do seu tamanho) da tabela
 *
 *****************************************************************************/

/* */
void ler2_dicionario(FILE * _fp_dic, dicionario * _dic, int * _posicao_livre, int _max_prob, int _max_mutacoes[])
{
	char pal[DIM_MAX];
	int tamanho = 0;

	while(fscanf(_fp_dic, "%s", pal) == 1)
	{	
		tamanho= strlen(pal);
		if((tamanho <= _max_prob) && (_max_mutacoes[tamanho-1] != 0))
		{
			escreve_palavra(_dic, tamanho - 1, _posicao_livre[tamanho - 1], pal);
			_posicao_livre[tamanho - 1]++;
		}
	}
}

/******************************************************************************
 * escreve_palavra()
 *
 * Argumentos: _dic - ponteiro para a estrutura do dicionario
 			   i - inteiro para o indice do tamanho de palavras que prentendemos
 			   j - inteiro para o indice da palavra que pretendemos desse tamanho
 			   pal - ponteiro para a palavra que pretendemos escrever
 * Retorna: (void)
 * Efeitos: escreve uma palavra no dicionario 
 *
 * Descrição: funcao que coloca a palavra na posicao pretendida da tabela
 *
 *****************************************************************************/

void escreve_palavra(dicionario * _dic, int i, int j, char * pal)
{
	strcpy(_dic->palavras[i][j], pal);
}

/******************************************************************************
 * ordenar()
 *
 * Argumentos: _dic - ponteiro para a estrutura do dicionario
			   _max_prob - inteiro que contem o problema de maior dimensao
 * Retorna: (void)
 * Efeitos: ordenar o dicionario 
 *
 * Descrição: funcao que correndo todos os tamanhos distintos (ate ao maior problema) 
 *			  invoca a funcao que ordena cada um dos tamanhos de cada vez
 *
 *****************************************************************************/

void ordenar(dicionario * _dic, int _max_prob)
{
	int i = 0;

	for(i = 0; i < _max_prob; i++)
		if(_dic->ocorrencias[i] != 0)
			quicksort(_dic->palavras[i], 0, _dic->ocorrencias[i] - 1);
}

/******************************************************************************
 * quicksort()
 *
 * Argumentos: _palavras - ponteiro para a tabela de palavras desse tamanho
 			   l - inteiro com o indice da primeira palavra
 			   r - inteiro com o indice da ultima palavra
 * Retorna: (void)
 * Efeitos: ordenar cada tamanho de palavras 
 *
 * Descrição: algoritmo recursivo que permite proceder a ordenacao alfabetica do dicionario
 *
 *****************************************************************************/

void quicksort(char ** _palavras, int l, int r)
{
 	int i = 0;

 	if (r <= l) 
 		return;

 	i = partition(_palavras, l, r);
 	quicksort(_palavras, l, i - 1);
 	quicksort(_palavras, i + 1, r);
}

/******************************************************************************
 * partition()
 *
 * Argumentos: _palavras - ponteiro para a tabela de palavras desse tamanho
 			   l - inteiro com o indice da primeira palavra
 			   r - inteiro com o indice da ultima palavra
 * Retorna: int
 * Efeitos: dividir a tabela 
 *
 * Descrição: funcao que sub-divide a tabela em duas parte
 *
 *****************************************************************************/

int partition(char ** _palavras, int l, int r)
{
 	int i = 0, j = 0;
 	char * v = NULL;

 	v = _palavras[r];
 	
 	i = l - 1; j = r;
 	
 	for( ; ; ) 
 	{
 		while (strcmp(_palavras[++i], v) < 0);
 		
 		while (strcmp(v, _palavras[--j]) < 0)
 			if (j == l) 
 				break;

 		if (i >= j) 
 			break;

 		troca_palavras(_palavras, i, j);
 		
 	}
 	
 	troca_palavras(_palavras, i, r);
 
 	return i;
}

/******************************************************************************
 * troca_palavras()
 *
 * Argumentos: _palavras - ponteiro para a tabela de palavras desse tamanho
 			   l - inteiro com o indice da primeira palavra que pretendemos trocar
 			   r - inteiro com o indice da outra palavra que pretendemos trocar
 * Retorna: (void)
 * Efeitos: trocar as palavras 
 *
 * Descrição: funcao que troca os ponteiros de duas strings
 *
 *****************************************************************************/

void troca_palavras(char ** _palavras, int i, int j)
{
	char * aux = NULL;

	aux = _palavras[i];
	_palavras[i] = _palavras[j];
	_palavras[j] = aux;
}

/******************************************************************************
 * libertar_dicionario()
 *
 * Argumentos: _dic - ponteiro para a estrutura do dicionario
			   _max_prob - inteiro que contem o problema de maior dimensao
 * Retorna: (void)
 * Efeitos: libertar toda a memoria 
 *
 * Descrição: funcao que faz free de toda a estrutura do dicionario
 *
 *****************************************************************************/

void libertar_dicionario(dicionario * _dic, int _max_prob)
{
  	int i = 0, j = 0;

	for(i = 0; i < _max_prob; i++)
  	{
  		if(_dic->ocorrencias[i] != 0)
  		{
  			for(j = 0; j < _dic->ocorrencias[i]; j++)
  			{
  				free(_dic->palavras[i][j]);
  			}

  			free(_dic->palavras[i]);
		}
	}

	free(_dic->palavras);

	libertar_vetor(_dic->ocorrencias);
	libertar_vetor(_dic->posicao_livre);

	free(_dic);
}

/******************************************************************************
 * libertar_vetor()
 *
 * Argumentos: vetor - ponteiro para o vetor
 * Retorna: (void)
 * Efeitos: libertar vetor 
 *
 * Descrição: funcao que faz a libertacao dos vetores
 *
 *****************************************************************************/

void libertar_vetor(int * vetor)
{
  	free(vetor);
}
