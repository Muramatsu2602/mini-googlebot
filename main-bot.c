#include <stdio.h>
#include <stdlib.h>

#include "Util/list.h"

#define READLINE_BUFFER 16
// #include "Util/fileManager.h"

/*
    1. Inserir um site: a inserção deve ser ordenada pela chave primária, isto é, o código do
       site. O sistema não deve aceitar valores de código já existentes;
    2. Remover um site: dado um código, deve-se excluir o site. Caso um código inexistente
       seja inserido, uma mensagem deve ser printada ao usuário a respeito disso;
    3. Inserir palavra-chave: dado um código, pode-se adicionar uma nova palavra-chave.
    4. Atualizar relevância: dado um código, deve-se atualizar a relevância do site;
    5. Sair: finalizar o programa.
*/

boolean openReadFile(char *fileName, FILE *fp, char *mode)
{
    fp = fopen(fileName, mode);
    if (fp != NULL)
    {
        return TRUE;
    }

    return FALSE;
}

// You can read file lines using this function
char *readline(FILE *stream)
{
    char *string = NULL;
    int pont = 0;
    do
    {
        if (pont % READLINE_BUFFER == 0)
        {
            string = (char *)realloc(string, ((pont / READLINE_BUFFER) + 1) * READLINE_BUFFER);
        }
        string[pont] = (char)fgetc(stream);
    } while (string[pont++] != '\n' && !feof(stream));
    string[pont - 1] = '\0';
    return string;
}

int main(int argc, char const *argv[])
{
    char *string;
    LISTA *lista = lista_criar();

    FILE *fp;
    openReadFile("Data/googlebot.txt", fp, "r+");

    while(!feof(fp))
    {
        string = readline(fp);
        lista_inserir_ordenado(lista, item_criar(string));
    }

    // lista_apagar(list);
    // fclose(fp);
    return 0;
}
