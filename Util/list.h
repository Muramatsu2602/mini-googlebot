/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#ifndef _LISTA_H
#define _LISTA_H

	#define inicial 0
	#define TAM_MAX 100
	#define ERRO -32000
	#define TOP_RELEVANCE_NUM 5

	#define ORDENADA 0 // 0 for non sorted
					   // 1 for sorted lists

	#include "item.h"

	typedef struct Lista LISTA;

	LISTA* lista_criar(void);
	boolean lista_inserir_fim(LISTA *lista, ITEM* item);
	boolean lista_inserir_ordenado(LISTA *lista, ITEM *item);     			// inserts ordered element by ID
	boolean lista_inserir_by_relevance(LISTA *lista, ITEM *item); 			// inserts ordered elements by RELEVANCE

	void lista_apagar(LISTA **lista); 						        		// erases whole list
	boolean lista_remover(LISTA *lista, int chave);							// removes item given an ID
	ITEM* lista_busca(LISTA *lista, int chave); 							// Searches for an item that has and ID x and returns it
	void lista_busca_keyword(LISTA *lista, LISTA *key_list, char *keyword); // Searches for an item given a keyword


	int lista_tamanho(LISTA *lista);										// returns size of the list
	boolean lista_vazia(LISTA *lista);										// checks if list is empty
	boolean lista_cheia(void);												// checks if heap allocation is possible
	void lista_imprimir(LISTA *lista);										// prints all properties of all given items
	void lista_imprimir_short(LISTA *l, int n); 							// prints only name and link of a given website

	void lista_apagar(LISTA **lista);										// 
	void lista_inverter(LISTA **lista);
	boolean lista_verifica_igual(LISTA *lista1, LISTA *lista2);

	void lista_sugerir_sites(LISTA *lista);
	void lista_tirar_repeticoes(LISTA *lista);

#endif