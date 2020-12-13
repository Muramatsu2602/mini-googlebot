/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dll.h"

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
        n->anterior = NULL;
        return n;
    }
    return NULL;
}

ITEM *no_get_item(NO *no)
{
    if (no != NULL)
    {
        return no->item;
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
boolean lista_cheia()
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
    if (l == NULL || lista_vazia(l))
        return;

    NO *noAtual = l->inicio;
    char **aux = NULL;

    for (int i = 0; i < lista_tamanho(l); i++)
    {
        printf("[%04d]\t", item_get_id(noAtual->item));
        printf("%s\t\t", item_get_name(noAtual->item));
        printf("%04d\t", item_get_relevance(noAtual->item));
        printf("%s\t", item_get_mainUrl(noAtual->item));
        printf("%d\t", item_get_numKeyWords(noAtual->item));

        aux = item_get_keyWords(noAtual->item);
        for (int j = 0; j < item_get_numKeyWords(noAtual->item); j++)
        {
            printf("%s ", aux[j]);
        }
        printf("\n");

        noAtual = noAtual->proximo;
    }

    return;
}

void lista_imprimir_short(LISTA *l, int n)
{
    if (l == NULL || lista_vazia(l))
        return;

    NO *noAtual = l->inicio;

    if (n <= 0 || n > lista_tamanho(l))
        n = lista_tamanho(l);

    printf("\nNOME\tURL\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t", item_get_name(noAtual->item));
        printf("%s\t", item_get_mainUrl(noAtual->item));
        printf("\n");
        noAtual = noAtual->proximo;
    }

    return;
}

void lista_imprimir_short2(NO **nos, int n)
{
    for(int i=0; i<n; i++)
    {
        if(nos[i] != NULL)
        {
            printf("%s\t", item_get_name(nos[i]->item));
            printf("%s\t", item_get_mainUrl(nos[i]->item));
            printf("\n");
        }
    }
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

boolean lista_inserir_by_relevance(LISTA *lista, ITEM *item)
{
    if (lista == NULL || item == NULL)
        return FALSE;

    NO *pnovo = (NO *)malloc(sizeof(NO));
    pnovo->item = item;

    NO *noAtual;

    if (lista->inicio == NULL || item_get_relevance(lista->inicio->item) < item_get_relevance(pnovo->item))
    {
        pnovo->proximo = lista->inicio;
        lista->inicio = pnovo;
    }
    else
    {
        noAtual = lista->inicio;

        while (noAtual->proximo != NULL && item_get_relevance(noAtual->proximo->item) >= item_get_relevance(pnovo->item))
        {
            // Se a relevância entre dois websites são iguais, o critério de desempate será feito através de seus nomes (em ordem alfabética)
            if(item_get_relevance(noAtual->proximo->item) == item_get_relevance(pnovo->item) && (strcmp(item_get_name(noAtual->proximo->item),item_get_name(pnovo->item)) < 0))
            {
                break;
            }
            noAtual = noAtual->proximo;
        }
        pnovo->proximo = noAtual->proximo;
        noAtual->proximo = pnovo;
    }
    lista->tamanho++;
    return TRUE;
}

// Função auxiliar para a decisão de inserção/busca quanto a qual será a extremidade escolhida
boolean lista_decidir_extremidade(LISTA *lista, int chave)
{
    int distInicio = abs(chave - item_get_id(lista->inicio->item));
    int distFim = abs(chave - item_get_id(lista->fim->item));

    if (distInicio < distFim)
    {
        // TRUE = inicio
        return TRUE;
    }
    // FALSE = fim
    return FALSE;
}

NO *lista_inserir_inicio(LISTA *lista, ITEM *item)
{
    if (lista == NULL || item == NULL)
    {
        return NULL;
    }

    NO *pnovo = (NO *)malloc(sizeof(NO));
    pnovo->item = item;

    if (lista->inicio == NULL)
    {
        lista->inicio = pnovo;
        lista->fim = pnovo;
    }
    else
    {
        lista->inicio->anterior = pnovo;
        pnovo->proximo = lista->inicio;
    }

    lista->inicio = pnovo;
    pnovo->anterior = NULL;
    lista->tamanho++;
    return pnovo;
}

NO *lista_inserir_fim(LISTA *lista, ITEM *item)
{
    if (lista == NULL || item == NULL)
    {
        return NULL;
    }

    NO *pnovo = (NO *)malloc(sizeof(NO));
    pnovo->item = item;

    // Se for o primeiro nó da lista
    if (lista->inicio == NULL)
    {
        lista->inicio = pnovo;
        lista->fim = pnovo;
    }
    else
    {
        lista->fim->proximo = pnovo;
        pnovo->anterior = lista->fim;
    }
    pnovo->proximo = NULL;
    lista->fim = pnovo;
    lista->tamanho++;
    return pnovo;
}

// Insere o item enviado do fim para o inicio da lista, pois a chave do item enviado está mais próxima
// Do fim do que o inicio da lista, realizando menos operações
NO *lista_inserir_ordenado_fim(LISTA *lista, ITEM *item)
{
    NO *pnovo = (NO *)malloc(sizeof(NO));
    pnovo->item = item;

    NO *noAtual;
    noAtual = lista->fim;

    // Anda até que o noAtual seja menor do que o nó a ser inserido
    while (item_get_id(pnovo->item) < item_get_id(noAtual->item))
    {
        noAtual = noAtual->anterior;
    }

    // O NÓ entrará após o noAtual, então o proximo nó->anterior irá agora apontar para o pnovo
    noAtual->proximo->anterior = pnovo;
    pnovo->anterior = noAtual;
    pnovo->proximo = noAtual->proximo;
    noAtual->proximo = pnovo;
    lista->tamanho++;
    return pnovo;
}

// Insere o item enviado do inicio para o fim da lista, pois a chave do item enviado está mais próxima
// Do inicio do que o fim da lista, relizando menos operações
NO *lista_inserir_ordenado_inicio(LISTA *lista, ITEM *item)
{
    NO *pnovo = (NO *)malloc(sizeof(NO));
    pnovo->item = item;

    NO *noAtual;
    noAtual = lista->inicio;

    while (item_get_id(pnovo->item) > item_get_id(noAtual->item))
    {
        noAtual = noAtual->proximo;
    }

    noAtual->anterior->proximo = pnovo;
    pnovo->anterior = noAtual->anterior;
    pnovo->proximo = noAtual;
    noAtual->anterior = pnovo;
    lista->tamanho++;
    return pnovo;
}

NO *lista_inserir_ordenado(LISTA *lista, ITEM *item)
{
    if (lista == NULL || item == NULL)
        return FALSE;

    // Caso 1: inserir no inicio da lista
    if (lista->inicio == NULL || item_get_id(item) < item_get_id(lista->inicio->item))
    {
        return lista_inserir_inicio(lista, item);
    }

    // Caso 2: inserir no fim da lista
    if (item_get_id(item) > item_get_id(lista->fim->item))
    {
        return lista_inserir_fim(lista, item);
    }

    // Caso 3: inserir no meio da lista

    // Decidir se irá buscar a posição em que o item será inserido a partir do inicio
    // ou a partir do fim da lista
    if (lista_decidir_extremidade(lista, item_get_id(item)))
    {
        return lista_inserir_ordenado_inicio(lista, item);
    }
    else
    {
        return lista_inserir_ordenado_fim(lista, item);
    }
    return NULL;
}

// Enviar o primeiro nó da lista
void lista_apagar(LISTA **lista)
{
    NO *noAtual = (*lista)->inicio;
    // Caso base: no Atual é nulo, ou seja, a lista inteira já foi apagada
    if (noAtual != NULL)
    {
        (*lista)->tamanho--;
        (*lista)->inicio = noAtual->proximo;
        if (!item_apagar(&noAtual->item))
        {
            printf("Erro ao apagar item!\n");
            return;
        }
        free(noAtual);
        noAtual = NULL;
        lista_apagar(lista);
    }
    else
    {
        // Todos já foram apagados, dar free na lista
        free(*lista);
    }
}

// Igual a função lista_busca_ordenada, porém retorna o NÓ encontrado
// É interna do .c, ou seja, não há declaração de cabeçalho no arquivo .h
NO *lista_busca_ordenada2(LISTA *lista, int chave)
{
    NO *aux = NULL;

    if (lista != NULL)
    {
        // Se a chave a ser buscada for maior do que a chave do último item da lista ou for menor do que a chave
        // do primeiro item da lista já se sabe que o ITEM buscado não existe (Funciona para listas ordenadas de
        // forma crescente).
        if (chave > item_get_id(lista->fim->item) || chave < item_get_id(lista->inicio->item))
        {
            return NULL;
        }

        // onde comecar a busca vai depender da relacao da chave com os valores do id na lista

        // procurando do inicio (esq-->dir)
        if (lista_decidir_extremidade(lista, chave))
        {
            aux = lista->inicio;
            while (aux != NULL && item_get_id(aux->item) <= chave)
            {
                if (item_get_id(aux->item) == chave)
                    return aux;

                aux = aux->proximo;
            }
        }
        // procurando do fim (dir-->esq)
        else
        {
            aux = lista->fim;
            while (aux != NULL && item_get_id(aux->item) >= chave)
            {
                if (item_get_id(aux->item) == chave)
                    return aux;

                aux = aux->anterior;
            }
        }
    }
    return NULL;
}

NO *lista_busca_ordenada(LISTA *lista, int chave)
{
    NO *no = NULL;

    no = lista_busca_ordenada2(lista, chave);
    if (no == NULL)
    {
        return NULL;
    }

    return no;
}

void lista_busca_keyword(LISTA *lista, LISTA *key_list, char *keyword)
{
    if (lista == NULL || key_list == NULL || (lista_vazia(lista)) || keyword == NULL)
        return;

    NO *aux;
    ITEM *item = NULL;
    char **mat = NULL;

    // Busca sequencial
    aux = lista->inicio;
    while (aux != NULL)
    {
        // Cada site possui até 10 palavras-chave
        // Alguma dessas pode ser a palavra buscada
        mat = item_get_keyWords(aux->item);

        // Verifica se o item atual contém a palavra-chave buscada
        // O FOR roda até que as palavra-chaves do item atual se esgotem (pior caso) OU até quando a palavra-chave
        // atual já ultrapassa alfabeticamente a palavra-chave buscada (evitando comparações desnecessárias) 
        for (int i = 0; (i < item_get_numKeyWords(aux->item)) && (strcmp(mat[i], keyword) <= 0); i++)
        {
            if (strcmp(mat[i], keyword) == 0)
            {
                item = item_copy(aux->item);
                lista_inserir_by_relevance(key_list, item);
                break;
            }
        }
        aux = aux->proximo;
    }

    if (lista_vazia(key_list))
        printf("Nenhum site encontrado para a keyword: %s\n", keyword);
}

//

boolean lista_remover(LISTA *lista, int chave)
{
    NO *noAtual = NULL;

    if (lista != NULL && !lista_vazia(lista))
    {
        noAtual = lista_busca_ordenada2(lista, chave);

        if (noAtual != NULL)
        {
            // decidindo em que regiao procurar o local pra remocao

            // Se este nó for o primeiro da lista
            if (noAtual == lista->inicio)
            {
                lista->inicio = lista->inicio->proximo;
                lista->inicio->anterior = NULL;
            }
            else
            {
                noAtual->anterior->proximo = noAtual->proximo;
            }

            if (noAtual == lista->fim)
            {
                lista->fim = noAtual->anterior;
            }
            else
            {
                noAtual->proximo->anterior = noAtual->anterior;
            }

            item_apagar(&noAtual->item);
            noAtual->proximo = NULL;
            noAtual->anterior = NULL;
            free(noAtual);
            noAtual = NULL;
            lista->tamanho--;
            return TRUE;
        }
    }
    return FALSE;
}

void lista_tirar_repeticoes(LISTA *lista)
{
    NO *noAtual = lista->inicio;
    NO *noProximo = noAtual->proximo;

    while (noAtual->proximo != NULL)
    {
        if (item_get_id(noAtual->item) == item_get_id(noAtual->proximo->item))
        {
            noProximo = noAtual->proximo->proximo;
            item_apagar(&noAtual->proximo->item);
            free(noAtual->proximo);
            noAtual->proximo = noProximo;
            lista->tamanho--;
        }
        else
        {
            noAtual = noAtual->proximo;
        }
    }
}
