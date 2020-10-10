#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

FILE *openReadFile(char *fileName, FILE *fp, char *mode)
{
    fp = fopen(fileName, mode);
    if (fp == NULL)
    {
        printf("ERRO NA ABERTURA DO ARQUIVO");
        return NULL;
    }

    return fp;
}

// You can read file lines using this function
char *readline(FILE *stream)
{
    char *string = NULL;
    int pont = 0;
    do
    {
        if (pont % READLINE_BUFFER == 0) // Se o ponteiro for divisivel pelo buffer ou é 0 é preciso alocar mais memória HEAP para receber a string
        {
            string = (char *)realloc(string, ((pont / READLINE_BUFFER) + 1) * READLINE_BUFFER);
        }
        string[pont] = (char)fgetc(stream);                                    // Recebe um dos caracteres da string
    } while (string[pont] != '\n' && string[pont++] != '\t' && !feof(stream)); // A condição de parada é achar o \n ou encontrar o marcador de fim de arquivo
    string[pont - 1] = '\0';                                                   // Insere o terminador de string
    return string;
}

int main(int argc, char const *argv[])
{
    char *string = NULL;
    LISTA *lista = NULL;
    FILE *fp = NULL;

    lista = lista_criar();
    fp = openReadFile("Data/googlebot.txt", fp, "r+");

    // Reading text from file
    string = readline(fp);
    while (!feof(fp))
    {
        lista_inserir_ordenado(lista, item_criar(string));
        free(string);
        string = readline(fp);
    }

    free(string);
    lista_apagar(&lista);
    fclose(fp);
    return 0;
}
