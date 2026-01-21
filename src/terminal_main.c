#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "terminal.h"
#include "conway.h"

#define WIDTH 20
#define HEIGHT 20

int main(int argc, char *argv[])
{
	Board board;
	if (argc > 2)
	{
		fprintf(stderr, "Usage:\n\t./program [file]\n");
		exit(EXIT_FAILURE);
	}

	if (argc < 2)
	{
		printf("Creating board from player inputs...\n");
	}
	else if (argc == 2)
	{
		printf("Loading board from file...\n");
		// Board board = init_empty_board(WIDTH, HEIGHT);
		// TODO - create dummy test board
		board = create_board_from_file(argv[1]);
		printf("Finished loading board from file.\n");
	}


	printf("Starting game...\n");

	while (true)
	{
		// print_separator(board);
		// print_board(board);
		print_separator(board);
		print_board(board);
		print_separator(board);
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {};
		increment_state(board);
	}

	destroy_board(board);
	return 0;
}
