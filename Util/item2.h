/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#ifndef ITEM2_H
#define ITEM2_H

    #include "dll.h"

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    #define ERROR 32000

    typedef struct item2_ ITEM2;

    ITEM2 *item2_criar(void);
    void insertionSort2(NO **nos, int qtd);
    boolean item2_apagar(ITEM2 **item);
    void item2_imprimir(ITEM2 *item);
    void item2_ordenar_nos(NO **nos, int qtd);

    // Adiciona um novo nó na lista de nós de ITEM2
    boolean item2_add_no(ITEM2 *item, NO *no);

    // GET e SET
    char *item2_get_keyWord(ITEM2 *item);
    int item2_get_qtd_nos(ITEM2 *item);
    void item2_set_qtd_nos(ITEM2*item, int qnd);
    NO **item2_get_nos(ITEM2 *item);
    void item2_set_keyWord(ITEM2 *item, char *word);

    // Função para remover referências de NÓS removidos da lista de nós no ITEM2
    void item2_remover_no_lista(ITEM2 *item, NO *noAtual);

#endif
