OBJ1 = Util/item.c -o Util/item.o
OBJ2 = Util/dll.c -o Util/dll.o
MAIN= main-bot.c
UTIL= Util/*.o
BINARY= main

# Flags for default compilation
CFLAGS = -Werror -std=c99 
# Flags for nitpicking compilation 
CFLAGS2 = -Wall -Wextra -Wpedantic -Wpointer-arith -O3 -march=native -std=c99
# Valgrind Flags
VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes

all:
	@echo "Welcome to Part 2 of the Google MiniBot Project!"
	@echo "Compiling all ./Util!"
	@gcc $(CFLAGS) -c $(OBJ1) -I Util/
	@gcc $(CFLAGS) -c $(OBJ2) -I Util/
	@gcc $(CFLAGS) $(MAIN) $(UTIL) -o $(BINARY) -I Util/

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
	@echo "Proudly made by: Giovanni Shibaki Camargo & Pedro Kenzo Muramatsu Carmo, from BCC 020 ICMC-USP"
	@echo "Creating a zip folder with all important files!"
	@zip -r proj1part2-bcc020.zip Data/*.txt Util/*.c Util/*.h $(MAIN) Makefile README.md
