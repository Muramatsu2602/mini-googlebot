/*
    This is our interface (visible to the user) where we define the functions of our ADT
*/
#ifndef ITEM_H
    #define ITEM_H

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    #define ERROR 32000

    typedef struct item_ ITEM;

    // defining all operations related to the ITEM_H
    ITEM *item_criar(char *string);
    boolean item_apagar ( ITEM ** item); // alteracao da variavel (por referencia)
    void item_imprimir(ITEM * item);
    
    // GETTERS AND SETTERS
    int item_get_id(ITEM *item); // (ITEM *) (*item)
    boolean item_set_id(ITEM **item, int id); // (ITEM *) (*item)
    int item_get_keyWord(ITEM *item);
    boolean item_set_keyWord(ITEM **item,char *word);
    int item_get_relevance(ITEM *item);
    boolean item_set_relevance(ITEM **item, int rel);


#endif

