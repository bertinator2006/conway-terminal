#include <stdio.h>
#include <stdlib.h>
#include "conway.h"
#include "terminal.h"

#define ALIVE_CELL 0b10000000 // Bit map which tells if a cell is alive or not

void print_cell(Board board, int x, int y)
{
	if (cell_alive(board, x, y))
	{
		printf("[]");
	}
	else
	{
		printf("--");
	}
}

void print_board(Board board)
{
	for (int i = 0; i < board.height; i++)
	{
		for (int j = 0; j < board.width; j++)
		{
			print_cell(board, j, i);
		}
		printf("\n");
	}
}

static char choose_character(bool alive)
{
	if (alive) return 'X';
	return ' ';
}

void print_neighbours(Board board)
{
	for (int i = 0; i < board.height; i++)
	{
		for (int j = 0; j < board.width; j++)
		{
			int neighbour_count = board.grid[j + i * board.width] & (~ALIVE_CELL);
			int alive = (board.grid[j + i * board.width] & ALIVE_CELL) != 0;
			printf(" %c%i", choose_character(alive), neighbour_count);
		}
		printf("\n");
	}
}

void info_board(Board board)
{
	printf("Width: %d\n", board.width);
	printf("Height: %d\n", board.height);
	print_board(board);
}

void print_separator(Board board)
{
	int width = board.width;
	for (int i = 0; i < width; i++)
	{
		printf("==");
	}
	printf("\n");
}

Board input_from_terminal()
{
	printf("Please enter the width and size of board.\n[width] [height]: ");

	int width;
	int height;
	scanf(" %d %d",&width, &height);
	if (width <= 0)
	{
		fprintf(stderr, "Invalid width.\n");
		exit(EXIT_FAILURE);
	}
	if (height <= 0)
	{
		fprintf(stderr, "Invalid height.\n");
		exit(EXIT_FAILURE);
	}

	Board board = create_empty_board(width, height);

	printf("Please enter coordinates of alive cells.\n");
	printf("Enter -1 -1 when done.\n");
	printf("[x] [y]: ");
	int x;
	int y;
	scanf(" %d %d", &x, &y);
	while (x != -1 && y != -1)
	{
		set_cell_as_alive(board, x, y);
		scanf(" %d %d", &x, &y);
	}

	return board;
}
