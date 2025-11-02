#include "conway.h"

//
void initialise_board(char *board, int width, int height)
{
	for (int i = 0; i < num_cells_board(width, height); i++)
	{
		board[i] = 0;
	}
}

// increments the board state to the next board state
void increment_boardstate(char *curr_board, char *next_board, int width, int height)
{
	for (int i = 0; i < num_cells_board(width, height); i++)
	{
		int neighbours = num_neighbours(curr_board[i]);
		int cell_alive = cell_is_alive(curr_board, i);
		if (cell_alive &&neighbours < 2) {
			set_cell_dead(i, next_board, width, height);
		} else if (!cell_alive && neighbours == 3) {
			set_cell_alive(i, next_board, width, height);
		} else if (cell_alive && neighbours >= 4) {
			set_cell_dead(i, next_board, width, height);
		}
	}
}

//
int cell_is_alive(char *board, int i)
{
	return board[i] & CELL_ALIVE;
}

// does not actually count the number of alive neighbours
// checks the last 4 bits in given char
int num_neighbours(char cell)
{
	return cell & 0x0f;
}

//
void set_cell_alive(int i, char *board, int width, int height)
{
	if (i > num_cells_board(width, height))
		return;

	// check corner
	int x = i % width;
	int y = i / width;

	if (x >= width)
		return;

	if (y >= height)
		return;


	// TODO

}

//
int cell_index(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	if (x >= width)
	{
		return CELLINDEX_X_INVALID;
	}
	if (y >= height)
	{
		return CELLINDEX_Y_INVALID;
	}
	return x + y * width;
}
