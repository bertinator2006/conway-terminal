# Making Conway's Game of Life in C
A zero-player game on a 2d grid of squares.
You decide the initial state of the program using a text file.
The program will eventually parse in your design.

Alive cells with less than 2 or more than 3 neighbours will die.
Dead cells with exactly 3 neighbours will come alive.

The program is currently implemented as a terminal only simulation where the timing is defined by the time parameter in code.
The program cosists of a main program and an abstracted form of the game of life that allows checking each cell and incrementing the board state.

All Rights Reserved
Usage of this program without prior consent from Aayush Poudel is strictly prohibited.
