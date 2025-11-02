#include <stdbool.h>
#include "conway.h"

// PRIVATE HELPER FUNCTIONS
void _update_neighbour(int index, int delta, int neighbour_relative_index, char *board, int width, int height);
int _set_cell_state(int index, bool set_alive, char *board, int width, int height);

// DONE
int num_cells_board(int width, int height)
{
	return width * height;
}

// DONE
void clear_board(char *board, int width, int height)
{
	for (int i = 0; i < num_cells_board(width, height); i++)
	{
		board[i] = 0;
	}
}

// DONE
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

// DONE
bool cell_is_alive(char *board, int index)
{
	if (i < 0)
	{
		return 0;
	}
	return board[i] & CELL_ALIVE;
}

// does not actually count the number of alive neighbours
// checks the last 4 bits in given char
// DONE
int num_neighbours(char cell)
{
	return cell & 0x0f;
}

// DONE
void set_cell_alive(int index, char *board, int width, int height)
{
	_set_cell_state(index, true, board, width, height);
}

// DONE
void set_cell_dead(int index, char *board, int width, int height)
{
	_set_cell_state(inde, false, board, width, height);
}

// DONE
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

// DONE
void copy_board(char *src_board, char *dest_board, int width, int height)
{
	int num_cells = num_cell_board(width, height);
	for (int i = 0; i < num_cells; i++)
	{
		dest_board[i] = src_board[i];
	}
}

// DONE
void increment_neighbour(int index, int neighbour_relative_index, char *board, int width, int height)
{
	_update_neighbour(index, 1, neighbour_relative_index, board, width, height);
}

// DONE
void decrement_neighbour(int index, int neighbour_relative_index, char *board, int width, int height)
{
	_update_neighbour(index, -1, neighbour_relative_index, board, width, height);
}

// NOT FOR PUBLIC USE
void _update_neighbour(int index, int delta, int neighbour_relative_index, char *board, int width, int height)
{
		if (i < 0) return;

	int offset_setmap[8] = {
		- width - 1,
		- width, 
		- width + 1,
		- 1,
		1,
		width - 1,
		width,
		width + 1
	};

	int neighbour_true_index = offset_setmap[neighbour_relative_index] + index;

	board[neighbour_true_index] += delta;
}

// NOT FOR PUBLIC USE
int _set_cell_state(int index, bool set_alive, char *board, int width, int height)
{
	if (index < 0 || index >= num_cells_board(width, height))
	{
		return;
	}
	
	if(cell_is_alive(board, index))
	{
		return;
	}

	board[index] = board[index] | CELL_ALIVE;
	int xpos = index % width;
    int ypos = index / width;

	// each pair is a pair for the x and y
	int offset_checkmap[8][2] = {
		{-1, -1}, { 0, -1}, { 1, -1},
		{-1,  0}, 			{ 1,  0},
		{-1,  1}, { 0,  1}, { 1,  1}
	};

	int offset_x;
	int offset_y;
	bool within_bounds_x;
	bool within_bounds_y;

	for (int i = 0; i < 8; i++)
	{
		offset_x = offset_checkmap[i][0];
		offset_y = offset_checkmap[i][1];
		within_bounds_x = (offset_x + xpos < width) && (offset_x + xpos >= 0);
		within_bounds_y = (offset_y + ypos < height) && (offset_y + ypos >= 0);
		if (within_bounds_x && within_bounds_y && set_alive)
		{
			increment_neighbour(index, i, board, width, height);
		}
		else if (within_bounds_x && within_bounds_y && !set_alive)
	}
}