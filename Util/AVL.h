/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#ifndef _AVL_H
#define _AVL_H

	#define ERRO -32000
	#define FILHO_ESQ 0
	#define FILHO_DIR 1

	#define max(a, b) ((a>b) ? a : b)

	#include "item2.h"

	typedef struct no2_ NO2;
	typedef struct avl_ AVL;

	boolean avl_inserir(AVL *T, ITEM2 *item);
	AVL *avl_criar(void);
	void avl_apagar_arvore(AVL **T);

	int get_profundidade(AVL *arv);
	void avl_printa_arvore(AVL *arv);
	int avl_conta_folhas(AVL *arv);
	int avl_conta_nos(AVL *arv);

	ITEM2 *avl_busca(AVL *T, char *chave);
	boolean avl_remover(AVL *T, char *chave);
	boolean avl_verifica_balanceada(AVL *T);

#endif