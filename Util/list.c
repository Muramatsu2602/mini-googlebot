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

    if (n == 0)
        n = lista_tamanho(l);

    printf("\nNAME\tURL\n");
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

void lista_busca_keyword(LISTA *lista, LISTA *key_list, char *keyword)
{
    if (lista == NULL || key_list == NULL || (lista_vazia(lista)) || keyword == NULL)
        return;

    NO *aux;
    ITEM *item = NULL;
    char **mat = NULL;

    // sequential search
    aux = lista->inicio;
    while (aux != NULL)
    {
        // each site has up to ten keywords
        // one of them has to be *keyword
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

void lista_tirar_repeticoes(LISTA *lista)
{
    NO *noAtual = lista->inicio;
    NO *noProximo = noAtual->proximo;
    
    while(noAtual->proximo !=NULL)
    {
        if(item_get_id(noAtual->item) == item_get_id(noAtual->proximo->item))
        {
            noProximo = noAtual->proximo->proximo;
            item_apagar(&noAtual->proximo->item);
            free(noAtual->proximo);
            noAtual->proximo = noProximo;
        }
        else
        {
            noAtual = noAtual->proximo;
        }
    }


}

void lista_sugerir_sites(LISTA *lista)
{
    // Primeiro passo: coletar todas as palavras-chave dos sites selecionados no passo anterior
    char **keywords = NULL;

    NO *noAtual = lista->inicio;

    char **aux;
    int numKeyWords = 0;
    int total = 0;
    
    // Copiar as palavras-chave para keyWords
    for(int i=0;i<lista->tamanho;i++)
    {
        aux = item_get_keyWords(noAtual->item);
        numKeyWords = item_get_numKeyWords(noAtual->item);

        keywords = (char **) realloc(keywords, (total+numKeyWords)*sizeof(char *));
        total += numKeyWords;

        for(int j=(total-numKeyWords), k=0;j<total;j++,k++)
        {
            keywords[j] = (char *) malloc((strlen(aux[k])+1)*sizeof(char));
            strcpy(keywords[j], aux[k]);
        }
        noAtual = noAtual->proximo;
    }

    LISTA *key_lista = NULL;
    key_lista = lista_criar();

    for(int i=0;i<total;i++)
    {
        lista_busca_keyword(lista, key_lista, keywords[i]);
    }

    lista_tirar_repeticoes(key_lista);

    lista_imprimir_short(key_lista,5);


    // Liberar a memória HEAP alocada para a matriz de strings <keywords> e para a lista <key_lista>
    for(int i=0;i<total;i++)
    {
        free(keywords[i]);
    }
    free(keywords);
    lista_apagar(&key_lista);
}