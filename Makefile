OBJ1 = Util/item.c -o Util/item.o
OBJ2 = Util/list.c -o Util/list.o
MAIN= main-bot.c
UTIL= Util/*.o
BINARY= main

CFLAGS = -Werror
VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes

all:
	@echo "Compiling all ./Util!"
	@gcc $(CFLAGS) -c $(OBJ1) -I Util/
	@gcc $(CFLAGS) -c $(OBJ2) -I Util/
	@gcc $(CFLAGS) $(MAIN) $(UTIL) -o $(BINARY) -I Util/

greetings:
	@echo "Welcome to Part 1 of the Google MiniBot Project!"
	@echo "Proudly made by: Giovanni Shibaki Camargo & Pedro Kenzo Muramatsu Carmo, from BCC 020 ICMC-USP"

run:
	@echo "Running the Application!"
	@./$(BINARY)

valval: all
	@echo "Looking for leaks!"
	@valgrind $(VFLAGS) ./$(BINARY)

clean:
	@echo "Cleaning the binary file!"
	@rm Util/*.o
	@rm $(BINARY)

zip:
	@echo "Creating a zip folder with all important files!"
	@zip -r proj1part1-bcc020.zip Data/*.txt Util/*.c Util/*.h $(MAIN) Makefile