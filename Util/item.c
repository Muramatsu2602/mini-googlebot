/*
    11796444 - Giovanni Shibaki Camargo
    11796451 - Pedro Kenzo Muramatsu Carmo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

// REMEMBER ME: typedef struct item_ ITEM;

struct item_ // Cada item representa um site
{
    int id;
    char name[50];
    int relevance;
    char mainUrl[100];
    int numKeyWords; // Limite = 10 palavras-chave 
    char **keyWords; //  Limite = 50 caracteres por palavra
};

ITEM *item_criar(void)
{
    ITEM *item;

    item = (ITEM *)malloc(sizeof(ITEM));

    if (item == NULL)
    {
        printf("Erro ao alocar ITEM!\n");
        return NULL;
    }

    return (item);
}

// formata string recebida e preenche um item
boolean item_set_CSV(char *string, ITEM *item)
{
    char *ptr = NULL;
    item_set_keyWords(item, NULL);
    item_set_numKeyWords(item, 0);

    // 1 - Código
    ptr = strtok(string, ",");
    if (ptr == NULL)
    {
        printf("STRTOK1!\n");
        return FALSE;
    }
    item_set_id(item, atoi(ptr));

    // 2 - Nome
    ptr = strtok(NULL, ",");
    if (ptr == NULL)
    {
        printf("STRTOK2!\n");
        return FALSE;
    }
    item_set_name(item, ptr);

    // 3 - Relevancia
    ptr = strtok(NULL, ",");
    if (ptr == NULL)
    {
        printf("STRTOK3!\n");
        return FALSE;
    }
    item_set_relevance(item, atoi(ptr));

    // 4 - URL
    ptr = strtok(NULL, ",");
    if (ptr == NULL)
    {
        printf("STRTOK4!\n");
        return FALSE;
    }
    item_set_mainUrl(item, ptr);

    // 5 - Palavras-Chave
    // Ler as palavras chave até que strtok retorne NULO
    ptr = strtok(NULL, ",");
    while (ptr != NULL && item->numKeyWords <= 10)
    {
        item->numKeyWords++;

        item->keyWords = (char **)realloc(item->keyWords, item->numKeyWords * sizeof(char *));
        item->keyWords[item->numKeyWords - 1] = (char *)malloc((1 + strlen(ptr)) * sizeof(char));
        strcpy(item->keyWords[item->numKeyWords - 1], ptr);

        ptr = strtok(NULL, ",");
    }
    return TRUE;
}

// cria item a partir de string em formato CSV
ITEM *item_criar_CSV(char *string)
{
    ITEM *item;

    item = (ITEM *)malloc(sizeof(ITEM));

    if (item != NULL)
    {
        /* Setar o ID, nome, relevancia, link */
        if (!item_set_CSV(string, item))
        {
            printf("ERRO ITEM_INSERIR_DADOS!");
            return NULL;
        }
    }

    // Retorna NULL se a alocação não for bem sucedida
    return (item);
}

boolean item_apagar(ITEM **item) // Ponteiro de ponteiro
{
    // Verifica se o item enviado existe
    if ((*item) != NULL)
    {
        for (int i = 0; i < (*item)->numKeyWords; i++)
            free((*item)->keyWords[i]);

        free((*item)->keyWords);
        (*item)->keyWords = NULL;

        free(*item);
        *item = NULL; /*
                            Quando é feito o free() a variavel continua existindo, terá o valor NULL
                            Este é o motivo de enviar um ponteiro duplo do item para a função, pois assim este valor pode ser também alterado (por referencia)
                            É uma precaução extra
                    */
        return (TRUE);
    }
    return (FALSE);
}

void item_imprimir(ITEM *item)
{
    char **aux = NULL;

    if (item == NULL)
    {
        printf("O item enviado é NULO!\n");
        return;
    }

    printf("ID:%d\n", item_get_id(item));
    printf("Nome:%s\n", item_get_name(item));
    printf("Relevância:%04d\n", item_get_relevance(item));
    printf("URL:%s\n", item_get_mainUrl(item));
    printf("Num palavras-chave:%02d\n", item_get_numKeyWords(item));
    printf("Palavras-chave:\n");

    aux = item_get_keyWords(item);
    for (int j = 0; j < item_get_numKeyWords(item); j++)
    {
        printf("\t[%d]%s\n", j, aux[j]);
    }
    printf("\n");
}

// GETTERS

int item_get_id(ITEM *item)
{
    if (item != NULL)
        return (item->id);

    printf("\nERROR: item_get_chave()\n");
    return ERROR;
}

char *item_get_name(ITEM *item)
{
    if (item != NULL)
        return (item->name);

    printf("\nERROR: item_get_name()\n");
    return NULL;
}

int item_get_relevance(ITEM *item)
{
    if (item != NULL)
        return item->relevance;

    printf("\nERROR: item_get_relevance()\n");
    return ERROR;
}

char *item_get_mainUrl(ITEM *item)
{
    if (item != NULL)
        return item->mainUrl;

    printf("\nERROR: item_get_mainUrl()\n");
    return NULL;
}

int item_get_numKeyWords(ITEM *item)
{
    if (item != NULL)
        return item->numKeyWords;

    printf("\nERROR: item_get_numKeyWords()\n");
    return ERROR;
}

char **item_get_keyWords(ITEM *item)
{
    if (item != NULL)
        return item->keyWords;

    printf("\nERROR: item_get_keyWords()\n");
    return NULL;
}

ITEM *item_copy(ITEM *source)
{
    if (source == NULL)
        return NULL;

    ITEM *destiny = NULL;

    destiny = item_criar();

    // Copia o conteúdo do item origem para o item destino
    item_set_id(destiny, item_get_id(source));
    memcpy(item_get_name(destiny), item_get_name(source), strlen(item_get_name(source)) + 1);
    item_set_relevance(destiny, item_get_relevance(source));
    memcpy(item_get_mainUrl(destiny), item_get_mainUrl(source), strlen(item_get_mainUrl(source)) + 1);
    item_set_numKeyWords(destiny, item_get_numKeyWords(source));

    // copiando o vetor de key-words
    destiny->keyWords = (char **) malloc((item_get_numKeyWords(destiny)) * sizeof(char *));
    for (int i = 0; i < item_get_numKeyWords(destiny); i++)
    {
        destiny->keyWords[i] = (char *)malloc((strlen(source->keyWords[i]) + 1) * sizeof(char));
        strcpy(destiny->keyWords[i], source->keyWords[i]);
    }

    return destiny;
}

// SETTERS

boolean item_set_id(ITEM *item, int id)
{
    if (id < 0 || id > 9999)
    {
        printf("Valor de ID inválido! Intervalo: 0 a 9999!");
        return FALSE;
    }

    if (item != NULL)
    {
        (item)->id = id;

        return TRUE;
    }
    return FALSE;
}

boolean item_set_name(ITEM *item, char *name)
{
    if ((item) != NULL && name != NULL)
    {
        strcpy((item)->name, name);
        return TRUE;
    }
    return FALSE;
}

boolean item_set_relevance(ITEM *item, int rel)
{
    if (rel < 0 || rel > 1000)
    {
        printf("O valor da relevância pode variar de 0 a 1000!");
        return FALSE;
    }

    if ((item) != NULL)
    {
        (item)->relevance = rel;
        return TRUE;
    }
    return FALSE;
}

boolean item_set_mainUrl(ITEM *item, char *url)
{
    if (url == NULL || strlen(url) > 100)
    {
        printf("O limite de caracteres para a URL do site é de 100 caracteres!\n");
        return FALSE;
    }

    strcpy((item)->mainUrl, url);
    return TRUE;
}

boolean item_set_numKeyWords(ITEM *item, int num)
{
    if (num < 0 || num > 10)
    {
        printf("Não é possível adicionar mais de 10 palavras-chave em um site!");
        return FALSE;
    }

    (item)->numKeyWords = num;
    return TRUE;
}

boolean item_set_keyWords(ITEM *item, char *word)
{
    // Inicializando os campos
    if (word == NULL)
    {
        item->keyWords = NULL;
        item->numKeyWords = 0;
        return FALSE;
    }

    // Cada palavra-chave pode ter no máximo 50 caracteres
    if (strlen(word) > 50)
    {
        printf("O limite de caracteres para palavras-chave é de 50 caracteres!\n");
        return FALSE;
    }

    // O número máximo de palavras-chave por site é de 10 palavras-chaves
    if ((item) != NULL && (item)->numKeyWords < 10)
    {
        item->numKeyWords++;

        item->keyWords = (char **)realloc(item->keyWords, (item->numKeyWords) * sizeof(char *));
        item->keyWords[item->numKeyWords - 1] = (char *)malloc((1 + strlen(word)) * sizeof(char));
        strcpy(item->keyWords[item->numKeyWords - 1], word);

        return TRUE;
    }
    return FALSE;
}