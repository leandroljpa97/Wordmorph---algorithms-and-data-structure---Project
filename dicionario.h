/******************************************************************************
 *
 * Nome do ficheiro: dicionario.h
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Lê, cria, aloca, ordena e liberta todas as palavras do dicionário      
 *
 *****************************************************************************/

#ifndef _DICIONARIO_H
#define _DICIONARIO_H

 #include "defs.h"

typedef struct _dicionario dicionario;

int 	   * retorna_ocorrencias(dicionario * _dic);
int 	   * retorna_posicao_livre(dicionario * _dic);
char 	 *** retorna_palavras_dic(dicionario * _dic);
dicionario * inicializa_dicionario( int _max_prob);
int 	   * inicializar_vetor(int _max_prob);
void 	 	 resolve_dicionario(FILE * _fp_dic, dicionario * _dic, int _max_prob, int _max_mutacoes[]);
void 	 	 ler1_dicionario(FILE * _fp_dic, dicionario * _dic, int _max_prob, int _max_mutacoes[]);
dicionario * alocar_dicionario(dicionario * _dic, int _max_prob);
void 	 	 ler2_dicionario(FILE * _fp_dic, dicionario * _dic, int * _posicao_livre, int _max_prob, int _max_mutacoes[]);
void 		 escreve_palavra(dicionario * _dic, int i , int j, char * pal);
void 	 	 ordenar(dicionario * dic,int _max_prob);
void 	 	 quicksort(char ** _palavras, int l, int r);
int 	 	 partition(char ** _palavras, int l, int r);
void 		 troca_palavras(char ** _palavras, int i, int j);
void 		 libertar_dicionario(dicionario * _dic, int _max_prob);
void 		 libertar_vetor(int * _vetor);

#endif
