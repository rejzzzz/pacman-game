#ifndef MAZE_H
#define MAZE_H
#include <SDL2/SDL.h>


#define ROWS 32
#define COLS 40

extern int maze[ROWS][COLS];
#define CELL_SIZE (COLS / ROWS)

void renderMaze();

#endif
