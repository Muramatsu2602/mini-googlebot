# Mini Googlebot
This is a project for the [SCC0202](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SCC0202&codcur=55041&codhab=0) course @ University of Sao Paulo.

It can be defined as a simulation of a data-gathering algorithm created by Google called "Googlebot" using C, which searches the web for URLs that redirect to websites. As a result, it gathers a dataset of each website, allowing Google's search Algorithm to decide its relevance to the user. This project aims to utilize the correct data structures in order to store and process data in a efficient manner.

## The Team
This project was developed by the undergrad students of Computer Science course at ICMC-USP, SP-Brazil:

* **11796444 - Giovanni Shibaki Camargo** - [giovanni-shibaki](https://github.com/giovanni-shibaki)

* **11796451 - Pedro Kenzo Muramatsu Carmo** - [Muramatsu2602](https://github.com/Muramatsu2602)

## Compiler/Plataform Used test 
The chosen compiler was GCC (Gnu C Compiler), using the flag -std=c99. Each programmer used a distinct text editor, both agreed upon using a GitHub repository to store the project's source-code.

## About the Data Structure Chosen
We decided to utilized the concept of **Simple Linked List** to implement an ADT to store the websites. This data structures has been chosen given the following benefits:

 * It offers a flexible storage (that depends on the system's dynammic memory), defined during runtime;
 * Allows Insertion and Deletion of items in all positions of the list;
 * Easy vizualization of the state of a linked list, allowing to easily draw that state and think through the code;
 * Easy to build specific functions for different problems and aplications.



## User Manual
In the project's repository, there are two folders, along with the main .c file (called "main-bot.c"). In the **Data**, we can find the input file: **googlebot.txt** . Whereas in the **Util**, we can find all ".c" and ".h" files regarding the implementation of the chosen ADT.

In order to compile and execute the program, you should use the following Makefile commands:
```
make
make run
```

Right after, a menu shall appear:
```
Opções:
1 - Inserir um site;
2 - Remover um site;
3 - Inserir Palavra-Chave um site;
4 - Atualizar relevância um site;
5 - Imprimir a lista de Sites;
6 - Sair.
Insira a Opção: 
```
Choose any of the shown options and select 6 to exit the application. Enjoy!

OBS: if you want to remove all binary files from the repository, type **make clean** on the terminal.

## About each Googlebot Function
Heres what each option does and its implementation:

### 1 - Insert a website
There are two main ways of inserting a website in this program: one reads a string in CSV format (that comes from a .txt file), extracts the data and creates an ITEM; the other reads keyboard input and creates the ITEM.

The second function, which is called when option 1 is selected, tests each input using SETTER functions, thus creating a ITEM (website). This same item is then sent to the **lista_inserir_ordenado** function, which inserts a new ITEM to the list in a ordered fashion.

### 2 - Remove a website
Reads an ID whose ITEM the user wants to delete from the list. If that ID exists, the **lista_remover** function is called. This function traverses through the ordered list, finds the correct spot and then proceeds to update the nodes that were adjacent to the deleted node.

### 3 - Inserting a new Keyword in a website
Fist, a ID is requested and then checked. Afterwards, the item whose ID was just verified is retrieved to the function, allowing for the **item_set_keywords** setter to add a new keyword to the website.

### 4 - Updating the relevance of a website
This function works similarly to the previous one, due to the fact that both use the setter function of the given ITEM (website). Therefore, after checking the ID and then retrieving the ITEM, we call the **item_set_relevance** setter, changing one of the ADT values.

### (EXTRA) 5 - Printing website list
This function, that was not required by the activity's plan, prints all registered websites from the list.

### 6 - Exit Application
Ends the application and then calls **lista_apagar** and closes the file, which frees all heap memory allocated.

### Input Format
These pieces of information must be read on a .txt file named "googlebot.txt", following the CSV format (*Comma Separated Value*) - meaning that all the data on a website is separated using commas. Here's an example:
```
0001,YouTube,900,https://www.youtube.com/,youtube,videos,online
0002,Netflix,800,https://www.netflix.com/br/,netflix,videos,streaming
```
The data present in this .txt is inserted into the data structure prior to the user interaction. It's important to mention that all input is treated as if it's **not already sorted**.

## Extra
For more details regarding this project (in pt-br), please read [this](https://ae4.tidia-ae.usp.br/access/content/group/a1128994-3797-49cb-8f1f-08ecfe0ced63/Projeto%20-%20parte%20I.pdf)
