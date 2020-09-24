#include <stdio.h>
#include <stdlib.h>

#include "item.h"

// REMEMBER ME: typedef struct item_ ITEM;

struct item_
{
    char caractere;
    /*Outros componentes*/
};

ITEM *item_criar(char c)
{
    ITEM *item;

    item = (ITEM *)malloc(sizeof(ITEM));

    if (item != NULL)
        item->caractere = c;

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
        printf("\n --> item: %c", item->caractere);
    }
}

char item_get_caractere(ITEM *item)
{
    if (item != NULL)
        return (item->caractere);
    else
    {
        printf("\nERROR: item_get_caractere()\n");
        exit(1); // ERROR: abort it! , there's not such int such that we can use it exclusively to represent an error (id is all INT)
                 // exit(0) --> 0 means regular exit
    }
}

boolean item_set_caractere(ITEM **item, char caractere)
{
    if (*item != NULL)
    {
        // we use (*item) to force the system to first analyse the item content (pointer) before the -> operator
        (*item)->caractere = caractere;
        
        return TRUE;
    }
    return FALSE;
}