#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "terminal.h"
#include "conway.h"

#define WIDTH 10
#define HEIGHT 10

Board create_test_board();

Board create_test_board()
{
	Board board = create_empty_board(WIDTH, HEIGHT);
	set_cell_as_alive(board, 5, 5);
	set_cell_as_alive(board, 6, 6);
	set_cell_as_alive(board, 4, 7);
	set_cell_as_alive(board, 5, 7);
	set_cell_as_alive(board, 6, 7);
	return board;
}


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
		board = input_from_terminal();
		printf("Finished creating board from terminal.\n");
	}
	else if (argc == 2)
	{
		printf("Loading board from file...\n");
		if (strcmp(argv[1], "-") == 0)
		{
			board = create_test_board();
		}
		else
		{
			board = create_board_from_file(argv[1]);
		}
		printf("Finished loading board from file.\n");
	}


	printf("Starting game...\n");

	while (true)
	{
		print_separator(board);
		print_board(board);
		print_separator(board);

		// Wait for user to hit enter
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {};

		increment_state(board);
	}

	destroy_board(board);
	return 0;
}
