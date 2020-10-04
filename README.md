# Mini Googlebot
This is a project for the [SCC0202](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SCC0202&codcur=55041&codhab=0) course @ University of Sao Paulo.

It can be defined as a simulation of a data-gathering algorithm created by Google called "Googlebot" using C, which searches the web for URLs that redirect to websites. As a result, it gathers a dataset of each website, allowing Google's search Algorithm to decide its relevance to the user. This project aims to utilize the correct data structures in order to store and process data in a efficient manner.

## The Team
This project was developed by the undergrad students of Computer Science course at ICMC-USP, SP-Brazil:

* **11796444 - Giovanni Shibaki Camargo** - [giovanni-shibaki](https://github.com/giovanni-shibaki)

* **11796451 - Pedro Kenzo Muramatsu Carmo** - [Muramatsu2602](https://github.com/Muramatsu2602)

<!-- ## Compiler/Plataform Used
gcc .... -->

## Data Structure Usage and Implementation Justification
We decided to utilized the concept of Simple Linked List to implement an ADT to store the websites. This data structures has been chosen given the following benefits:

 * It offers a flexible storage (that depends on the system's dynammic memory), defined during runtime.
 * ...

## User Manual
In the project's repository, there are two folders, allong with the main .c file (called "main-bot.c"). In the **Data**, we can find all the url-related data acquired from the input. Whereas in the **Util**, we can find all ".c" and ".h" files regarding the implementation of the chosen ADT and a auxiliary file called "fileManager". This last one is tasked with dealing with the input, thus not overloading the main file with too many functions.

We can also point out ...

## Tools, Development Model and Presentation
This project is developed using the C language, according to the C99 pattern.

### Observation
These pieces of information must be read on a .txt file named "googlebot.txt", following the CSV format (*Comma Separated Value*) - meaning that all the data on a website is separated using commas. Here's an example:
```
0001,YouTube,900,https://www.youtube.com/,youtube,videos,online
0002,Netflix,800,https://www.netflix.com/br/,netflix,videos,streaming
```
<!--
  ### Project's features
  When executed,  the programme must show the following options:
  * **Insert a website**
  *  **Remove a website**
  * **Insert primary-key**
  * **Update Relevance**
  * **Exit**
-->
## Extra
For more details regarding this project (in pt-br), please read [this](https://ae4.tidia-ae.usp.br/access/content/group/a1128994-3797-49cb-8f1f-08ecfe0ced63/Projeto%20-%20parte%20I.pdf)
