/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util/dll.h"
#include "Util/AVL.h"

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

// Realiza a leitura das linhas do arquivo de entrada
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

boolean inserirSite(LISTA *lista, AVL *avl)
{

    NO *newsite = (NO *) malloc (sizeof(NO));
    char *text_aux = NULL;
    int aux = 0;

    // ID
    printf("Digite o código do site a ser inserido: ");
    scanf("%d", &aux);
    if (lista_busca_ordenada(lista, aux) != NULL)
    {
        printf("Codigo ja cadastrado!\n");
        return FALSE;
    }

    newsite->item = item_criar();

    if (!item_set_id(newsite->item, aux))
    {
        return FALSE;
    }

    // NOME
    printf("Digite o nome do Site: ");
    getchar(); // Consome o \n do scanf anterior
    text_aux = readline(stdin);
    if (!item_set_name(newsite->item, text_aux))
    {
        item_apagar(&newsite->item);
        free(text_aux);
        return FALSE;
    }
    free(text_aux);

    // RELEVANCIA
    printf("Digite o valor da relevância do site: ");
    scanf("%d", &aux);
    if (!item_set_relevance(newsite->item, aux))
    {
        item_apagar(&newsite->item);
        return FALSE;
    }

    // URL
    printf("Digite a URL do Site: ");
    getchar(); // Consome o \n do scanf anterior
    text_aux = readline(stdin);
    if (!item_set_mainUrl(newsite->item, text_aux))
    {
        free(text_aux);
        item_apagar(&newsite->item);
        return FALSE;
    }
    free(text_aux);

    // NUM_KEYWORDS
    printf("Digite o número de palavras-chave que deseja adicionar: ");
    scanf("%d", &aux);
    // o num_keywords ja eh incrementado automaticamente a medida que se executa item_set_keywords

    if(aux > 10 || aux < 0)
    {
        printf("O número de palavras chave deve variar entre 0 e 10!\n");
        item_apagar(&newsite->item);
        return FALSE;
    }

    // KEYWORDS
    item_set_keyWords(newsite->item, NULL);
    getchar(); // Consome o \n do scanf anterior
    for (int i = 0; i < aux; i++)
    {
        printf("Digite a %d palavra-chave: ", 1 + i);
        text_aux = readline(stdin);
        if (!item_set_keyWords(newsite->item, text_aux))
        {
            free(text_aux);
            item_apagar(&newsite->item);
            return FALSE;
        }
        free(text_aux);
    }

    // ERRO NA INSERCAO
    newsite = lista_inserir_ordenado(lista, newsite->item);
    if(newsite == NULL)
    {
        item_apagar(&newsite->item);
        return FALSE;
    }
    
    // Depois de inserir o item na lista, atualizar AVL de palavras-chave
    char **keys = item_get_keyWords(newsite->item);
    int qtd_keys = item_get_numKeyWords(newsite->item);
    ITEM2 *aux2 = NULL;
    ITEM2 *item_novo = NULL;

    for(int i=0; i<qtd_keys; i++)
    {
        aux2 = avl_busca(avl, keys[i]);
        if(aux2 != NULL)
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

    printf("Novo site de id: %d inserido com sucesso!\n\nPressione qualquer botão para continuar...", item_get_id(newsite->item));
    getchar();

    return TRUE;
}

void removerSite(LISTA *lista)
{
    int id;

    printf("Digite o código do site que deseja remover: ");
    scanf("%d", &id);
    getchar();

    if (lista_busca_ordenada(lista, id) == NULL)
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

void inserirPalavraChave(LISTA *lista, AVL *avl)
{
    int id;
    char *string;

    printf("Digite o código do site que deseja inserir: ");
    scanf("%d", &id);
    getchar();

    NO *noSite = lista_busca_ordenada(lista, id);
    if (noSite == NULL)
    {
        printf("Site não encontrado na lista!!\n\nPressione qualquer botão para continuar...");
        getchar();
        return;
    }

    printf("Digite a palavra-chave a ser adicionada: ");
    string = readline(stdin);

    // adicionando a nova palavra-chave
    if (!item_set_keyWords((lista_busca_ordenada(lista, id))->item, string))
        printf("Erro ao inserir nova Palavra-Chave!\n\nPressione qualquer botão para continuar...");
    else
        printf("Palavra-Chave adicionada com sucesso!\n\nPressione qualquer botão para continuar...");

    ITEM2 *aux2 = NULL;
    ITEM2 *item_novo = NULL;

    aux2 = avl_busca(avl, string);
    if(aux2 != NULL)
    {
        // Encontrou a palavra-chave na AVL, então inserir o pnovo na lista de nós que contém tal palavra chave
        item2_add_no(aux2, noSite);
    }
    else
    {
        item_novo = item2_criar();
        item2_set_keyWord(item_novo, string);
        item2_add_no(item_novo, noSite);
        avl_inserir(avl, item_novo);
        item_novo = NULL;
        // Não encontrou a palavra-chave na AVL, criar um novo nó nesta árvore
    }
    getchar();
    free(string);
}

void atualizarRelevancia(LISTA *lista)
{
    int id;
    int relevancia;

    printf("Digite o código do site que deseja atualizar a relevancia: ");
    scanf("%d", &id);

    if (lista_busca_ordenada(lista, id) == NULL)
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

    // Atualizando relevância do site
    if (!item_set_relevance((lista_busca_ordenada(lista, id))->item, relevancia))
        printf("Erro ao atualizar relevancia!\n\nPressione qualquer botão para continuar...");
    else
        printf("Relevancia atualizada com sucesso!\n\nPressione qualquer botão para continuar...");
    getchar();
}

void buscarPorKeyword(LISTA *lista)
{
    char *keyword = NULL;
    LISTA *key_lista = NULL;
    key_lista = lista_criar();

    printf("insira a palavra-chave desejada: ");
    getchar();

    keyword = readline(stdin);

    // armazena em key_lista sites que contem a keyword
    lista_busca_keyword(lista, key_lista, keyword);
    lista_imprimir_short(key_lista, 0);

    free(keyword);
    lista_apagar(&key_lista);

    printf("\n\nPressione qualquer botão para continuar...");
    getchar();
}

void sugerirSites(LISTA *lista)
{
    char *keyword = NULL;
    LISTA *key_lista = NULL;
    key_lista = lista_criar();

    printf("insira a palavra-chave desejada: ");
    getchar();

    keyword = readline(stdin);

    // Buscas a palavra fornecida entre as palavras-chave de cada site
    lista_busca_keyword(lista, key_lista, keyword);

    // Função que executa os próximos passos do sugerirSites no arquivo dll.c
    // Está no arquivo dll.c pois a função necessita do acesso aos ponteiros lista->inicio e no->proximo
    lista_sugerir_sites(lista, key_lista);

    free(keyword);
    lista_apagar(&key_lista);

    printf("\n\nPressione qualquer botão para continuar...");
    getchar();
}

int main(void)
{
    char *string = NULL;
    LISTA *lista = NULL;
    FILE *fp = NULL;
    int opcao = 0;

    lista = lista_criar();
    fp = openReadFile("Data/googlebot.txt", fp, "r+");

    // Árvore AVL utilizada para busca de KeyWords e sugestão de sites
    AVL *avl = NULL;
    avl = avl_criar();

    // Leitura do arquivo de entrada
    string = readline(fp);
    NO *newsite = NULL;
    while (!feof(fp))
    {
        newsite = lista_inserir_ordenado(lista, item_criar_CSV(string));
        if (newsite == NULL)
        {
            printf("ERRO inserir lista!");
            return 0;
        }
        // Depois de inserir o item na lista, atualizar AVL de palavras-chave
        char **keys = item_get_keyWords(newsite->item);
        int qtd_keys = item_get_numKeyWords(newsite->item);
        ITEM2 *aux2 = NULL;
        ITEM2 *item_novo = NULL;

        for(int i=0; i<qtd_keys; i++)
        {
            aux2 = avl_busca(avl, keys[i]);
            if(aux2 != NULL)
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

    avl_printa_arvore(avl);

    while (opcao != 8)
    {
        system("clear");
        printf("\nOpções:\n");
        printf("1 - Inserir um site;\n");
        printf("2 - Remover um site;\n");
        printf("3 - Inserir Palavra-Chave um site;\n");
        printf("4 - Atualizar relevância um site;\n");
        printf("5 - Imprimir a lista de Sites;\n");
        printf("6 - Buscar sites por Palavra-chave;\n");
        printf("7 - Sugestão de sites;\n");
        printf("8 - Sair.\n");
        printf("Insira a Opção: ");

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
                removerSite(lista);
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
                sugerirSites(lista);
                break;
            case 8:
                system("clear");
                break;
        }
    }

    free(string);
    lista_apagar(&lista);
    avl_apagar_arvore(&avl);
    fclose(fp);
    return 0;
}