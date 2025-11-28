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
#define STATE_ALIVE 1
#define STATE_DEAD 0
#define FILE_CHAR_ALIVE '1'
#define FILE_CHAR_DEAD '0'

// internal helper functions only
int num_cells(Board board);
void increment_neighbour_buffer(Board board, int index, int relative_index);
void decrement_neighbour_buffer(Board board, int index, int relative_index);
void update_neighbour_buffer(Board board, int index, int relative_index, int update_mode);
void set_cell_dead_buffer(Board board, int index);
void set_cell_alive_buffer(Board board, int index);
void set_cell_state_buffer(Board board, int index, int set_state_mode);
int num_neighbours(Board board, int index);
bool is_cell_alive(Board board, int index);

// TODO
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
    for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++)
    {
        width++;
    }
    height++;

    while (fgets(buffer, MAX_SIZE, board_file) != NULL)
    {
        height++;
    }
    fseek(board_file, 0, SEEK_SET);

    board.width = width;
    board.height = height;

    board.grid = NULL;
    board.next_grid = NULL;

    // TODO: Remove this return statement after implementing the rest of the code properly
    return board;

    board.grid = malloc(num_cells(board));
    board.next_grid = malloc(num_cells(board));
}

void update_neighbour_buffer(Board board, int index, int relative_index, int update_mode)
{
	if (index < 0) return;

	int delta = update_mode == MODE_INCREMENT ? 1 : -1;
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
	board.next_grid[true_index] += delta;
}

void set_cell_state_buffer(Board board, int index, int state)
{
	if (state == SET_STATE_ALIVE)
	{
		board.next_grid[index] |= ALIVE_CELL;
	}
	else if (state == SET_STATE_DEAD)
	{
		board.next_grid[index] &= ~ALIVE_CELL;
	}
	else
	{
		return;
	}

	int offset_setmap[8][2] = {
		{-1, -1}, { 0, -1}, { 1, -1},
		{-1,  0}, { 1,  0},
		{-1,  1}, { 0,  1}, { 1,  1}
	};

	int x = index % board.width;
	int y = index / board.width;
	uint8_t offset_x;
	uint8_t offset_y;
	for (int i = 0; i < 8; i++)
	{
		offset_x = offset_setmap[i][0];
		offset_y = offset_setmap[i][1];
		x += offset_x;
		y += offset_y;
		bool within_bounds_x = x >= 0 && x <= board.width;
		bool within_bounds_y = y >= 0 && y <= board.width;
		bool within_bounds = within_bounds_x  && within_bounds_y;
		if (within_bounds && state == SET_STATE_ALIVE)
		{

			increment_neighbour_buffer(board, index, i);
		}
		else if (within_bounds && state == SET_STATE_DEAD)
		{

			decrement_neighbour_buffer(board, index, i);
		}
	}
	return;
}

void destroy_board(Board board)
{
	free(board.grid);
	free(board.next_grid);
}

int num_cells(Board board)
{
	return board.width * board.height;
}

bool is_cell_alive(Board board, int index)
{
	return board.grid[index] & ALIVE_CELL;
}

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

void set_cell_dead_buffer(Board board, int index)
{
	set_cell_state_buffer(board, index, STATE_DEAD);
}

void set_cell_alive_buffer(Board board, int index)
{
	set_cell_state_buffer(board, index, STATE_ALIVE);
}

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
		if (cell_alive &&neighbours < 2)
		{
			set_cell_dead_buffer(board, i);
		}
		else if (!cell_alive && neighbours == 3)
		{
			set_cell_alive_buffer(board, i);
		}
		else if (cell_alive && neighbours >= 4)
		{
			set_cell_dead_buffer(board, i);
		}
	}
}

bool cell_alive(Board board, int x, int y)
{
	if (x < 0 || x >= board.width || y < 0 || y >= board.height) return false;
	return board.grid[y * board.width + x] & ALIVE_CELL;
}

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
