#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "conway.h"

#define MAX_SIZE 4000
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
Board create_empty_board(int width, int height);
static char calc_neighbour_count(Board board, int index);
static void init_board_neighbours(Board board);

static void debug(void) {
	printf("Here\n");
}

bool cell_alive(Board board, int x, int y)
{
	return board.grid[y * board.width + x] & ALIVE_CELL;
}

Board create_board_from_string(int width, int height, char string[])
{
	// I kinda copilotted this one, hope it works lol
	Board board = create_empty_board(width, height);
	int cell_count = num_cells(board);

	for (int i = 0; i < cell_count; i++)
	{
		board.next_grid[i] = choose_init_cell(string[i]);
		bool set_state = (board.next_grid[i] >> 7) & STATE_ALIVE;
		set_cell_state_buffer(board, i, set_state);
	}

	init_board_neighbours(board);

	memcpy(board.grid, board.next_grid, cell_count);
	return board;
}

Board create_board_from_file(const char *board_file_name)
{
	FILE *board_file = fopen(board_file_name, "r");
	if (board_file == NULL)
	{
		fprintf(stderr, "Error opening file: %s\n", board_file_name);
		exit(EXIT_FAILURE);
	}

	char buffer[MAX_SIZE] = {0};

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

	Board board = create_empty_board(width, height);
	int cell_count = num_cells(board);

	fseek(board_file, 0, SEEK_SET);
	int counter = 0;
	while (fgets(buffer, MAX_SIZE, board_file) != NULL)
	{
		for (int i = 0; i < width; i++)
		{
			if (buffer[i] == '1')
			{
				board.next_grid[counter] |= ALIVE_CELL;
			}
			else
			{
				board.next_grid[counter] &= (~ALIVE_CELL);
			}
			// board.next_grid[counter] = choose_init_cell(buffer[i]);
			bool set_state = board.next_grid[counter] & ALIVE_CELL;
			set_cell_state_buffer(board, counter, set_state);
			counter++;
		}
	}

	memcpy(board.grid, board.next_grid, cell_count * sizeof(char));
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

// TODO - this is not working at all and empties the board
static void init_board_neighbours(Board board)
{

	int cell_count = num_cells(board);
	for (int i = 0; i < cell_count; i++)
	{
		char alive = board.grid[i] & ALIVE_CELL;
		board.next_grid[i] = alive | calc_neighbour_count(board, i);
	}

	memcpy(board.grid, board.next_grid, 1);
}

static char calc_neighbour_count(Board board, int index)
{
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

	int boundary_check[8][2] = {
		{-1, -1}, { 0, -1}, { 1, -1},
		{-1,  0}, { 1,  0},
		{-1,  1}, { 0,  1}, { 1,  1}
	};

	char count = 0;
	int tx = index % board.width;
	int ty = index / board.width;

	for (int i = 0; i < 8; i++)
	{
		int x = tx + boundary_check[i][0];
		int y = ty + boundary_check[i][1];

		bool within_bounds_x = (x >= 0 && x <= board.width);
		bool within_bounds_y = (y >= 0 && y <= board.width);

		if (within_bounds_x  && within_bounds_y)
		{
			if (board.grid[index + offset_setmap[i]] & ALIVE_CELL)
			{
				count++;
			}
		}
	}

	return count;
}

void increment_state(Board board)
{
	for (int i = 0; i < num_cells(board); i++)
	{
		int neighbours = num_neighbours(board, i);
		int cell_alive = is_cell_alive(board, i);
		// if (cell_alive) {
		// 	printf("%d\n", neighbours)
		// }
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
	if (state == STATE_DEAD && !is_cell_alive(board, index)) return;
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
		{-1,  0},
		{ 1,  0},
		{-1,  1}, { 0,  1}, { 1,  1}
	};

	int tx = index % board.width;
	int ty = index / board.width;
	for (int i = 0; i < 8; i++)
	{
		int x = tx + offset_setmap[i][0];
		int y = ty + offset_setmap[i][1];
		bool within_bounds_x = (x >= 0 && x < board.width);
		bool within_bounds_y = (y >= 0 && y < board.height);
		bool within_bounds = (within_bounds_x  && within_bounds_y);

		if (within_bounds && state == STATE_ALIVE)
		{
			update_neighbour_buffer(board, index, i, MODE_INCREMENT);
		}
		else if (within_bounds && state == STATE_DEAD)
		{
			update_neighbour_buffer(board, index, i, MODE_DECREMENT);
		}
	}
	return;
}

static void update_neighbour_buffer(Board board, int index, int relative_index, int update_mode)
{
	if (index < 0)
	{
		printf("How did it fail this\n");
		return;
	}

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
	if (update_mode > 0)
	{
		// char before = board.next_grid[true_index];
		board.next_grid[true_index] += update_mode;
		// char after = board.next_grid[true_index];
		// printf("%02x -> %02x\n\n", before, after);
	}
	else
	{
		board.next_grid[true_index] += (board.next_grid[true_index] & (~ALIVE_CELL)) ? update_mode : 0;
	}
	// printf("This is the end of update_neighbour_buffer. %i is: %02x\n", true_index, board.next_grid[true_index]);

	// memcpy(board.grid, board.next_grid, num_cells(board) * sizeof(char));
	// printf("This is the end of update_neighbour_buffer. %i is: %02x\n", true_index, board.grid[true_index]);

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

Board create_empty_board(int width, int height)
{
    Board board;
    board.width = width;
    board.height = height;
    board.grid = malloc(num_cells(board) * sizeof(char));
    board.next_grid = malloc(num_cells(board) * sizeof(char));

    memset(board.grid, 0, num_cells(board) * sizeof(char));
    memcpy(board.next_grid, board.grid, num_cells(board) * sizeof(char));

    return board;
}

void destroy_board(Board board)
{
	free(board.grid);
	free(board.next_grid);
}
