#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

// REMEMBER ME: typedef struct item_ ITEM;

struct item_ // each item represents a website
{
    int id;
    char name[50];
    int relevance;
    char mainUrl[100];
    int numKeyWords; // Limit = 10 key words
    char **keyWords; //  Limit = 50 char per word
};

boolean item_inserir_dados(char *string, ITEM *item)
{
    char *ptr = NULL;
    item_set_keyWords(item, NULL);
    item_set_numKeyWords(item, 0);

    // 1 - Código
    ptr = strtok(string, ",");
    if (ptr == NULL)
    {
        printf("STRTOK1!\n");
        return FALSE;
    }
    item_set_id(item, atoi(ptr));

    // 2 - Nome
    ptr = strtok(NULL, ",");
    if (ptr == NULL)
    {
        printf("STRTOK2!\n");
        return FALSE;
    }
    item_set_name(item, ptr);

    // 3 - Relevancia
    ptr = strtok(NULL, ",");
    if (ptr == NULL)
    {
        printf("STRTOK3!\n");
        return FALSE;
    }
    item_set_relevance(item, atoi(ptr));

    // 4 - URL
    ptr = strtok(NULL, ",");
    if (ptr == NULL)
    {
        printf("STRTOK4!\n");
        return FALSE;
    }
    item_set_mainUrl(item, ptr);

    // 5 - Palavras-Chave
    // Ler as palavras chave até que strtok retorne NULO
    ptr = strtok(NULL, ",");
    while (ptr != NULL && item->numKeyWords <= 10)
    {
        item->numKeyWords++;

        item->keyWords = (char **)realloc(item->keyWords, item->numKeyWords * sizeof(char *));
        item->keyWords[item->numKeyWords - 1] = (char *)malloc((1 + strlen(ptr)) * sizeof(char));
        strcpy(item->keyWords[item->numKeyWords - 1], ptr);

        ptr = strtok(NULL,",");
    }

    return TRUE;
}

// A função recebe a string com todos os dados e chama uma função auxiliar para separar essa string nos devidos campos
ITEM *item_criar(char *string)
{
    ITEM *item;

    item = (ITEM *)malloc(sizeof(ITEM));

    if (item != NULL)
    {
        /* Setar o ID, nome, relevancia, link */
        if (!item_inserir_dados(string, item))
        {
            printf("ERRO ITEM_INSERIR_DADOS!");
            return NULL;
        }
    }

    // it will return NULL if alocation doesnt work
    return (item);
}

boolean item_apagar(ITEM **item) // pointer to a pointer
{
    // we can only erase existing items
    if ((*item) != NULL)
    {
        for (int i = 0; i < (*item)->numKeyWords; i++)
        {
            free((*item)->keyWords[i]);
        }
        free((*item)->keyWords);
        (*item)->keyWords = NULL;

        free(*item);
        *item = NULL; // --> variable still exists, so it will be NULL (disables its future usage post-erase)
                      // this is why we use a double pointer, so we can alter its value (by reference) too
                      // It is an extra precaution
        return (TRUE);
    }
    return (FALSE);
}

void item_imprimir(ITEM *item)
{
    char **aux = NULL;

    if (item == NULL)
    {
        printf("CANNOT PRINT! Item is empty!\n");
        return;
    }

    printf("ID:%d\n", item_get_id(item));
    printf("NAME:%s\n", item_get_name(item));
    printf("RELEVANCE:%04d\n", item_get_relevance(item));
    printf("URL:%s\n", item_get_mainUrl(item));
    printf("NUM KEYWORDS:%02d\n", item_get_numKeyWords(item));
    printf("KEYWORDS:\n");

    aux = item_get_keyWords(item);
    for (int j = 0; j < item_get_numKeyWords(item); j++)
    {
        printf("\t[%d]%s\n", j, aux[j]);
    }
    printf("\n");
}

// GETTERS

int item_get_id(ITEM *item)
{
    if (item != NULL)
        return (item->id);

    printf("\nERROR: item_get_chave()\n");
    return ERROR;
}

char *item_get_name(ITEM *item)
{
    if (item != NULL)
        return (item->name);

    printf("\nERROR: item_get_name()\n");
    return NULL;
}

int item_get_relevance(ITEM *item)
{
    if (item != NULL)
        return item->relevance;

    printf("\nERROR: item_get_relevance()\n");
    return ERROR;
}

char *item_get_mainUrl(ITEM *item)
{
    if (item != NULL)
        return item->mainUrl;

    printf("\nERROR: item_get_mainUrl()\n");
    return NULL;
}

int item_get_numKeyWords(ITEM *item)
{
    if (item != NULL)
        return item->numKeyWords;

    printf("\nERROR: item_get_numKeyWords()\n");
    return ERROR;
}

char **item_get_keyWords(ITEM *item)
{
    if (item != NULL)
        return item->keyWords;

    printf("\nERROR: item_get_keyWords()\n");
    return NULL;
}

// SETTERS

boolean item_set_id(ITEM *item, int id)
{
    if (id < 0)
    {
        printf("ID cannot be negative!");
        return FALSE;
    }

    if (item != NULL)
    {
        // we use (*item) to force the system to first analyse the item content (pointer) before the -> operator
        (item)->id = id;

        return TRUE;
    }
    return FALSE;
}

boolean item_set_name(ITEM *item, char *name)
{
    if ((item) != NULL)
    {
        strcpy((item)->name, name);
        return TRUE;
    }
    return FALSE;
}

boolean item_set_relevance(ITEM *item, int rel)
{
    if (rel < 0 || rel > 1000)
    {
        printf("0-1000 is the range for relevance!");
        return FALSE;
    }

    if ((item) != NULL)
    {
        (item)->relevance = rel;
        return TRUE;
    }
    return FALSE;
}

boolean item_set_mainUrl(ITEM *item, char *url)
{
    if (url == NULL || strlen(url) > 100)
    {
        printf("50 characters max per keyword!\n");
        return FALSE;
    }

    strcpy((item)->mainUrl, url);
    return TRUE;
}

boolean item_set_numKeyWords(ITEM *item, int num)
{
    if (num < 0 || num > 10)
    {
        printf("10 is the max number for keywords!");
        return FALSE;
    }

    (item)->numKeyWords = num;
    return TRUE;
}

boolean item_set_keyWords(ITEM *item, char *word)
{
    // initializing the field
    if (word == NULL)
    {
        item->keyWords = NULL;
        return FALSE;
    }

    // max 50carac na keyword
    if (strlen(word) > 50)
    {
        printf("50 characters max per keyword!\n");
        return FALSE;
    }

    // Sets the limit of 10 keywords max
    if ((item) != NULL && (item)->numKeyWords < 10)
    {
        strcpy((item)->keyWords[(item)->numKeyWords-1], word);
        (item)->numKeyWords++;
        return TRUE;
    }
    return FALSE;
}