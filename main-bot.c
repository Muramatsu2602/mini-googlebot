/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util/op.h"

#pragma region Func Auxiares

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

void csv_read(char *string, FILE *fp, LISTA *lista, AVL *avl)
{
    // Leitura do arquivo de entrada
    string = readline(fp);
    NO *newsite = NULL;
    while (!feof(fp))
    {
        newsite = lista_inserir_ordenado(lista, item_criar_CSV(string));
        if (newsite == NULL)
        {
            printf("ERRO inserir lista!");
            exit(ERROR);
        }
        // Depois de inserir o item na lista, atualizar AVL de palavras-chave
        char **keys = item_get_keyWords(newsite->item);
        int qtd_keys = item_get_numKeyWords(newsite->item);
        ITEM2 *aux2 = NULL;
        ITEM2 *item_novo = NULL;

        for (int i = 0; i < qtd_keys; i++)
        {
            aux2 = avl_busca(avl, keys[i]);
            if (aux2 != NULL)
            {
                // Encontrou a palavra-chave na AVL, então inserir o pnovo na lista de nós que contém tal palavra chave
                item2_add_no(aux2, newsite);
            }
            else
            {
                item_novo = item2_criar();
                item2_set_keyWord(item_novo, keys[i]);
                item2_add_no(item_novo, newsite);
                avl_inserir(avl, item_novo);
                item_novo = NULL;
                // Não encontrou a palavra-chave na AVL, criar um novo nó nesta árvore
            }
        }
        free(string);
        string = readline(fp);
    }
}

void print_menu()
{
    printf("\nOpções:\n");
    printf("1 - Inserir um site;\n");
    printf("2 - Remover um site;\n");
    printf("3 - Inserir Palavra-Chave um site;\n");
    printf("4 - Atualizar relevância um site;\n");
    printf("5 - Imprimir a lista de Sites;\n");
    printf("6 - Buscar sites por Palavra-chave;\n");
    printf("7 - Sugestão de sites;\n");
    printf("8 - Mostrar árvore AVL de palavras-chave;\n");
    printf("9 - Sair.\n");
    printf("Insira a Opção: ");
}

#pragma endregion 

int main(void)
{
    char *string = NULL;
    LISTA *lista = NULL;
    AVL *avl = NULL;
    FILE *fp = NULL;
    int opcao = 0;

    // criando a lista para armazenar os websites e efetuar as ops da parte I
    lista = lista_criar();
    fp = openReadFile("Data/googlebot.txt", fp, "r+");

    // Árvore AVL utilizada para busca de KeyWords e sugestão de sites
    avl = avl_criar();

    // Processando o .csv e preenchendo os respectivos TADs
    csv_read(string, fp, lista, avl);

    // MENU PRINCIPAL
    while (opcao != 9)
    {
        system("clear");
        print_menu();
        scanf("%d", &opcao);
        system("clear");

        switch (opcao)
        {
            case 1:
                if (!inserirSite(lista, avl))
                {
                    printf("Erro ao inserir Site via teclado!\n\n\nPressione qualquer botão para continuar...");
                    getchar();
                    getchar();
                }
                break;

            case 2:
                removerSite(lista, avl);
                break;

            case 3:
                inserirPalavraChave(lista, avl);
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
                buscarPorKeyword(lista, avl);
                break;

            case 7:
                sugerirSites(lista, avl);
                break;

            case 8:
                avl_printa_arvore(avl);
                printf("\n\nPressione qualquer botão para continuar...");
                getchar();
                getchar();
                break;
                
            case 9:
                system("clear");
                break;
        }
    }

    // LIBERANDO A MEM HEAP!
    free(string);
    lista_apagar(&lista);
    avl_apagar_arvore(&avl);
    fclose(fp);
    return 0;
}