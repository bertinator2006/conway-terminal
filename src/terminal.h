#ifndef TERMINAL_H
#define TERMINAL_H

#include "conway.h"

void print_board(Board board);
void info_board(Board board);
void print_separator(Board board);
Board input_from_terminal();
void print_neighbours(Board board);

#endif
