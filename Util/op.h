/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#ifndef _OPERATION_H
#define _OPERATION_H

    #include "dll.h"
    #include "AVL.h"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define BUFFER 100
    
    char *readline(FILE *stream);

    boolean inserirSite(LISTA *lista, AVL *avl);
    void removerSite(LISTA *lista, AVL *avl);
    void inserirPalavraChave(LISTA *lista, AVL *avl);
    void atualizarRelevancia(LISTA *lista);
    void buscarPorKeyword(LISTA *lista, AVL *avl);
    void sugerirSites(LISTA *lista, AVL *avl);

#endif