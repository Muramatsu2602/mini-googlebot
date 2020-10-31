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

	#define ORDENADA 0 // 0 para listas não ordenada, 1 para listas ordenadas

	#include "item.h"

	typedef struct Lista LISTA;

	LISTA* lista_criar(void);
	boolean lista_inserir_fim(LISTA *lista, ITEM* item);
	boolean lista_inserir_ordenado(LISTA *lista, ITEM *item); // Inserir itens de forma ordenada através do ID
	boolean lista_inserir_by_relevance(LISTA *lista, ITEM *item); // Inserir itens de forma ordenada através da relevância

	void lista_apagar(LISTA **lista);
	boolean lista_remover(LISTA *lista, int chave);
	ITEM* lista_busca(LISTA *lista, int chave); // Busca o item de chave X e retorna esse item
	void lista_busca_keyword(LISTA *lista, LISTA *key_list, char *keyword);


	int lista_tamanho(LISTA *lista);
	boolean lista_vazia(LISTA *lista);
	boolean lista_cheia(void);
	void lista_imprimir(LISTA *lista);
	void lista_imprimir_short(LISTA *l, int n); // Imprime apenas o nome e o link dos sites da lista enviada

	void lista_apagar(LISTA **lista);
	void lista_inverter(LISTA **lista);
	boolean lista_verifica_igual(LISTA *lista1, LISTA *lista2);

	void lista_sugerir_sites(LISTA *lista);
	void lista_tirar_repeticoes(LISTA *lista);

#endif