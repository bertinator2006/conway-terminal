#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "conway.h"

#define MAX_SIZE 4000
#define SET_STATE_ALIVE 1
#define SET_STATE_DEAD 0
#define MODE_DECREMENT -1
#define MODE_INCREMENT 1
#define ALIVE_CELL 0b10000000
#define DEAD_CELL 0b00000000
#define STATE_ALIVE 1
#define STATE_DEAD 0
#define FILE_CHAR_DEAD '0'

static void set_cell_state_buffer(Board board, int index, bool state);
static char choose_init_cell(char byte);
static void update_neighbour_buffer(Board board, int index, int relative_index, int update_mode);
static int num_cells(Board board);
static int num_neighbours(Board board, int index);
static int is_cell_alive(Board board, int index);

Board create_board_from_string(int width, int height, char string[])
{
	// I kinda copilotted this one, hope it works lol
	Board board = init_empty_board(width, height);
	int cell_count = num_cells(board);

	for (int i = 0; i < cell_count; i++)
	{
		board.next_grid[i] = choose_init_cell(string[i]);
		bool set_state = (board.next_grid[i] >> 7) & STATE_ALIVE;
		set_cell_state_buffer(board, i, set_state);
	}

	memcpy(board.grid, board.next_grid, cell_count);
	return board;
}

Board create_board_from_file(const char *board_file_name)
{
	Board board;
	FILE *board_file = fopen(board_file_name, "r");
	if (board_file == NULL)
	{
		fprintf(stderr, "Error opening file: %s\n", board_file_name);
		exit(EXIT_FAILURE);
	}

	char buffer[MAX_SIZE] = {0};

	char *result = fgets(buffer, MAX_SIZE, board_file);
	if (result == NULL)
	{
		fprintf(stderr, "Error reading the file.\n");
		exit(EXIT_FAILURE);
	}

	int width = 0;
	int height = 0;

	int i;
	while (fgets(buffer, MAX_SIZE, board_file) != NULL)
	{
		i = strcspn(buffer, "\n");

		if (width == 0)
		{
			width = i;
		}
		else if (i != width)
		{
			fprintf(stderr, "File has inconsistent width.\n");
			exit(1);
		}

		height++;
	}

	init_empty_board(width, height);
	int cell_count = num_cells(board);

	fseek(board_file, 0, SEEK_SET);
	int counter = 0;
	while (fgets(buffer, MAX_SIZE, board_file) != NULL)
	{
		for (int i = 0; i < width; i++)
		{
			board.next_grid[counter] = choose_init_cell(buffer[i]);
			bool set_state = (board.next_grid[counter] >> 7) & STATE_ALIVE;
			set_cell_state_buffer(board, counter, set_state);
			counter++;
		}
	}

	memcpy(board.grid, board.next_grid, cell_count);
	return board;
}

static char choose_init_cell(char byte)
{
	if (byte == '0')
	{
		return DEAD_CELL;
	}
	return ALIVE_CELL;
}

void increment_state(Board board)
{
	for (int i = 0; i < num_cells(board); i++)
	{
		int neighbours = num_neighbours(board, i);
		int cell_alive = is_cell_alive(board, i);
		if (cell_alive && neighbours < 2)
		{
			// printf("cell_alive && neighbours < 2\n");
			set_cell_state_buffer(board, i, STATE_DEAD);
		}
		else if (!cell_alive && neighbours == 3)
		{
			// printf("!cell_alive && neighbours == 3\n");
			set_cell_state_buffer(board, i, STATE_ALIVE);
		}
		else if (cell_alive && neighbours >= 4)
		{
			// printf("cell_alive && neighbours >= 4\n");
			set_cell_state_buffer(board, i, STATE_DEAD);
		}
	}

	memcpy(board.grid, board.next_grid, num_cells(board));
}

static void set_cell_state_buffer(Board board, int index, bool state)
{
	if (state == STATE_ALIVE)
	{
		board.next_grid[index] |= ALIVE_CELL;
	}
	else if (state == STATE_DEAD)
	{
		board.next_grid[index] &= ~ALIVE_CELL;
	}

	int offset_setmap[8][2] = {
		{-1, -1}, { 0, -1}, { 1, -1},
		{-1,  0}, { 1,  0},
		{-1,  1}, { 0,  1}, { 1,  1}
	};

	int x = index % board.width;
	int y = index / board.width;
	int offset_x;
	int offset_y;
	for (int i = 0; i < 8; i++)
	{
		offset_x = offset_setmap[i][0];
		offset_y = offset_setmap[i][1];
		x += offset_x;
		y += offset_y;
		bool within_bounds_x = (x >= 0 && x <= board.width);
		bool within_bounds_y = (y >= 0 && y <= board.width);
		bool within_bounds = (within_bounds_x  && within_bounds_y);

		if (within_bounds && state == SET_STATE_ALIVE)
		{
			update_neighbour_buffer(board, index, i, MODE_DECREMENT);
		}
		else if (within_bounds && state == SET_STATE_DEAD)
		{
			update_neighbour_buffer(board, index, i, MODE_DECREMENT);
		}
	}
	return;
}

static void update_neighbour_buffer(Board board, int index, int relative_index, int update_mode)
{
	if (index < 0) { return; }

	int offset_setmap[8] = {
		-board.width - 1,
		-board.width,
		-board.width + 1,
		-1,
		1,
		board.width - 1,
		board.width,
		board.width + 1
	};

	int true_index = offset_setmap[relative_index] + index;
	int delta = (update_mode == MODE_INCREMENT) ? 1 : -1;
	if (delta > 0) {
		board.next_grid[true_index] += delta;
	} else
	{
		board.next_grid[true_index] += (board.next_grid[true_index] & ~ALIVE_CELL) ? delta : 0;
	}
}

static int num_cells(Board board)
{
	return board.width * board.height;
}

static int num_neighbours(Board board, int index)
{
	return board.grid[index] & (~ALIVE_CELL);
}

static int is_cell_alive(Board board, int index)
{
	return board.grid[index] & ALIVE_CELL;
}
