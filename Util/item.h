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
    
    // GETTERS
    int item_get_id(ITEM *item); 
    char * item_get_name(ITEM * item);
    int item_get_relevance(ITEM *item);
    char * item_get_mainUrl(ITEM *item);
    int item_get_numKeyWords(ITEM *item);
    char ** item_get_keyWords(ITEM *item);

    // SETTERS
    boolean item_set_id(ITEM *item, int id);
    boolean item_set_name(ITEM *item, char *name);
    boolean item_set_relevance(ITEM *item, int rel);
    boolean item_set_mainUrl(ITEM *item, char *url);
    boolean item_set_numKeyWords(ITEM *item, int num);
    boolean item_set_keyWords(ITEM *item, char *word);
#endif

