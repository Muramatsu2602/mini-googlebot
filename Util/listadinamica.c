#include <stdio.h>
#include <stdlib.h>
#include "listadinamica.h"
#include "item.h"

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    NO *proximo;
};

struct Lista
{
    NO *inicio;
    NO *fim;
    int tamanho;
};

NO *no_criar(ITEM *item)
{
    NO *n = (NO *)malloc(sizeof(NO));

    if ((n != NULL) && (item != NULL))
    {
        n->item = item;
        n->proximo = NULL;
        return n;
    }
    return NULL;
}

LISTA *lista_criar(void)
{
    // Alocar espaço na memória para os itens
    LISTA *lista;
    lista = (LISTA *)malloc(sizeof(LISTA));

    if (lista != NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }

    return lista;
}

boolean lista_inserir_fim(LISTA *lista, ITEM *item)
{
    if ((!lista_cheia(lista)) && (lista != NULL))
    {
        NO *pnovo = (NO *)malloc(sizeof(NO));
        // se vazia, muda os ponteiros
        if (lista->inicio == NULL)
        {
            pnovo->item = item;
            lista->inicio = pnovo;
            pnovo->proximo = NULL;
        }
        // se nao vazia, muda o ponteiro deproximo, fim e so
        else
        {
            lista->fim->proximo = pnovo;
            pnovo->item = item;
            pnovo->proximo = NULL;
        }
        lista->fim = pnovo;
        lista->tamanho++;

        return TRUE;
    }
    return FALSE;
}

boolean lista_remover(LISTA *lista, int chave)
{
    
}

boolean lista_cheia(LISTA *lista)
{
    if ((lista != NULL) &&)
    {
    }
}

int lista_tamanho(LISTA *lista)
{
}
