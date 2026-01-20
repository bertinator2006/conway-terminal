#ifndef CONWAY_H
#define CONWAY_H

#include <stdbool.h>
#include <stdint.h>

#define X_OUT_BOUNDS -1
#define Y_OUT_BOUNDS -2
#define CELL_EMPTY 0
#define SUCCESS 0

typedef struct Board {
	uint8_t *grid;
	uint8_t *next_grid;
	int width;
	int height;
} Board;

// creates empty board
// Needs to be destroyed at end of program with destroy_board
Board create_empty_board(int width, int height);

// moves the board_state ahead by one
void increment_state(Board board);

// returns true if cell is alive
// false if cell is dead
bool cell_alive(Board board, int x, int y);

// Needs to be called for every init_board called
void destroy_board(Board board);

// Gets a board from a file
Board create_board_from_file(const char *board_file_name);

// Creates a board from a string
Board create_board_from_string(int width, int height, char string[]);

#endif
