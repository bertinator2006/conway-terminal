#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "terminal.h"
#include "conway.h"

#define WIDTH 20
#define HEIGHT 20

static Board input_from_terminal();

int main(int argc, char *argv[])
{
	Board board;
	if (argc < 2)
	{
		printf("Creating board from player inputs...\n");
		board = input_from_terminal();
	} else if (argc == 2)
	{
		printf("Loading board from file...\n");
		// Board board = init_empty_board(WIDTH, HEIGHT);
        // // TODO - create dummy test board
		board = create_board_from_file(argv[1]);
	} else 
	{
		fprintf(stderr, "Usage:\n\t./program [file]\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Starting game...\n");

        while (true)
        {
			print_board(board);
			increment_state(board);
			fgets(NULL, 0, stdin);
        }

	destroy_board(board);
	return 0;
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