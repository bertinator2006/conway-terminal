#include <stdio.h>
#include "terminal.h"
#include "conway.h"

#define WIDTH 10
#define HEIGHT 10


int main(void)
{
	printf("Starting game...\n");
	Board board = init_empty_board(WIDTH, HEIGHT);

	print_board(board);

	return 0;
}
