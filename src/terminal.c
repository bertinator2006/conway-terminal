#include <stdio.h>
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

static Board input_from_terminal() {
	int width;
	int height;
	int throwaway;

	printf("\n");
	printf("Enter board width: ");
	scanf("%d", &width);
	while ((throwaway = getchar()) != '\n' && throwaway != EOF) {}

	printf("Enter board height: ");
	scanf("%d", &height);
	while ((throwaway = getchar()) != '\n' && throwaway != EOF) {}

	printf("Board size set to %dx%d\n", width, height);
	char *input = malloc(sizeof(char) * (height * width));

	int index = 0;
	printf("Enter board rows (use 0 for dead cells and 1 for alive cells and press enter to go to the next row):\n");
	for (int row = 0; row < height; row++)
	{
		printf("row %d: ", row);
		for (int col = 0; col < width; col++)
		{
			char cell;
			scanf(" %c", &cell);
			input[index++] = cell;
		}
		while ((throwaway = getchar()) != '\n' && throwaway != EOF) {}
	}

	return create_board_from_string(width, height, input);
}
