#include <stdio.h>
#include <stdlib.h>

#include "item.h"

// REMEMBER ME: typedef struct item_ ITEM;

struct item_
{
    int chave;
    /*Outros componentes*/
};

ITEM *item_criar(int key)
{
    ITEM *item;

    item = (ITEM *)malloc(sizeof(ITEM));

    if (item != NULL)
        item->chave = key;

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
        printf("\n --> item: %d", item->chave);
    }
}

int item_get_chave(ITEM *item)
{
    if (item != NULL)
        return (item->chave);
    else
    {
        printf("\nERROR: item_get_chave()\n");
        exit(1); // ERROR: abort it! , there's not such int such that we can use it exclusively to represent an error (id is all INT)
                 // exit(0) --> 0 means regular exit
    }
}

boolean item_set_chave(ITEM **item, int chave)
{
    if (*item != NULL)
    {
        // we use (*item) to force the system to first analyse the item content (pointer) before the -> operator
        (*item)->chave = chave;
        
        return TRUE;
    }
    return FALSE;
}