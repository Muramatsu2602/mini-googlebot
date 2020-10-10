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
    char *string = NULL;
    char *aux = NULL;
    printf("Digite o código do site a ser inserido: ");
    int cod;
    scanf("%d",&cod);
    getchar(); // Consome o \n do scanf anterior
    printf("Digitou: %d\n",cod);

    if(lista_busca(lista, cod) != NULL)
    {
        printf("Um site com este ID já existe!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    string = (char *) malloc((sizeof(int)+1)*sizeof(char));
    sprintf(string, "%d", cod);

    printf("Digite o nome do Site: ");
    aux = readline(stdin);

    if(strlen(aux) > 50)
    {
        printf("O nome do Site deve conter até 50 caracteres!\n\nPressione qualquer botão para continuar...");
        getchar();
        free(aux);
        aux = NULL;
        free(string);
        string = NULL;
        return;
    }

    string = (char *) realloc(string,(strlen(string)+strlen(aux)+2)*sizeof(char));
    strcat(string,",");
    strcat(string, aux);
    free(aux);
    aux = NULL;

    printf("Digite o valor da relevância do site: ");
    aux = readline(stdin);

    if(atoi(aux) < 0 || atoi(aux) > 1000)
    {
        printf("O valor deve ser entre 0 e 1000!\n\nPressione qualquer botão para continuar...");
        getchar();
        free(aux);
        aux = NULL;
        free(string);
        string = NULL;
        return;
    }

    string = (char *) realloc(string,(strlen(string)+strlen(aux)+2)*sizeof(char));
    strcat(string,",");
    strcat(string, aux);
    free(aux);
    aux = NULL;

    printf("Digite a URL do Site: ");
    aux = readline(stdin);

    if(strlen(aux) > 100)
    {
        printf("A URL do site pode conter até 100 caracteres!\n\nPressione qualquer botão para continuar...");
        getchar();
        free(aux);
        aux = NULL;
        free(string);
        string = NULL;
        return;
    }

    string = (char *) realloc(string,(strlen(string)+strlen(aux)+2)*sizeof(char));
    strcat(string,",");
    strcat(string, aux);
    free(aux);
    aux = NULL;

    int num;
    printf("Digite o número de palavars-chaves que deseja adicioanar: ");
    scanf("%d",&num);
    getchar(); // Consome o \n do scanf

    if(num < 0 || num > 10)
    {
        printf("O número de palavras chave deve ser de 0 a 10!\n\nPressione qualquer botão para continuar...");
        getchar();
        free(string);
        string = NULL;
        return;
    }

    for(int i=0;i<num;i++)
    {
        printf("Digite a %d palavra-chave: ",i+1);
        aux = readline(stdin);

        if(strlen(aux) > 50)
        {
            printf("A palavra-chave pode conter até 100 caracteres!\n\nPressione qualquer botão para continuar...");
            getchar();
            free(aux);
            aux = NULL;
            free(string);
            string = NULL;
            return;
        }   

        string = (char *) realloc(string,(strlen(string)+strlen(aux)+2)*sizeof(char));
        strcat(string,",");
        strcat(string, aux);
        free(aux);
        aux = NULL;
    }

    if(!lista_inserir_fim(lista, item_criar(string)))
    {
        free(string);
        printf("Erro ao inserir novo Site!!\n\n");
    }

    printf("Novo site de id: %d inserido com sucesso!\n\nPressione qualquer botão para continuar...",cod);
    getchar();
    free(string);
}

void removerSite(LISTA *lista)
{
    int id;
    printf("Digite o código do site que deseja remover: ");
    scanf("%d",&id);
    getchar();

    if(lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    if(lista_remover(lista, id))
    {
        printf("Site removido com sucesso!\n\nPressione qualquer botão para continuar...");
        getchar();
    }
    else
    {
        printf("Erro ao remover Site!\n\nPressione qualquer botão para continuar...");
        getchar();
    }

}

void inserirPalavraChave(LISTA *lista)
{
    int id;
    char *string;
    printf("Digite o código do site que deseja inserir: ");
    scanf("%d",&id);
    getchar();

    if(lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    printf("Digite a palavra-chave a ser adicionada: ");
    string = readline(stdin);

    if(strlen(string) > 50)
    {
        printf("A palavra-chave excede o limite de 50 caracteres!\n\nPressione qualquer botão para continuar...");
        getchar();
        free(string);
        return;
    }

    if(item_set_keyWords(lista_busca(lista, id), string)) 
    {
        printf("Palavra-Chave adicionada com sucesso!\n\nPressione qualquer botão para continuar...");
        getchar();
    }
    else
    {
        printf("Erro ao inserir nova Palavra-Chave!\n\nPressione qualquer botão para continuar...");
        getchar();
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
        printf("Site não encontrado na lista!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    printf("Alterando a relevancia do Site de id: %d\n\n",id);
    printf("Digite o novo valor de relevancia: ");
    scanf("%d",&relevancia);
    getchar();
    printf("\n");

    if(item_set_relevance(lista_busca(lista, id), relevancia))
    {
        printf("Relevancia atualizada com sucesso!\n\nPressione qualquer botão para continuar...");
        getchar();
    }
    else
    {
        printf("Erro ao atualizar relevancia!\n\nPressione qualquer botão para continuar...");
        getchar();
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
        if(!lista_inserir_ordenado(lista, item_criar(string)))
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
    while(opcao != 6)
    {
        system("clear");
        printf("\nOpções:\n");
        printf("1 - Inserir um site;\n");
        printf("2 - Remover um site;\n");
        printf("3 - Inserir Palavra-Chave um site;\n");
        printf("4 - Atualizar relevância um site;\n");
        printf("5 - Imprimir a lista de Sites;\n");
        printf("6 - Sair.\n");
        
        printf("Insira a Opção: ");
        scanf("%d",&opcao);
        system("clear");

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
                lista_imprimir(lista);
                printf("\n\nPressione qualquer botão para continuar...");
                getchar();
                getchar();
                break;

            case 6:
                system("clear");
                break;
        }
    }
    
    lista_apagar(&lista);
    fclose(fp);
    return 0;
}
