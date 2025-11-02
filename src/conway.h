#define CELL_ALIVE 0b10000000
#define CELLINDEX_X_INVALID -1
#define CELLINDEX_Y_INVALID -2

// initialises board with all 0's
void initialise_board(char *board, int width, int height);

// increments the board state to the next board state
void increment_boardstate(char *curr_board, char *next_board, int width, int height);

// gets the number of cells in board
int num_cells_board(int width, int height);

// will update the given board as follows:
// 	deactivates cell
// 	decrement neighbour cell counts if cell was previously alive
// TODO - not implemented
void set_cell_dead(int index, char *board, int width, int height);

// will update the given board as follows
// 	activates cell
// 	increment neighbour cell counts if cell was previously dead
// TODO - not implemented
void set_cell_alive(int index, char *board, int width, int height);

// returns 1 if cell is currently set as alive
// returns 0 otherwise
int cell_is_alive(char *board, int index);

// returns the number of neighbours given cell has
int num_neighbours(char cell);

// return the index of the cell for the board
// returns negative number for error
int cell_index(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

// replicates the source board into the destination board
void copy_board(char *src_board, char *dest_board, int width, int height);

// increments a neighbour
void increment_neighbour(int index, int neighbour_relative_index, char *board, int width, int height);

// decrements_neighbour
void decrement_neighbour(int index, int neighbour_relative_index, char *board, int width, int height)
