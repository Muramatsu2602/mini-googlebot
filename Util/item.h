/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/
#ifndef ITEM_H
#define ITEM_H

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    #define ERROR 32000

    typedef struct item_ ITEM;

    // CRIAR ITEM A PARTIR DO TECLADO
    ITEM *item_criar(void);

    // CRIAR ITEM A PARTIR DE STRING EM CSV
    ITEM *item_criar_CSV(char *string);
    boolean item_set_CSV(char *string, ITEM *item); // Insere Istring;

    boolean item_apagar(ITEM **item);                 
    void item_imprimir(ITEM *item);

    // GETTERS
    int item_get_id(ITEM *item);
    char *item_get_name(ITEM *item);
    int item_get_relevance(ITEM *item);
    char *item_get_mainUrl(ITEM *item);
    int item_get_numKeyWords(ITEM *item);
    char **item_get_keyWords(ITEM *item);

    // SETTERS
    boolean item_set_id(ITEM *item, int id);
    boolean item_set_name(ITEM *item, char *name);
    boolean item_set_relevance(ITEM *item, int rel);
    boolean item_set_mainUrl(ITEM *item, char *url);
    boolean item_set_numKeyWords(ITEM *item, int num);
    boolean item_set_keyWords(ITEM *item, char *word);

#endif
