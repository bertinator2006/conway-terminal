#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"
#include "conway.h"

#define WIDTH 10
#define HEIGHT 10


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage:\n\t./program [file]\n");
        exit(EXIT_FAILURE);
    }

	printf("Starting game...\n");
	Board board = create_board_from_file(argv[1]);

    info_board(board);
    increment_state(board);
    print_separator(board);
    print_board(board);

	return 0;
}
