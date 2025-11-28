#include <stdio.h>
#include "terminal.h"
#include "conway.h"

#define WIDTH 10
#define HEIGHT 10


int main(int argc, char *argv[])
{
	printf("Starting game...\n");
	Board board = init_board_from_file(WIDTH, HEIGHT);

    info_board(board);

	return 0;
}
