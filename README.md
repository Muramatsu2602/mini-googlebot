# Mini Googlebot

Este projeto faz parte da disciplina [SCC0202](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SCC0202&codcur=55041&codhab=0) do segundo semestre do curso de Ciências de Computação no ICMC-USP.

Seu propósito é simular um algoritmo de coleta de dados criado pela Google, o chamado Googlebot, utilizando a linguagem C. O algoritmo, que procura pela internet URLs que redirecionem para websites, coleta um conjunto de dados e metadados de cada website, permitindo que o algoritmo decida sua relevância para o usuário. Desse modo, este exercicio procura avaliar a decisão correta na escolha de uma determinada estrutura de dados, bem como a implementação eficiente de suas funções.

## A Equipe

* **11796444 - Giovanni Shibaki Camargo** - [giovanni-shibaki](https://github.com/giovanni-shibaki)

* **11796451 - Pedro Kenzo Muramatsu Carmo** - [Muramatsu2602](https://github.com/Muramatsu2602)

## Compilador/Plataforma Utilizada

O compilador escolhido foi o GCC (Gnu C Compiler) e o código-fonte fora compilado e testado utilizando a flag -std=c99, para garantir o padrão C99. Cada desenvolvedor optou por editores de textos distintos e utilizou-se a ferramenta de versionamento de codigo GitHub.

## Sobre a Estrutura de Dados Escolhida
Como salienta a proposta do projeto, a "Busca por palavra-chave" é a operação mais importante e frequente no sistema Mini Googlebot. Assim, de modo a reduzir a quantidade de operações realizadas nas buscas

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
8 - Sair.
Insira a Opção: 
```
Digite no teclado o número correspondente a operação desejada e pressione 8 para sair do programa. 

OBS: se deseja remover os arquivos gerados na execução, digite <make clean>.

## Sobre as Funcionalidades do GoogleBot
Segue abaixo a explicação sobre cada operação e sua implementação:

### 1 - Inserir um site
Existem duas maneiras de inserir um novo website no TAD Lista: o primeiro lê diretamente do arquivo .txt em formato CSV, extraindo de lá os dados de uma linha e a partir disso criando o ITEM, lidando também com a formatação da string (por meio do strtok); o outro recebe o input do teclado, preenche e cria o ITEM. Ambos invocam a função <lista_inserir_ordenado>, que adiciona o ITEM na lista de acordo com seu ID.

### 2 - Remover um site
A partir de um ID fornecido pelo usuario, apaga esse item da lista. Se o ID de fato existe, invoca-se a função <lista_remover>, a qual itera sobre a lista ordenada, encontra o ponto correto e assim atualiza os nós adjacentes apos deleta-lo.

### 3 - Inserir Palavra-Chave um site
Primeiramente, pede-se um ID, que é validado pela função <lista_busca_ordenada>. A seguir, retorna-se o item desejado, permitindo que o *setter* <item_set_keywords> inclua uma nova palavra-chave ao website.

### 4 - Atualizar relevância um site
Essa função funciona de modo semelhante a anterior, visto que ambas, utilizam *setters* de um dado ITEM (website). Portanto, depois de verificar o ID fornecido e retornando o ITEM a quem este corresponde, chamamos <item_set_relevance>, alterando um dos dados da struct ITEM.

### (EXTRA) 5 - Imprimir a lista de Sites
Mostra-se na tela o conteúdo do TAD Lista, ou seja, todos os websites armazenados até então, mostrando cada um de seus atributos, em ordem de ID.

### 6 - Buscar sites por Palavra-chave
Dado uma palavra-chave, iteramos pela lista. Para cada website, roda-se um loop na matriz de palavras-chave, ate que se encontre o termo desejado. Se sim, adicionamos esse website em uma lista auxiliar <key_lista>. Em seguida, imprimimos na tela o conteudo dessa lista, exibindo apenas nome e URL de cada registro.

### 7 - Sugestão de sites
A função de Sugestão de Sites funciona em conjunto com a função de busca por palavra chave, pois primeiro recebe uma palavra-chave para que todos os sites que possuem essa palavra-chave sejam copiados para dentro de outra lista auxiliar <key_lista>, que servirá para fornecer as demais palavras chaves utilizadas nesta função. Em seguida a função <lista_sugerir_sites> é chamada para que todas as palavras chaves dos itens em <key_lista> sejam selecionadas.

Por fim, todos os sites que contém pelo menos uma das palavras-chaves selecionadas são inseridos em uma lista. Em seguida são retidadas as possíveis repetições de sites (através da função <lista_tirar_repeticoes>) e exibidos os 5 sites mais relevantes dos encontrados (função <lista_imprimir_short>).

### 8 - Sair
Fecha o menu e chama a função <lista_apagar> e <fclose()>, liberando toda a memória dinamicamente alocada.

### Formato da Entrada
Os registros contidos no arquivo .txt seguem o formato CSV (*Comma Separated Value*), o que significa que todos os campos de um dado website estão separados por vírgulass. Segue abaixo um exemplo: 
```
0001,YouTube,900,https://www.youtube.com/,youtube,videos,online
0002,Netflix,800,https://www.netflix.com/br/,netflix,videos,streaming
```
Os dados presentes neste .txt são depositados na estrutura de dados antes da interação com o usuário. Vale mencionar que todo o *input* é tratado como se *não fosse necessariamente ordenado*.