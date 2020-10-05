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

ITEM *item_criar(int id, char *name, int rel, char *mainUrl, int numKeyWords, char *keyWord)
{
    ITEM *item;

    item = (ITEM *)malloc(sizeof(ITEM));

    if (item != NULL)
        /* Setar o ID, nome, relevancia, link */
        item->numKeyWords = 0;


    // it will return NULL if alocation doesnt work
    return (item);
}

boolean item_apagar(ITEM **item) // pointer to a pointer
{
    // we can only erase existing items
    if (*item != NULL)
    {
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
    if (item != NULL)
    {
        printf("\n --> item: %d", item->id);
    }
}

int item_get_id(ITEM *item)
{
    if (item != NULL)
        return (item->id);
    else
    {
        printf("\nERROR: item_get_id()\n");
        exit(1); // ERROR: abort it! , there's not such int such that we can use it exclusively to represent an error (id is all INT)
                 // exit(0) --> 0 means regular exit
    }
}

boolean item_set_id(ITEM **item, int id)
{
    if (*item != NULL)
    {
        // we use (*item) to force the system to first analyse the item content (pointer) before the -> operator
        (*item)->id = id;
        
        return TRUE;
    }
    return FALSE;
}

// Permite a inserção de novas palavras-chave
boolean item_set_keyWord(ITEM **item,char *word)
{
    // Controla o limite de 10 palavras-chave
    if((*item) != NULL && (*item)->numKeyWords < 10)
    {
        strcpy(word,(*item)->keyWord[(*item)->numKeyWords]); // FIX ME!
        return TRUE;
    }
    return FALSE;
}

boolean item_set_relevance(ITEM **item, int rel)
{
    if((*item) != NULL)
    {
        (*item)->relevance = rel;
        return TRUE;
    }
    return FALSE;
}

int item_get_relevance(ITEM *item)
{
    if(item != NULL)
    {
        return item->relevance;
    }
    return ERROR; 
}