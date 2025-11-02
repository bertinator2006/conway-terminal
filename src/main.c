#include <stdio.h>
#include <stdlib.h>
#include "conway.h"
#include "terminal.h"
#include "wait.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

int main(void)
{
	printf("Program is starting...\n");
	
	char *cur_board = malloc(sizeof(char) * num_cells_board(BOARD_WIDTH, BOARD_HEIGHT));
	char *next_board = malloc(sizeof(char) * num_cells_board(BOARD_WIDTH, BOARD_HEIGHT));

	initialise_board(cur_board, BOARD_WIDTH, BOARD_HEIGHT);
	initialise_board(next_board, BOARD_WIDTH, BOARD_HEIGHT);
	
	while (1)
	{
		print_barrier
		wait(500);
		print_board(cur_board, BOARD_WIDTH, BOARD_HEIGHT);
		increment_boardstate(cur_board, next_board, BOARD_WIDTH, BOARD_HEIGHT);
		copy_board(next_board, cur_board, BOARD_WIDTH, BOARD_HEIGHT);
	}
	
	free(cur_board);
	free(next_board);
	return 0;
}
