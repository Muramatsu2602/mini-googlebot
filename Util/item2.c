/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item2.h"

// REMEMBER ME: typedef struct item_ ITEM2;

struct item2_ // Cada item representa um site
{
    char key_word[50];
    NO **nos; // Guarda os endereços dos nós que contém esta palavra-chave
    int qtd_nos;
};

ITEM2 *item2_criar(void)
{
    ITEM2 *item;

    item = (ITEM2 *)malloc(sizeof(ITEM2));

    if (item == NULL)
    {
        printf("Erro ao alocar ITEM2!\n");
        return NULL;
    }

    item->nos = NULL;
    item->qtd_nos = 0;
    return (item);
}

boolean item2_add_no(ITEM2 *item, NO *no)
{
    item->qtd_nos++;
    item->nos = (NO **) realloc (item->nos, (item->qtd_nos)*sizeof(NO *));
    item->nos[(item->qtd_nos-1)] = no;
    // Ordenar nós por relevância
    item2_ordenar_nos(item->nos, item->qtd_nos);
}

// Algoritmo de ordenação InsertionSort para ordenar nós por relevância
void insertionSort2(NO **nos, int qtd)
{
    NO *key;
    int j;
    for(int i=1; i<qtd; i++)
    {
        key = nos[i];
        j = i - 1;

        // Move os elementos que são maiores do que a chave para uma posição a frente
        while(j >= 0 && item_get_relevance(nos[i]->item) > item_get_relevance(key->item))
        {
            nos[j+1] = nos[j];
            j = j - 1;
        }
        nos[j + 1] = key;
    }
}

boolean item2_apagar(ITEM2 **item) // Ponteiro de ponteiro
{
    // Verifica se o item enviado existe
    if ((*item) != NULL)
    {
        free((*item)->nos);
        free(*item);
        *item = NULL; /*
                            Quando é feito o free() a variavel continua existindo, terá o valor NULL
                            Este é o motivo de enviar um ponteiro duplo do item para a função, pois assim este valor pode ser também alterado (por referencia)
                            É uma precaução extra
                    */
        return (TRUE);
    }
    return (FALSE);
}

void item2_imprimir(ITEM2 *item)
{
    char **aux = NULL;

    if (item == NULL)
    {
        printf("O item enviado é NULO!\n");
        return;
    }
}

void item2_ordenar_nos(NO **nos, int qtd)
{
    insertionSort2(nos, qtd);
}

int item2_get_qtd_nos(ITEM2 *item)
{
    if(item != NULL)
        return item->qtd_nos;
    return -1;
}

NO **item2_get_nos(ITEM2 *item)
{
    if(item != NULL)
        return item->nos;
    return NULL;
}

void item2_set_keyWord(ITEM2 *item, char *word)
{
    if(item != NULL)
        strcpy(item->key_word, word);
    return;
}

char *item2_get_keyWord(ITEM2 *item)
{   
    if(item != NULL)
        return item->key_word;
    return NULL;
}