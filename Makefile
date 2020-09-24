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
