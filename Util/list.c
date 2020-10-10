#include <stdio.h>
#include <stdlib.h>

#include "list.h"

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

/*
    Verifica se a lista está vazia. Retorna TRUE em caso positivo e FALSE
    caso contrário
*/
boolean lista_vazia(LISTA *lista)
{
    if ((lista != NULL) && lista->inicio == NULL)
    {
        return TRUE;
    }
    return FALSE;
}

/*
    Verifica se a lista está cheia. Retorna TRUE em caso positivo e FALSE
    caso contrário
*/
boolean lista_cheia(LISTA *lista)
{
    // Verifica se consegue criar outro nó, senão a lista está cheia
    NO *no = (NO *)malloc(sizeof(NO));
    if (no != NULL)
    {
        free(no);
        no = NULL;
        return FALSE;
    }
    return TRUE;
}

int lista_tamanho(LISTA *lista)
{
    return (lista->tamanho);
}

void lista_imprimir(LISTA *l)
{
    NO *noAtual = l->inicio;
    for (int i = 0; i < l->tamanho; i++)
    {
        printf("ID:%d\n", item_get_id(noAtual->item));
        printf("%s\t%04hu\t%s\t%s", item_ge(noAtual->item));

        noAtual = noAtual->proximo;
    }
    printf("\n");
    return;
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

boolean lista_inserir_ordenado(LISTA *lista, ITEM *item)
{

    if (lista == NULL || item == NULL)
        return FALSE;

    NO *pnovo = (NO *)malloc(sizeof(NO));
    pnovo->item = item;
    pnovo->proximo = NULL;

    if (pnovo == NULL)
        return FALSE;

    if (lista_vazia(lista))
    {
        pnovo->proximo = lista->inicio;
        lista->inicio = pnovo;
        lista->tamanho++;
        return TRUE;
    }
    else
    {
        if (item_get_id(pnovo->item) < item_get_id(lista->inicio->item))
        {

            NO *aux = lista->inicio;
            lista->inicio = pnovo;
            lista->inicio->proximo = aux;
            aux = NULL;
            lista->tamanho++;
            return TRUE;
        }

        NO *noAnterior = lista->inicio;
        NO *temp = lista->inicio->proximo;

        while (temp != NULL && item_get_id(pnovo->item) >= item_get_id(temp->item))
        {
            noAnterior = temp;
            temp = temp->proximo;
        }

        if (temp == NULL)
            noAnterior->proximo = pnovo;
        else
        {
            pnovo->proximo = temp;
            noAnterior->proximo = pnovo;
        }
    }
    lista->tamanho++;
    return TRUE;
}

boolean lista_inserir_fim(LISTA *lista, ITEM *item)
{
    if ((!lista_cheia(lista)) && (lista != NULL))
    {
        NO *pnovo = (NO *)malloc(sizeof(NO));
        // Testar se a lista está vazia
        if (lista->inicio == NULL)
        {
            pnovo->item = item;
            lista->inicio = pnovo;
            pnovo->proximo = NULL;
        }
        // Se não estiver vazia pega o NÓ que está no fim da lista
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

// Enviar o primeiro nó da lista
void lista_apagar(LISTA **lista)
{

    NO *noAtual = (*lista)->inicio;
    // Caso base: no Atual é nulo, ou seja, a lista inteira já foi apagada
    NO *noProximo;
    if (noAtual != NULL)
    {
        noProximo = noAtual->proximo;
        if (!item_apagar(&noAtual->item))
        {
            printf("Erro ao apagar item!\n");
            return;
        }
        free(noAtual);
        noAtual = NULL;
        (*lista)->tamanho--;
        (*lista)->inicio = noProximo;
        lista_apagar(lista);
    }
    else
    {
        // Todos já foram apagados, dar free na lista
        free(*lista);
    }
}

void lista_inverter(LISTA **lista)
{
    // Tem vários algoritmos para inverter a lista
    NO *noAtual = (*lista)->inicio;
    (*lista)->fim = noAtual; // Já define o primeiro nó agora como o último nó da lista
    NO *noAnterior = NULL;
    NO *noProximo = NULL;

    while (noAtual != NULL)
    {
        noProximo = noAtual->proximo; // Pega o próximo nó da lista (1 iteração: será NULL)
        /*
            Na primeira vez o nó atual é o primeiro da lista e seu ponteiro próximo é deverá ser nulo. Como vamos inverter a ordem dos nós
            o primeiro nó será agora o último da lista e o ponteiro de seu próximo pontará para ele.
        */
        noAtual->proximo = noAnterior;
        noAnterior = noAtual; // Pega o nó atual para que seja utilizado na proximo iteração do while
        noAtual = noProximo;  // O nó a ser manipulado agora será o proximo da lista original
    }

    // Redefine o inicio da lista como o último nó da original
    (*lista)->inicio = noAnterior;
}

// Busca sequencial de itens, para listas não ordenadas
ITEM *lista_busca_sequencial(LISTA *lista, int chave)
{
    NO *aux;
    if (lista != NULL)
    {
        aux = lista->inicio;
        while (aux != NULL)
        {
            if (item_get_id(aux->item) == chave)
            {
                return aux->item;
            }
            aux = aux->proximo;
        }
    }
    return NULL;
}

ITEM *lista_busca_ordenada(LISTA *lista, int chave)
{
    NO *aux;
    if (lista != NULL)
    {
        aux = lista->inicio;
        while (aux != NULL && item_get_id(aux->item) <= chave)
        {
            if (item_get_id(aux->item) == chave)
            {
                return aux->item;
            }
            aux = aux->proximo;
        }
    }
    return NULL;
}

ITEM *lista_busca(LISTA *lista, int chave)
{
    ITEM *x;

    if (!ORDENADA)
    {
        x = lista_busca_sequencial(lista, chave);
    }
    else
    {
        x = lista_busca_ordenada(lista, chave);
    }
    return x;
}

/*
// Versão 1 do lista_remover
boolean lista_remover(LISTA *lista, int chave)
{
    NO *noAtual;
    NO *noAnterior = NULL;
    NO *noProximo = NULL;

    noAtual = lista->inicio;
    while(noAtual != NULL && item_get_chave(noAtual->item) !=  chave)
    {
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if(noAtual != NULL)
    {
        // Achou o nó a ser removido
        if(noAtual == lista->inicio)
        {
            noAnterior = noAtual;
            noAtual = noAtual->proximo;

            lista->inicio = noAtual;

            // Excluir o nó anterior
            item_apagar(&noAnterior->item);
            free(noAnterior);
            noAnterior = NULL;
            lista->tamanho--;
            return TRUE;
        }
        else if(noAtual == lista->fim)
        {
            lista->fim = noAnterior;

            // Excluir o nó
            item_apagar(&noAtual->item);
            free(noAtual);
            noAtual = NULL;
            lista->tamanho--;
            return TRUE;
        }
        else
        {
            // É um nó no meio da lista
            noProximo = noAtual->proximo;

            noAnterior->proximo = noProximo;
            item_apagar(&noAtual->item);
            free(noAtual);
            noAtual = NULL;
            lista->tamanho--;
            return TRUE;
        }
    }
    return FALSE;
}
*/

// Versão 2 do lista_remover -> mais eficiente!
boolean lista_remover(LISTA *lista, int chave)
{
    NO *noAtual;
    NO *noAnterior = NULL;
    NO *noProximo = NULL;

    noAtual = lista->inicio;
    while (noAtual != NULL && item_get_id(noAtual->item) != chave)
    {
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if (noAtual != NULL)
    {
        // Achou o nó a ser removido
        if (noAtual == lista->inicio)
        {
            // É o primeiro nó da lista

            noAnterior = noAtual;
            noAtual = noAtual->proximo;

            lista->inicio = noAtual;

            // Excluir o nó anterior (que era o atual)
            item_apagar(&noAnterior->item);
            free(noAnterior);
            noAnterior = NULL;
            lista->tamanho--;
            return TRUE;
        }
        else
        {
            if (noAtual == lista->fim)
            {
                // É o último nó da lista

                noAnterior->proximo = NULL;
                lista->fim = noAnterior;
            }
            else
            {
                // É um nó no meio da lista

                noProximo = noAtual->proximo;
                noAnterior->proximo = noProximo;
            }

            // Excluir o nó
            item_apagar(&noAtual->item);
            free(noAtual);
            noAtual = NULL;
            lista->tamanho--;
            return TRUE;
        }
    }
    return FALSE;
}

boolean lista_verifica_no(NO *n1, NO *n2)
{
    // Os 2 nós tem que terminar juntos
    if (n1 == NULL && n2 == NULL)
    {
        return TRUE;
    }

    // Verifica se as chaves de cada item são iguais
    if (item_get_id(n1->item) != item_get_id(n2->item))
    {
        return FALSE;
    }
    else
    {
        // Chamada recursiva para o próximo nó
        lista_verifica_no(n1->proximo, n2->proximo);
    }
    return TRUE;
}

boolean lista_verifica_igual(LISTA *lista1, LISTA *lista2)
{
    // Verificar se o tamanho das listas são iguais
    if (lista1->tamanho != lista2->tamanho)
    {
        return FALSE;
    }

    NO *noAtual1 = lista1->inicio;
    NO *noAtual2 = lista2->inicio;

    // A função lista_verifica_no é uma função recursiva que verifica os nós a partir do primeiro nó
    if (lista_verifica_no(noAtual1, noAtual2))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}