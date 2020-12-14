# Mini Googlebot

Este projeto faz parte da disciplina [SCC0202](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SCC0202&codcur=55041&codhab=0) do segundo semestre do curso de Ciências de Computação no ICMC-USP.

Seu propósito é simular um algoritmo de coleta de dados criado pela Google, o chamado Googlebot, utilizando a linguagem C. O algoritmo, que procura pela internet URLs que redirecionem para websites, coleta um conjunto de dados e metadados de cada website, permitindo que o algoritmo decida sua relevância para o usuário. Desse modo, este exercicio procura avaliar a decisão correta na escolha de uma determinada estrutura de dados, bem como a implementação eficiente de suas funções.

## A Equipe

* **11796444 - Giovanni Shibaki Camargo** - [giovanni-shibaki](https://github.com/giovanni-shibaki)

* **11796451 - Pedro Kenzo Muramatsu Carmo** - [Muramatsu2602](https://github.com/Muramatsu2602)

## Compilador/Plataforma Utilizada

O compilador escolhido foi o GCC (Gnu C Compiler) e o código-fonte fora compilado e testado utilizando a flag -std=c99, para garantir o padrão C99. Cada desenvolvedor optou por editores de textos distintos e utilizou-se a ferramenta de versionamento de codigo GitHub.

## Sobre a Estrutura de Dados Escolhida

Nosso projeto contou com a aplicação mista de estruturas de dados: uma DLL (antes Lista Simplesmente ligada, na entrega 1)e uma AVL.

Como comentado, substituimos na entrega 2 deste projeto a lista Simplesmente Encadeada por um **Lista Duplamente Ligada (ou DLL)**. Trata-se de uma estrutura de dados linear e dinamica (fator este importante dado o fato que novos sites podem ser inseridos ou removidos em runtime), que permite iteração bidirecional, isto é, percorrer a lista a partir de qualquer uma de suas extremidades. Isso reduz o numero de iterações todas as vezes que a função de lista_busca é acionada, pois agora iniciamos a busca na extremidade mais proxima da chave desejada, evitando a chamada "busca cega".

Ademais,facilita a inserção de um nó antes de outro nó específico. Resumidamente, os ponteiros que apontam para os nós vizinhos (próximo e anterior), nos casos em que a lista é percorrida para ambos sentidos percorridos, evitam iterações extras para se obter o nó anterior ou posterior. Por mais que ocupe mais memoria por utilizar o ponteiro "anterior", a predominancia da busca neste projeto torna evidente a vantagem de uma DLL.

Além disso, com o propósito de exercer justamente as duas novas funções que definem a entrega 2 (busca por palavra chave e sugestão de sites), utilizamos o conceito de Arvore AVL. Seu funcionamento basico consiste em armazenar as referências de todos os nós que contêm uma dada palavra-chave. Dessa forma, cada item da arvore (**ITEM2**)  representa uma palavra-chave e aponta para todos os nós da DLL (websites) que possuam esta palavra-chave. Somado a isso, salienta-se que a lista de nós de cada **ITEM2** é ordenada pela relevancia dos websites.

Como salienta a proposta do projeto, a "Busca por palavra-chave" é a operação mais importante e frequente no sistema Mini Googlebot. Foi por este motivo que optamos por implementar uma AVL, haja vista que esta estrutura de dados permite busca com eficiência de tempo de O(log n), o que é muito mais eficiente do que procurar por todas palavras chaves em todos os itens (sites) da DLL. A titulo de exemplo, assintoticamente teriamos uma performance O(logn) da arvore versus O(n^2) na operação de Sugerir Sites, o que evidencia a vantagem na adoção desta Estrutura de Dados.

## Manual de Uso
No repositorio deste projeto, há dois diretórios principais, juntamente ao arquivo principal **main-bot.c**. No diretorio **Data**, podemos encontrar o arquivo de entrada **googlebot.txt** que contem a coleção de websites dispostos em formato CSV. Em **Util**, por sua vez, estão guardados todos os arquivos de extensões *.c* e *.h* relacionados a implementação e definição do TAD escolhido.

De modo a compilar e executar o programa, voce deve utilizar os seguintes comandos no terminal Linux:
```
make
make run
```
Em seguida, um menu deve aparecer:
```
Opções:
1 - Inserir um site;
2 - Remover um site;
3 - Inserir Palavra-Chave um site;
4 - Atualizar relevância um site;
5 - Imprimir a lista de sites;
6 - Buscar sites por Palavra-chave;
7 - Sugestão de sites;
8 - Mostrar árvore AVL de palavras-chave;
9 - Sair.
Insira a Opção: 

```
Digite no teclado o número correspondente a operação desejada e pressione 8 para sair do programa. 

OBS: se deseja remover os arquivos gerados na execução, digite <make clean>.

## Sobre as Funcionalidades do GoogleBot
Segue abaixo a explicação sobre cada operação e sua implementação:

### 1 - Inserir um site
Existem duas maneiras de inserir um novo website no TAD Lista: o primeiro lê diretamente do arquivo .txt em formato CSV, extraindo de lá os dados de uma linha e a partir disso criando o ITEM, lidando também com a formatação da string (por meio do strtok); o outro recebe o input do teclado, preenche e cria o ITEM. Ambos invocam a função <lista_inserir_ordenado>, que adiciona o ITEM na lista de acordo com seu ID.

### 2 - Remover um site
A partir de um ID fornecido pelo usuario, apaga esse item da lista. Se o ID de fato existe, invoca-se a função <lista_remover>, a qual invoca a função <lista_busca_ordenada2> que retorna o nó a ser removido e por fim remove o nó encontrado. 

Visto que agora possuimos uma Arvore AVL que tambem referência os nós da DLL (websites). Quando um site é removido, sua referência na AVL também é  removida. Ou seja, invocamos a função de <item2_remover_no_lista>, que cumpre justamente este papel.

### 3 - Inserir Palavra-Chave um site
Primeiramente, pede-se um ID, que é validado pela função <lista_busca_ordenada>. A seguir, retorna-se o item desejado, permitindo que o *setter* <item_set_keywords> inclua uma nova palavra-chave ao website e refaça a ordenação em ordem alfabética das palavras-chave por meio do algoritmo de ordenação Insertion Sort, escolhido pelo fato de que o tamanho do vetor de elementos (no caso um vetor de strings) ser pequeno.
Com um maximo de 10 palavras-chave por website, depender de uma ordenação que aloca memoria adicional (como o MergeSort, por exemplo), seria um gasto desnessario. Alem disso, ainda que o Insertion Sort seja O(n^2), em detrimento de O(nlog(n)), vale ressaltar que o tamanho pequeno e fixo do vetor jamais sera comparavel a um comportamento assintotico, que confere a estes algoritmos sua classe especifica.

Ademais, toda vez que uma nova palavra-chave é inserida em um dado *website*, realiza-se uma busca na Arvore AVL. Desse modo, caso a palavra-chave for encontrada na Árvore, o endereço do nó do *website* é inserido na lista de endereços do **ITEM2**, da Arvore AVL. Caso contrario, se a palavra-chave nao for encontrada, adiciona-se um novo no  à Árvore com essa palavra-chave (evitando que hajam duplicatas de uma mesma palavra-chave). 

### 4 - Atualizar relevância um site
Essa função funciona de modo semelhante a anterior, visto que ambas, utilizam *setters* de um dado ITEM (website). Portanto, depois de verificar o ID fornecido e retornando o ITEM a quem este corresponde, chamamos <item_set_relevance>, alterando um dos dados da struct ITEM.

### (EXTRA) 5 - Imprimir a lista de Sites
Mostra-se na tela o conteúdo do TAD Lista, ou seja, todos os websites armazenados até então, mostrando cada um de seus atributos, em ordem de ID.

### 6 - Buscar sites por Palavra-chave
Primeiramente, busca-se o nó da AVL que contém a palavra-chave procurada. Assim, a referência para todos os nós da DLL São armazenados em um vetor do tipo NO **nos, impressos na tela por meio da funcao <lista_imprimir_short2>. 

### 7 - Sugestão de sites
Inicialmente, realiza as mesmas acoes da operacao acima (com exceção do <lista_imprimir_short2>). A seguir, todas as palavras-chave dos nós da DLL armazenados (em vetor do tipo NO** nos) são coletados e buscadas na AVL. Dessa forma, todos os sites que possuem ao menos uma das palavras encontradas, são ordenados em ordem decrescene com base no valor de suas relevâncias e, assim, exibindo na tela os 5 *websites* mais relevantes ( utilizando-se da função <lista_imprimir_short>).

### 8 - Mostrar árvore AVL de palavras-chave; (EXTRA)
Imprime, em-ordem, cada um dos nós (cada um dos quais contem uma palavra chave) da árvore AVL. 

### 9 - Sair
Fecha o menu e chama a função <lista_apagar>, <avl_apagar_arvore> e <fclose()>, liberando toda a memória dinamicamente alocada. 

### Formato da Entrada
Os registros contidos no arquivo .txt seguem o formato CSV (*Comma Separated Value*), o que significa que todos os campos de um dado website estão separados por vírgulass. Segue abaixo um exemplo: 
```
0001,YouTube,900,https://www.youtube.com/,youtube,videos,online
0002,Netflix,800,https://www.netflix.com/br/,netflix,videos,streaming
```
Os dados presentes neste .txt são depositados na estrutura de dados antes da interação com o usuário. Vale mencionar que todo o *input* é tratado como se *não fosse necessariamente ordenado*.