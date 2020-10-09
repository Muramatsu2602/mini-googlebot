#include <stdio.h>
#include <stdlib.h>

#include "Util/list.h"
#include "Util/fileManager.h"

/*
    1. Inserir um site: a inserção deve ser ordenada pela chave primária, isto é, o código do
       site. O sistema não deve aceitar valores de código já existentes;
    2. Remover um site: dado um código, deve-se excluir o site. Caso um código inexistente
       seja inserido, uma mensagem deve ser printada ao usuário a respeito disso;
    3. Inserir palavra-chave: dado um código, pode-se adicionar uma nova palavra-chave.
    4. Atualizar relevância: dado um código, deve-se atualizar a relevância do site;
    5. Sair: finalizar o programa.
*/

int main(int argc, char const *argv[])
{
    LISTA * list;
    FILE * fp;



    // lista_apagar(list);
    // fclose(fp);
    return 0;
}
