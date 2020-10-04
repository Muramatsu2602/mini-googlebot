#ifndef _LISTA_H
#define _LISTA_H

#define TRUE 1
#define FALSE 0
#define boolean int
#define inicial 0
#define TAM_MAX 100
#define ERRO -32000

#define ORDENADA 0 // 0 para lista não ordenada, 1 para listas ordenadas

#include "item.h"

typedef struct Lista LISTA;

LISTA *lista_criar(void);
boolean lista_inserir_fim(LISTA *lista, ITEM *item);
boolean lista_inserir_ordenado(LISTA *lista, ITEM *item);
boolean lista_remover(LISTA *lista, int chave);
void lista_apagar(LISTA **lista);
ITEM *lista_busca(LISTA *lista, int chave); // Busca o item de chave X e retorna esse item

int lista_tamanho(LISTA *lista);
boolean lista_vazia(LISTA *lista);
boolean lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);

int lista_remover_item2(LISTA *lista, int chave);
ITEM *lista_busca_rec(LISTA *lista, int chave);

#endif