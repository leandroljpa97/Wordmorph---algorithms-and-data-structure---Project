/******************************************************************************
 *
 * Nome do ficheiro: main.c
 *        (c) 2016 AED
 * Autores: Diogo Rodrigues, Nº 84030
 *          Leandro Almeida, Nº 84112
 * Última modificação: 2016-12-11
 *
 * COMENTÁRIOS
 *    Programa Principal      
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "dicionario.h"
#include "lista_adjacencias.h"
#include "grafo.h"
#include "heap.h"
#include "ficheiros.h"

/******************************************************************************
 * main ()
 *
 * Argumentos: argc - número de argumentos
 *             argv - tabela de ponteiros para a string de argumentos
 * Retorna: int
 * Efeitos-colaterais: nenhuns
 *
 * Descrição: Programa Principal
 *
 *****************************************************************************/

int main(int argc, char *argv[]) 
{
  	char * ficheiro_in_prob = NULL, * ficheiro_in_dic = NULL, * ficheiro_out = NULL;

	FILE * fp_prob = NULL, * fp_dic = NULL, * fp_out = NULL;

    /*Tamanho do maior problema*/
    int max_prob = 0;

    int max_mutacoes[DIM_MAX] = {0};
   
    dicionario * dic = NULL;

    lista_adj *** grafos = NULL;

    /*Caso o número de argumentos seja menor do que deve ser*/
    if(argc < 3)
      exit(0);
  
  	ficheiro_in_dic = argv[1];
    ficheiro_in_prob = argv[2];

  	ficheiro_out = verificar_ficheiros(ficheiro_in_dic, ficheiro_in_prob, ficheiro_out);

    fp_prob = fopen(ficheiro_in_prob, "r");

    if(fp_prob == NULL)
      exit(0);  

    ler1_problemas(fp_prob, &max_prob,max_mutacoes);

    fseek(fp_prob, 0, SEEK_SET);

    dic = inicializa_dicionario(max_prob);

    fp_dic = fopen(ficheiro_in_dic, "r");

    if(fp_dic == NULL)
      exit(0); 

    resolve_dicionario(fp_dic, dic, max_prob, max_mutacoes); 

    grafos = criar_grafos(dic, max_prob, max_mutacoes );

  	fp_out = fopen(ficheiro_out, "w");

  	if(fp_out == NULL)
      exit(0);    

  	ler2_resolve_problemas(fp_prob, fp_out, dic, grafos);
  
    liberta_memoria(grafos,dic,max_prob);

    libertar_dicionario(dic, max_prob);

    free(ficheiro_out);

  	fclose(fp_dic);
  	fclose(fp_prob);
  	fclose(fp_out);
  	
  	return 0; 
}