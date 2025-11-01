SRC = src/conway.c src/main.c
BIN = program

mac:
	clang $(SRC) -o $(BIN)

win:
	gcc $(SRC) -o $(BIN)
