/*
	Giovanni Shibaki Camargo
	Nusp: 11796444
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVL.h"

struct no2_
{
	ITEM2 *item;
	NO2 *esq;
	NO2 *dir;
	int altura;
};

struct avl_{
	NO2 *raiz;
	int profundidade;
};

AVL *avl_criar(void)
{
	AVL *r = (AVL *) malloc(sizeof(AVL));
	if(r != NULL)
	{
		r->raiz = NULL;
		r->profundidade = -1;
	}
	return (r);
}

int avl_altura_no(NO2 *raiz)
{
	if(raiz == NULL)
		return -1;
	return raiz->altura;
}

NO2 *avl_rotacao_direita(NO2 *raiz)
{
	NO2 *b = raiz->esq;
	raiz->esq = b->dir;
	b->dir = raiz;

	raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;

	b->altura = max(avl_altura_no(b->esq), raiz->altura) + 1;

	// Retornar a raiz da árvore já rotacionada
	return b;
}

NO2 *avl_rotacao_esquerda(NO2 *raiz)
{
	NO2 *b = raiz->dir;
	raiz->dir = b->esq;
	b->esq = raiz;

	raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;

	b->altura = max(avl_altura_no(b->dir), raiz->altura) + 1;

	// Retornar a raiz da árvore já rotacionada
	return b;
}

NO2 *avl_rotacao_direita_esquerda(NO2 *raiz)
{
	// Realiza a rotação esquerda no filho a direita da raiz
	// Para depois fazer a rotação esquerda nele
	raiz->dir = avl_rotacao_direita(raiz->dir);
	return avl_rotacao_esquerda(raiz);
}

NO2 *avl_rotacao_esquerda_direita(NO2 *raiz)
{
	// Realiza a rotação direita no filho a esquerda da raiz
	// Para depois fazer a rotação direita nele
	raiz->esq = avl_rotacao_esquerda(raiz->esq);
	return avl_rotacao_direita(raiz);
}

NO2 *avl_cria_no(ITEM2 *item)
{
	NO2 *n = (NO2 *) malloc(sizeof(NO2));

	if((n != NULL) && (item != NULL))
	{
		n->altura = 0;
		n->item = item;
		n->esq = NULL;
		n->dir = NULL;
		return n;
	}
	return NULL;
}

// Mesmos critérios de ABB para a inserção de nós
NO2 *avl_inserir_no(NO2 *raiz, ITEM2 *item)
{
	if(raiz == NULL)
	{
		raiz = avl_cria_no(item);
	}
	else if(strcmp(item2_get_keyWord(raiz->item), item2_get_keyWord(item)) < 0)
	{
		raiz->dir = avl_inserir_no(raiz->dir, item);
	}
	else if(strcmp(item2_get_keyWord(raiz->item), item2_get_keyWord(item)) > 0)
	{
		raiz->esq = avl_inserir_no(raiz->esq, item);
	}

	raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;

	// Se for negativo é rotação esquerda (lado direito está desbalanceado) ou direita/esquerda
	if(avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir) == -2)
	{
		// Ou posso verificar também se os fatores de balanceamento tem sinais opostos
		// Vendo assim se o novo nó foi inserido a direita ou a esquerda do raiz->dir
		// Para assim realizar a rotação
		if(strcmp(item2_get_keyWord(item), item2_get_keyWord(raiz->dir->item)) > 0)
		{
			// Item entrou a direita de raiz->dir
			raiz = avl_rotacao_esquerda(raiz);
		}
		else
		{
			// Item entrou a esquerda de raiz->dir
			raiz = avl_rotacao_direita_esquerda(raiz);
		}
	}

	// Se for positivo é rotação direita (lado esquerdo está desbalanceado) ou esquerda/direita
	if(avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir) == 2)
	{
		if(strcmp(item2_get_keyWord(item), item2_get_keyWord(raiz->esq->item)) < 0)
		{
			// Item entrou a esquerda de raiz->esq
			raiz = avl_rotacao_direita(raiz);
		}
		else
		{
			// Item entrou a direita de raiz->esq
			raiz = avl_rotacao_esquerda_direita(raiz);
		}
	}

	return raiz;
}

boolean avl_inserir(AVL *T, ITEM2 *item)
{
	return ((T->raiz = avl_inserir_no(T->raiz, item)) != NULL);
}


/*
	https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
	Printa conforme entra, printa raiz, no esquerdo, no direito
*/
void printPreorder(NO2 *no)
{
	if(no == NULL)
	{
		return;
	}

	// Printa o valor do item atual
	printf("%s ",item2_get_keyWord(no->item));

	// Chamada recursiva para o filho esquerdo
	printPreorder(no->esq);

	// Chamada recursiva para o filho direito
	printPreorder(no->dir);
}

/*
	Último nó a esquerda, depois o nó PAI, depois o da direita
	e assim por diante
*/
void printInorder(NO2 *no)
{
	if(no == NULL)
	{
		return;
	}

	// Chamada recursiva para o filho esquerdo
	printPreorder(no->esq);

	// Printa o valor do item atual
	printf("%s ",item2_get_keyWord(no->item));

	// Chamada recursiva para o filho direito
	printPreorder(no->dir);
}

/*
	Parecido com o Inorder, mas depois do filho esquerdo mostra o direito, e só depois o pai dele
*/
void printPostorder(NO2 *no)
{
	if(no == NULL)
	{
		return;
	}

	// Chamada recursiva para o filho esquerdo
	printPreorder(no->esq);

	// Chamada recursiva para o filho direito
	printPreorder(no->dir);

	// Printa o valor do item atual
	printf("%s ",item2_get_keyWord(no->item));
}

int avl_profundidade(NO2 *no)
{
	if(no == NULL)
		return -1;
	int esq = avl_profundidade(no->esq);
	int dir = avl_profundidade(no->dir);

	return ((esq > dir) ? esq : dir) + 1;
}

int get_profundidade(AVL *arv)
{
	return avl_profundidade(arv->raiz);
}

void apagar_arvore(NO2 **raiz)
{
	if(*raiz != NULL)
	{
		apagar_arvore(&(*raiz)->esq);
		apagar_arvore(&(*raiz)->dir);
		item2_apagar(&(*raiz)->item);
		free(*raiz);
		*raiz = NULL;
	}
}

void avl_apagar_arvore(AVL **T)
{
	apagar_arvore(&(*T)->raiz);
	free(*T);
	*T = NULL;
}

void printa_arvore(NO2 *raiz, int espacamento)
{
	if(raiz == NULL)
		return;

	espacamento += 10;

	printa_arvore(raiz->dir, espacamento);

	printf("\n");
	for(int i = 10; i < espacamento; i++)
	{
		printf(" ");
	}
	printf("%s\n", item2_get_keyWord(raiz->item));

	printa_arvore(raiz->esq, espacamento);
}

void avl_printa_arvore(AVL *arv)
{
	printa_arvore(arv->raiz, 0);
}

int conta_folhas(NO2 *raiz)
{
	if(raiz == NULL)
		return 0;

	if(raiz->esq == NULL && raiz->dir == NULL)
	{
		return 1;
	}	
	else
	{
		// Contar recursivamente o número de nós no lado esquerdo
		// + o número de nós no lado direito de cada nó
		return conta_folhas(raiz->esq) + conta_folhas(raiz->dir);
	}
}

int avl_conta_folhas(AVL *arv)
{
	return conta_folhas(arv->raiz);
}

int conta_nos(NO2 *raiz)
{
	if(raiz == NULL)
		return 0;

	int total = 1;

	// Contar recursivamente o número de nós no lado esquerdo
	// + o número de nós no lado direito de cada nó
	total += (conta_nos(raiz->esq) + conta_nos(raiz->dir));

	return total;
}

int avl_conta_nos(AVL *arv)
{
	return conta_nos(arv->raiz);
}

ITEM2 *avl_busca2(NO2 *raiz, char *chave)
{
	if(raiz == NULL)
		return NULL;

	if(strcmp(chave, item2_get_keyWord(raiz->item)) == 0)
			return (raiz->item);

	// Está em preorder, pode ser feito em posorder ou inorder também
	if(strcmp(chave, item2_get_keyWord(raiz->item)) < 0)
	{
		return (avl_busca2(raiz->esq, chave));
	}
	else
	{
		return (avl_busca2(raiz->dir, chave));
	}
}

// Busca em árvore binária de busca versão recursiva
// Busca pelo ITEM que possui a palavra chave enviada
ITEM2 *avl_busca(AVL *T, char *chave)
{
	return (avl_busca2(T->raiz, chave));
}

void troca_max_esq(NO2 *troca,  NO2 *raiz, NO2 *noAnterior)
{
	if(troca->dir != NULL)
	{
		// Andar até não existir mais valores a direita
		troca_max_esq(troca->dir, raiz, troca);
		return;
	}

	if(raiz == noAnterior)
	{
		// Não javia nenhum nó a direita do primeiro nó a esquerda depois da raiz
		// Então a raiz->esq simplesmente recebe o nó a esquerda do nó que será removido 
		// Ou seja, o nó a ser removido será a RAIZ
		noAnterior->esq = troca->esq;
	}
	else
	{
		// Chegou aqui quando não tem mais nenhum nó a direita E EXISTIA UM NÓ A DIREITA DO PRIMEIRO NÓ A ESQUERDA DA RAIZ, 
		// então a direita do noAnterior será o que está a esquerda do nó que será removido
		noAnterior->dir = troca->esq;
	}

	// O item da raiz será agora o item do último nó a direita encontrado
	raiz->item = troca->item;
	free(troca);
	troca = NULL;
}

NO2 *avl_remover_aux(NO2 **raiz, char *chave)
{
	// Existem 3 casos
	// 1) nó não tem nenhum filho
	// 2) nó tem 1 filho
	// 3) nó tem 2 filhos

	// No caso de remover um nó que tem 2 filhos esse nó excluido será substituido pelo nó mais a esquerda do filho direito
	// Ou o maior nó da árvore esquerda

	NO2 *noAtual;
	if((*raiz) == NULL)
		return (NULL);
	
	if(strcmp(chave,item2_get_keyWord((*raiz)->item)) == 0)
	{
		if((*raiz)->esq == NULL || (*raiz)->dir == NULL)
		{
			// Caso 1 se resume ao caso 2: há um filho ou nenhum filho
			noAtual = *raiz;
			if((*raiz)->esq == NULL)
				*raiz = (*raiz)->dir;
			else
				*raiz = (*raiz)->esq;
			free(noAtual);
			noAtual = NULL;
		}
		else
		{
			// Caso 3
			troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
		}
	}
	else if(strcmp(chave, item2_get_keyWord((*raiz)->item)) < 0)
			return avl_remover_aux(&(*raiz)->esq, chave);
	else if(strcmp(chave, item2_get_keyWord((*raiz)->item)) > 0)
			return avl_remover_aux(&(*raiz)->dir, chave);
	
	if(*raiz != NULL)
	{
		(*raiz)->altura = max(avl_altura_no((*raiz)->esq), avl_altura_no((*raiz)->dir))+1;
		if(avl_altura_no((*raiz)->esq) - avl_altura_no((*raiz)->dir) == -2)
		{
			if(avl_altura_no((*raiz)->dir->esq) - avl_altura_no((*raiz)->dir->dir) <= 0)
			{
				// Para debug
				//printf("\nRodar esquerda...\n");
				*raiz = avl_rotacao_esquerda(*raiz);
			}
			else
			{
				// Para debug
				//printf("\nRodar direita-esquerda...\n");
				*raiz = avl_rotacao_direita_esquerda(*raiz);
			}
		}	

		if(avl_altura_no((*raiz)->esq) - avl_altura_no((*raiz)->dir) == 2)
		{
			if(avl_altura_no((*raiz)->esq->esq) - avl_altura_no((*raiz)->esq->dir) >= 0)
			{
				// Para debug
				//printf("\nRodar direita...\n");
				*raiz = avl_rotacao_direita(*raiz);
			}
			else
			{
				// Para debug
				//printf("\nRodar esquerda-direita...\n");
				*raiz = avl_rotacao_esquerda_direita(*raiz);
			}
		}
	}
	return *raiz;
}

boolean avl_remover(AVL *T, char *chave)
{
	if(T == NULL)
		return FALSE;
	avl_remover_aux(&T->raiz, chave);
	return TRUE;
}

/*
	Função que verifica se uma árvore de busca está perfeitamente balanceada
	Para isso o número de nós de suas subárvores pode diferir no máximo 1
*/
boolean verifica_balanceada(NO2 *raiz)
{
	if(raiz == NULL)
		return 1;

	int numDir = avl_profundidade(raiz->dir);
	int numEsq = avl_profundidade(raiz->esq);

	// Verifica se a diferença de nós a esquerda com os nós a direita é menor ou igual a 1
	if(abs(numDir - numEsq) <= 1 && verifica_balanceada(raiz->dir) && verifica_balanceada(raiz->esq))
	{
		// Se for, retornar TRUE
		return TRUE;
	}
	// Se não for, retornar FALSE
	return FALSE;
}

boolean avl_verifica_balanceada(AVL *T)
{
	if(T == NULL)
		return FALSE;
	return verifica_balanceada(T->raiz);
}