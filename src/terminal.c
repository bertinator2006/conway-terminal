#include <stdio.h>
#include "conway.h"
#include "terminal.h"

#define ALIVE_CELL 0b10000000

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

