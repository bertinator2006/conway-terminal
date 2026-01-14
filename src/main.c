#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "terminal.h"
#include "conway.h"

#define WIDTH 20
#define HEIGHT 20

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage:\n\t./program [file]\n");
		exit(EXIT_FAILURE);
	}

	printf("Starting game...\n");
        // Board board = init_empty_board(WIDTH, HEIGHT);
        // // TODO - create dummy test board
	Board board = create_board_from_file(argv[1]);

        while (true)
        {
                print_board(board);
                increment_state(board);
                fgets(NULL, 0, stdin);
        }

        destroy_board(board);
	return 0;
}