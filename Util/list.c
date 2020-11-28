/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    NO *anterior;
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
        n->anterior = NULL;
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
            noAtual = noAtual->proximo;
        }
        pnovo->proximo = noAtual->proximo;
        noAtual->proximo = pnovo;
    }
    lista->tamanho++;
    return TRUE;
}

boolean lista_inserir_ordenado(LISTA *lista, ITEM *item)
{
    if (lista == NULL || item == NULL)
        return FALSE;

    NO *pnovo = (NO *)malloc(sizeof(NO));
    pnovo->item = item;

    NO *noAtual;

    if (lista->inicio == NULL || item_get_id(lista->inicio->item) >= item_get_id(pnovo->item))
    {
        pnovo->proximo = lista->inicio;
        lista->inicio = pnovo;
    }
    else
    {
        noAtual = lista->inicio;

        while (noAtual->proximo != NULL && item_get_id(noAtual->proximo->item) < item_get_id(pnovo->item))
        {
            noAtual = noAtual->proximo;
        }
        pnovo->proximo = noAtual->proximo;
        noAtual->proximo = pnovo;
    }
    lista->tamanho++;
    return TRUE;
}

boolean lista_inserir_fim(LISTA *lista, ITEM *item)
{
    if (item == NULL)
    {
        printf("item enviado é nulo!");
        return FALSE;
    }
    if ((!lista_cheia()) && (lista != NULL))
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
        for (int i = 0; i < item_get_numKeyWords(aux->item); i++)
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

boolean lista_remover(LISTA *lista, int chave)
{
    NO *noAtual;

    if(lista != NULL && !lista_vazia(lista))
    {
        noAtual = lista_busca_ordenada(lista, chave);

        if(noAtual != NULL)
        {
            // Se este nó for o primeiro da lista
            if(noAtual == lista->inicio)
            {
                lista->inicio = lista->inicio->proximo;
                lista->inicio->anterior = NULL;
            }
            else
            {
                noAtual->anterior->proximo = noAtual->proximo;
            }

            if(noAtual == lista->fim)
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

void lista_sugerir_sites(LISTA *lista)
{
    if(lista == NULL || lista_vazia(lista))
    {
        return;
    }
    // Primeiro passo: coletar todas as palavras-chave dos sites selecionados no passo anterior
    char **keywords = NULL;

    NO *noAtual = lista->inicio;

    char **aux;
    int numKeyWords = 0;
    int total = 0;

    // Copiar as palavras-chave para keyWords
    for (int i = 0; i < lista->tamanho; i++)
    {
        aux = item_get_keyWords(noAtual->item);
        numKeyWords = item_get_numKeyWords(noAtual->item);

        keywords = (char **)realloc(keywords, (total + numKeyWords) * sizeof(char *));
        total += numKeyWords;

        for (int j = (total - numKeyWords), k = 0; j < total; j++, k++)
        {
            keywords[j] = (char *)malloc((strlen(aux[k]) + 1) * sizeof(char));
            strcpy(keywords[j], aux[k]);
        }
        noAtual = noAtual->proximo;
    }

    LISTA *key_lista = NULL;
    key_lista = lista_criar();

    // Inserir em key_lista todos os itens que possuem as palavras-chaves encontradas
    for (int i = 0; i < total; i++)
    {
        lista_busca_keyword(lista, key_lista, keywords[i]);
    }

    if(key_lista == NULL || lista_vazia(key_lista))
    {
        // Liberar memória HEAP
        lista_apagar(&key_lista);
        for (int i = 0; i < total; i++)
        {
            free(keywords[i]);
        }
        free(keywords);
        return;
    }

    // Tirar as repetições na lista <key_lista>
    lista_tirar_repeticoes(key_lista);

    // Imprime o nome e o link dos 5 sites mais relevantes (se encontrar menos de 5 sites imprime apenas os que encontrou)
    lista_imprimir_short(key_lista, TOP_RELEVANCE_NUM);

    // Liberar a memória HEAP alocada para a matriz de strings <keywords> e para a lista <key_lista>
    for (int i = 0; i < total; i++)
    {
        free(keywords[i]);
    }
    free(keywords);
    lista_apagar(&key_lista);
}
