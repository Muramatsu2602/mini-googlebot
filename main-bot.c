#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util/list.h"

#define BUFFER 100

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
        if (pont % BUFFER == 0) // Se o ponteiro for divisivel pelo buffer ou é 0 é preciso alocar mais memória HEAP para receber a string
        {
            string = (char *)realloc(string, ((pont / BUFFER) + 1) * BUFFER);
        }
        string[pont] = (char)fgetc(stream);                                    // Recebe um dos caracteres da string
    } while (string[pont] != '\n' && string[pont++] != '\t' && !feof(stream)); // A condição de parada é achar o \n ou encontrar o marcador de fim de arquivo
    string[pont] = '\0';                                                       // Insere o terminador de string
    return string;
}

boolean inserirSite(LISTA *lista)
{
    ITEM *newsite = NULL;
    char *text_aux = malloc(sizeof(char) * BUFFER);
    int aux = 0;
    int n;

    newsite = item_criar();

    printf("Digite o código do site a ser inserido: ");
    scanf("%d", &aux);
    if (lista_busca(lista, aux) != NULL)
    {
        printf("Codigo ja cadastrado!\n");
        getchar();
        return FALSE;
    }
    if (!item_set_id(newsite, aux))
        return FALSE;

    printf("Digite o nome do Site: ");
    scanf("%s", text_aux);
    if (!item_set_name(newsite, text_aux))
    {
        free(text_aux);
        return FALSE;
    }

    printf("Digite o valor da relevância do site: ");
    scanf("%d", &aux);
    if (!item_set_relevance(newsite, aux))
        return FALSE;

    printf("Digite a URL do Site: ");
    scanf("%s", text_aux);
    if (!item_set_mainUrl(newsite, text_aux))
    {
        free(text_aux);
        return FALSE;
    }

    printf("Digite o número de palavras-chave que deseja adicionar: ");
    scanf("%d", &aux);

    item_set_keyWords(newsite, NULL);
    for (int i = 0; i < aux; i++)
    {
        printf("Digite a %d palavra-chave: ", 1 + i);
        scanf("%s", text_aux);
        if (!item_set_keyWords(newsite, text_aux))
        {
            free(text_aux);
            return FALSE;
        }
    }

    if (!lista_inserir_ordenado(lista, newsite))
    {
        free(text_aux);
        return FALSE;
    }

    printf("Novo site de id: %d inserido com sucesso!\n\nPressione qualquer botão para continuar...", item_get_id(newsite));
    getchar();
    getchar();

    return TRUE;
}

void removerSite(LISTA *lista)
{
    int id;

    printf("Digite o código do site que deseja remover: ");
    scanf("%d", &id);
    getchar();

    if (lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    if (lista_remover(lista, id))
        printf("Site removido com sucesso!\n\nPressione qualquer botão para continuar...");
    else
        printf("Erro ao remover Site!\n\nPressione qualquer botão para continuar...");

    getchar();
}

void inserirPalavraChave(LISTA *lista)
{
    int id;
    char *string;

    printf("Digite o código do site que deseja inserir: ");
    scanf("%d", &id);
    getchar();

    if (lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    printf("Digite a palavra-chave a ser adicionada: ");
    string = readline(stdin);

    // Adding new Keyword
    if (!item_set_keyWords(lista_busca(lista, id), string))
        printf("Erro ao inserir nova Palavra-Chave!\n\nPressione qualquer botão para continuar...");
    else
        printf("Palavra-Chave adicionada com sucesso!\n\nPressione qualquer botão para continuar...");

    getchar();
    free(string);
}

void atualizarRelevancia(LISTA *lista)
{
    int id;
    int relevancia;

    printf("Digite o código do site que deseja atualizar a relevancia: ");
    scanf("%d", &id);

    if (lista_busca(lista, id) == NULL)
    {
        printf("Site não encontrado na lista!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    printf("Alterando a relevancia do Site de id: %d\n\n", id);
    printf("Digite o novo valor de relevancia: ");
    scanf("%d", &relevancia);
    getchar();
    printf("\n");

    // Updating Relevance
    if (!item_set_relevance(lista_busca(lista, id), relevancia))
        printf("Erro ao atualizar relevancia!\n\nPressione qualquer botão para continuar...");
    else
        printf("Relevancia atualizada com sucesso!\n\nPressione qualquer botão para continuar...");
    getchar();
}

int main(int argc, char const *argv[])
{
    char *string = NULL;
    LISTA *lista = NULL;
    FILE *fp = NULL;
    int opcao = 0;

    lista = lista_criar();
    fp = openReadFile("Data/googlebot.txt", fp, "r+");

    // Reading text from file
    string = readline(fp);
    while (!feof(fp))
    {
        if (!lista_inserir_ordenado(lista, item_criar_CSV(string)))
        {
            printf("ERRO inserir lista!");
            return 0;
        }
        free(string);
        string = readline(fp);
    }

    while (opcao != 6)
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
        scanf("%d", &opcao);
        system("clear");

        switch (opcao)
        {
            case 1:
                if (!inserirSite(lista))
                {
                    printf("Erro ao inserir Site via teclado!\n\n\nPressione qualquer botão para continuar...");
                    getchar();
                    getchar();
                }
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

    free(string);
    lista_apagar(&lista);
    fclose(fp);
    return 0;
}