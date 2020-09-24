# check this for an awesome-looking makefile:  https://www.notion.so/Tutorial-Makefile-5a7fba7f5bae442b8b4677dd97b900d0

FLAG = -Wall
OBJ1 = Util/item.c -o Util/item.o
OBJ2 = Util/pilha.c -o Util/pilha.o
MAIN=main-palindromo.c
UTIL= Util/*.o
BINARY=main

all:
	gcc $(FLAG) -c $(OBJ1) -I Util/
	gcc $(FLAG) -c $(OBJ2) -I Util/
	gcc $(FLAG) $(MAIN) $(UTIL) -o $(BINARY) -I Util/

run:
	./$(BINARY)

clean:
	@rm *.o
