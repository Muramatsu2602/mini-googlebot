# check this for an awesome-looking makefile:  https://www.notion.so/Tutorial-Makefile-5a7fba7f5bae442b8b4677dd97b900d0

FLAG = -Wall =Werror
OBJ1 = Util/item.c -o Util/item.o
OBJ2 = Util/listadinamica.c -o Util/listadinamica.o
MAIN=main-bot.c
UTIL= Util/*.o
BINARY=main

greetings:
	@echo "Welcome to Part 1 of the Google MiniBot Project"
all:
	@echo "Compiling all ./Util!"
	@gcc $(FLAG) -c $(OBJ1) -I Util/
	@gcc $(FLAG) -c $(OBJ2) -I Util/
	@gcc $(FLAG) $(MAIN) $(UTIL) -o $(BINARY) -I Util/

run:
	@echo "Running the Application!"
	@./$(BINARY)

clean:
	@echo "Cleaning the binary file!"
	@rm *.o

zip:
	@echo "Creating a zip folder with all files!"
	@zip -r proj1part1-bcc020.zip /Util/*.c /Util/*.h Makefile