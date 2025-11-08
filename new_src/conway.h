#ifndef CONWAY_H
#define CONWAY_H

#define X_OUT_BOUNDS -1
#define Y_OUT_BOUNDS -2
#define CELL_EMPTY 0
#define SUCCESS 0

typedef struct Board {
	char *grid;
	char *next_grid;
	int width;
	int height;
} Board;

// creates empty board
// Needs to be destroyed at end of program with destroy_board
Board init_empty_board(int width, int height);

// turns the cell in the given position on
void create_cell(Board board, int x, int y);

// deletes the cell in the given position
void delete_cell(Board board, int x, int y);

// initialises a board from a text file
// the format for this can be found in example_board.txt
Board init_board_from_file(char *file_name);

// moves the board_state ahead by one
void increment_state(Board board);

// checks if the cell at given position is alive
// returns CELL_ALIVE if cell is alive
// returns CELL_DEAD if cell is dead
// returns negative numbers for errors
int cell_state(Board board, int x, int y);


// Needs to be called for every init_board called
void free_board(Board board);

#endif
