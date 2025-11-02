SRC = src/conway.c src/main.c
BIN = program
FLAGS = -Wall -Wextra -Wshadow -Wpedantic

def:
	@echo "Please select one of the following:"
	@echo "    make mac"
	@echo "    make win"

mac:
	clang $(SRC) -o $(BIN) $(FLAGS)

win:
	gcc $(SRC) -o $(BIN) $(FLAGS)
