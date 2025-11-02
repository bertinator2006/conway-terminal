#include "conway.h"

// 
int num_cells_board(int width, int height)
{
	return width * height;
}


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
int cell_is_alive(char *board, int index)
{
	if (i < 0)
	{
		return 0;
	}
	return board[i] & CELL_ALIVE;
}

// does not actually count the number of alive neighbours
// checks the last 4 bits in given char
int num_neighbours(char cell)
{
	return cell & 0x0f;
}

//
void set_cell_alive(int index, char *board, int width, int height)
{
	if (index < 0 || index > num_cells_board(width, height))
	{
		return;
	}
	
	if(cell_is_alive(board, index))
	{
		return;
	}

	board[i] = board[i] | CELL_ALIVE;
	int xpos = index % width;
    int ypos = index / width;

	int offset_checkmap[9][2] = {
		{-1, -1}, { 0, -1}, { 1, -1},
		{-1,  0}, { 0,  0}, { 1,  0},
		{-1, -1}, { 0, -1}, { 1, -1}
	}

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

// 
void copy_board(char *src_board, char *dest_board, int width, int height)
{
	int num_cells = num_cell_board(width, height);
	for (int i = 0; i < num_cells; i++)
	{
		dest_board[i] = src_board[i];
	}
}

