SRC = src/conway.c src/main.c src/terminal.c
BIN = program

all:
	gcc $(SRC) -o $(BIN)

run:
	./$(BIN)

