#include <stdio.h>
#include "terminal.h"
#include "conway.h"

void print_board(char *board, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (cell_is_alive(board, cell_index(x, y, width, height)))
            {
                printf('[]'); // Alive cell
            }
            else
            {
                printf('  '); // Dead cell
            }
        }
        putchar('\n');
    }
}


void print_barrier(unsigned int width)
{
    for (unsigned int i = 0; i < width*2; i++)
    {
        putchar('=');
    }
    putchar('\n');
}