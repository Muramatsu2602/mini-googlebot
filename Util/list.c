#include <stdio.h>
#include <stdlib.h>

#include "list.h"
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

int lista_tamanho(LISTA *lista)
{
    if (lista)
        return lista->tamanho;
    exit(1);
}

boolean lista_vazia(LISTA *lista)
{
    if ((lista != NULL) && lista->inicio == NULL)
        return TRUE;
    else
        return FALSE;
}

boolean lista_cheia(LISTA *l)
{
    NO *no = (NO *)malloc(sizeof(NO));

    if (no != NULL)
    {
        free(no);
        no = NULL;
        return (FALSE);
    }
    return (TRUE);
}


// remove item especifico da lista
boolean lista_remover(LISTA *lista, int chave)
{
    NO *aux = NULL;
    NO *p = NULL;

    if (lista != NULL)
    {
        p = lista->inicio;

        while (p != NULL && item_get_chave(p->item) != chave)
        {
            aux = p;
            p = p->proximo;
        }

        // chegamos no final da lista OU achamos o no a ser removido
        if (p != NULL) // elemento esta na lista (p nao esta nulo, carac do fim)
        {
            if (p == lista->inicio)
            {
                lista->inicio = p->proximo;
                p->proximo = NULL;
            }
            // esta no meio
            else
            {
                aux->proximo = p->proximo;
                p->proximo = NULL;
            }

            if (p == lista->fim)
            {
                lista->fim = aux;
            }

            free(p);
            lista->tamanho--;
            return TRUE;
        }
    }
    return FALSE; // a lista nao existe ou nao encontramos o item
}

// Inverte lista iterativamente
LISTA *lista_inverter(LISTA *lista)
{
    // podemos inverter uma lista se ela existe e nao eh vazia
    if (lista == NULL || lista_vazia(lista))
    {
        return NULL;
    }

    // 
    NO *atual = lista->inicio;
    NO *anterior = NULL;
    NO *prox = NULL;

    // aplicando SWAPs
    while (atual != NULL)
    {
        prox = atual->proximo;
        atual->proximo = anterior;

        // colocando pointeros para frente
        anterior = atual;
        atual = prox;
    }

    // corrigindo as extremidades da lista
    lista->inicio = anterior;
    lista->fim = prox;

    printf("Lista invertida com sucesso!\n");
    
    return lista;
}

void lista_imprimir(LISTA *lista)
{
    // Podemos imprimir uma lista nao vazia e que exista
    NO *p = NULL;

    if (lista != NULL && !lista_vazia(lista))
    {
        p = lista->inicio;
        int i;

        printf("Imprimindo a lista de tamanho %d!\n",lista->tamanho);
        // percorremos os nos a partir do inicio da lista
        for (i = 0; i < lista->tamanho; i++)
        {
            printf("[%d]\n", item_get_chave(p->item));
            p = p->proximo;
        }

        return;
    }
    printf(" A lista esta vazia ou NULA");
}

void lista_apagar(LISTA **lista)
{
    NO *p = NULL;
    p = (*lista)->inicio;

    // podemos apagar uma lista nao nula
    if (*lista == NULL)
        return;

    for (int i = 0; i < (*lista)->tamanho; i++)
    {
        item_apagar(&p->item);
        p = p->proximo;
    }

    free(*lista);
    *lista = NULL;
    return;
}