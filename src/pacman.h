#ifndef PACMAN_H
#define PACMAN_H
#include "entity.h"
#include "game.h"
#include "maze.h"
#include <SDL2/SDL.h>


void movePacman(SDL_Event* e, Entity* pacman, int maze[ROWS][COLS]);
void renderPacman(Entity pacman);

#endif
