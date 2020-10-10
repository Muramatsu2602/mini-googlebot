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

void inserirSite(LISTA *lista)
{
    char *string;
    /*char *aux;
    printf("Digite o código do site a ser inserido: ");
    aux = readline(stdin);

    if(lista_busca(lista, atoi(aux)) != NULL)
    {
        printf("Um site com este ID já existe!!\n");
        return;
    }

    string = (char *) malloc(strlen(aux)*sizeof(char));*/

    printf("Estrutura de inserção de site:\n");
    printf("Todos os campos são separados por vírgula sem espaço entre eles! Máximo de 10 palavras-chave");
    printf("<Código>,<Nome do Site>,<URL>,<palavra-chave 1>,<palavra-chave 2>,<palavra-chave n>\n\n");

    printf("Digite a inserção do novo site conforme a estrutura: \n");
    getchar(); // Consome o \n do scanf anterior
    string = readline(stdin);

    lista_inserir_fim(lista,item_criar(string));
    free(string);
}

void removerSite(LISTA *lista)
{
    int id;
    printf("Digite o código do site que deseja remover: ");
    scanf("%d",&id);

    if(lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!");
        return;
    }

    if(lista_remover(lista, id))
    {
        printf("Site removido com sucesso!\n");
    }
    else
    {
        printf("Erro ao remover Site!\n");
    }

}

void inserirPalavraChave(LISTA *lista)
{
    int id;
    char *string;
    printf("Digite o código do site que deseja inserir: ");
    scanf("%d",&id);

    if(lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!");
        return;
    }

    printf("Digite a palavra-chave a ser adicionada: ");
    getchar(); // Consome o \n do scanf anterior
    string = readline(stdin);

    if(strlen(string) > 50)
    {
        printf("A palavra-chave excede o limite de 50 caracteres!\n");
        free(string);
        return;
    }

    if(item_set_keyWords(lista_busca(lista, id), string)) 
    {
        printf("Palavra-Chave adicionada com sucesso!\n");
    }
    else
    {
        printf("Erro ao inserir nova Palavra-Chave!\n");
    }
    free(string);
}

void atualizarRelevancia(LISTA *lista)
{
    int id;
    int relevancia;
    printf("Digite o código do site que deseja atualizar a relevancia: ");
    scanf("%d",&id);

    if(lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!");
        return;
    }

    printf("Alterando a relevancia do Site de id: %d\n\n",id);
    printf("Digite o novo valor de relevancia: ");
    scanf("%d",&relevancia);
    printf("\n");

    /*if(relevancia < 0 || relevancia > 1000)
    {
        printf("Valor de relevância inválido!");
        return;
    }*/

    if(item_set_relevance(lista_busca(lista, id), relevancia))
    {
        printf("Relevancia atualizada com sucesso!\n");
    }
    else
    {
        printf("Erro ao atualizar relevancia!\n");
    }
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
        if(!lista_inserir_fim(lista, item_criar(string)))
        {
            printf("ERRO inserir lista!");
            return 0;
        }
        free(string);
        string = readline(fp);
    }
    free(string);

    // lista_imprimir(lista);

    int opcao = 0;
    while(opcao != 5)
    {
        printf("\n\nOpções:\n");
        printf("1 - Inserir um site;\n");
        printf("2 - Remover um site;\n");
        printf("3 - Inserir Palavra-Chave um site;\n");
        printf("4 - Atualizar relevância um site;\n");
        printf("5 - Sair.\n");
        
        printf("Insira a Opção: ");
        scanf("%d",&opcao);

        switch(opcao)
        {
            case 1:
                inserirSite(lista);
                break;

            case 2:
                removerSite(lista);
                break;

            case 3:
                inserirPalavraChave(lista);
                break;

            case 4:
                atualizarRelevancia(lista);
                break;

            case 5:
                return 0;
        }
    }
    
    lista_apagar(&lista);
    fclose(fp);
    return 0;
}
