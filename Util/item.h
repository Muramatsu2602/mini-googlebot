/*
    This is our interface (visible to the user) where we define the functions of our ADT
*/
#ifndef ITEM_H
    #define ITEM_H

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    typedef struct item_ ITEM;

    // defining all operations related to the ITEM_H
    ITEM * item_criar(int chave);
    boolean item_apagar ( ITEM ** item); // alteracao da variavel (por referencia)
    void item_imprimir(ITEM * item);
    
    // GETTERS AND SETTERS
    int item_get_chave(ITEM *); // (ITEM *) (*item)
    int item_set_chave(ITEM ** item, int chave); // (ITEM *) (*item)


#endif

