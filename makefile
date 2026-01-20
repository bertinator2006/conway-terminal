SRC = src/conway.c src/terminal_main.c src/terminal.c
BIN = program

all:
	gcc $(SRC) -o $(BIN)

run:
	./$(BIN)

clean:
	rm $(BIN)
