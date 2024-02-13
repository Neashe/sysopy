#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <number of threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n_threads = atoi(argv[1]);
    if (n_threads <= 0){
        printf("Number of threads must be positive\n");
        exit(EXIT_FAILURE);
    }

	srand(time(NULL));
	setlocale(LC_CTYPE, "");
	initscr(); // Start curses mode

	char *foreground = create_grid();
	char *background = create_grid();
	char *tmp;

	init_grid(foreground);
    init_threads(n_threads,foreground, background);

	while (true)
	{
		draw_grid(foreground);
		usleep(500 * 1000);

		// Step simulation
		update_grid();
		tmp = foreground;
		foreground = background;
		background = tmp;
	}

	endwin(); // End curses mode
	destroy_grid(foreground);
	destroy_grid(background);
    cleanup_threads();


	return 0;
}
