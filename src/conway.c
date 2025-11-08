#include <stdbool.h>
#include <stdlib.h>
#include "conway.h"

#define SET_STATE_ALIVE 1
#define SET_STATE_DEAD 0
#define MODE_DECREMENT -1
#define MODE_INCREMENT 1
#define ALIVE_CELL 0b10000000
#define STATE_ALIVE 1
#define STATE_DEAD 0


int num_cells(Board board);
void increment_neighbour_buffer(Board board, int index, int relative_index);
void decrement_neighbour_buffer(Board board, int index, int relative_index);
void update_neighbour_buffer(Board board, int index, int relative_index, int update_mode); // TODO
void set_cell_dead_buffer(Board board, int index);
void set_cell_alive_buffer(Board board, int index);
void set_cell_state_buffer(Board board, int index, int set_state_mode); // TODO
int num_neighbours(Board board, int index);
bool is_cell_alive(Board board, int index);

// Uses malloc
Board init_empty_board(int width, int height)
{
	Board board;
	board.width = width;
	board.height = height;
	board.grid = malloc(sizeof(char) * width * height);
	board.next_grid = malloc(sizeof(char) * width * height);

	int cell_count = num_cells(board);
	for (int i = 0; i < cell_count; i++)
	{
		board.grid[i] = CELL_EMPTY;
		board.next_grid[i] = CELL_EMPTY;
	}

	return board;
}

// TODO
void create_cell(Board board, int x, int y);

// TODO
void delete_cell(Board board, int x, int y);

// TODO
Board init_board_from_file(char *file_name);

// TODO
void increment_state(Board board)
{
	int width = board.width;
	int height = board.height;
	char *curr_board = board.grid;
	char *next_board = board.next_grid;
	for (int i = 0; i < num_cells(board); i++)
	{
		int neighbours = num_neighbours(board, i);
		int cell_alive = is_cell_alive(board, i);
		if (cell_alive &&neighbours < 2) {
			set_cell_dead_buffer(board, i);
		} else if (!cell_alive && neighbours == 3) {
			set_cell_alive_buffer(board, i);
		} else if (cell_alive && neighbours >= 4) {
			set_cell_dead(board, i);
		}
	}
}

// TODO
int cell_state(Board board, int x, int y);


// DONE
void set_cell_dead_buffer(Board board, int index)
{
	set_cell_state_buffer(board, index, STATE_DEAD);
}

// DONE
void set_cell_alive_buffer(Board board, int index)
{
	set_cell_state_buffer(board, index, STATE_ALIVE);
}

// DONE
int num_cells(Board board)
{
	return board.width * board.height;
}

// DONE
bool is_cell_alive(Board board, int index)
{
	return board.grid[index] & ALIVE_CELL;
}

// DONE
int num_neighbours(Board board, int index)
{
	return board.grid[index] & 0x0f;
}

void increment_neighbour_buffer(Board board, int index, int relative_index)
{
	update_neighbour_buffer(board, index, relative_index, MODE_INCREMENT);
}

void decrement_neighbour_buffer(Board board, int index, int relative_index)
{
	update_neighbour_buffer(board, index, relative_index, MODE_DECREMENT);
}

void update_neighbour_buffer(Board board, int index, int relative_index, int update_mode)
{

}
