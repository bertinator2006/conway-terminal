SRC = src/conway.c src/main.c
BIN = program

all:
	make wsl

def:
	@echo "Please select one of the following:"
	@echo "    make mac"
	@echo "    make win"
	@echo "    make wsl"

mac:
	@echo "clang $(SRC) -o $(BIN) $(FLAGS)"
	clang $(SRC) -o $(BIN) $(FLAGS)

win:
	@echo "gcc $(SRC) -o $(BIN) $(FLAGS)"
	gcc $(SRC) -o $(BIN) $(FLAGS)

clean:
	rm $(BIN)