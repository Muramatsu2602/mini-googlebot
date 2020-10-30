/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#ifndef _LISTA_H
#define _LISTA_H

	#define inicial 0
	#define TAM_MAX 100
	#define ERRO -32000

	#define ORDENADA 0 // 0 for non sorted, 1 for sorted lists

	#include "item.h"

	typedef struct Lista LISTA;

	LISTA* lista_criar(void);
	boolean lista_inserir_fim(LISTA *lista, ITEM* item);
	boolean lista_inserir_ordenado(LISTA *lista, ITEM *item); // inserts ordered element by ID
	boolean lista_inserir_by_relevance(LISTA *lista, ITEM *item); // inserts ordered elements by RELEVANCE

	void lista_apagar(LISTA **lista);
	boolean lista_remover(LISTA *lista, int chave);
	ITEM* lista_busca(LISTA *lista, int chave); // Busca o item de chave X e retorna esse item
	LISTA *lista_busca_keyword(LISTA *lista, char *keyword);


	int lista_tamanho(LISTA *lista);
	boolean lista_vazia(LISTA *lista);
	boolean lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista);
	void lista_imprimir_short(LISTA *l); // prints only name and link of a given website

	void lista_apagar(LISTA **lista);
	void lista_inverter(LISTA **lista);
	boolean lista_verifica_igual(LISTA *lista1, LISTA *lista2);

#endif