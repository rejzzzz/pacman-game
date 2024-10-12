#ifndef GHOST_H
#define GHOST_H
#include "entity.h"
#include <SDL2/SDL.h>
#include"maze.h"

#include "game.h"

void moveGhost(Entity* ghost, Entity* pacman, int maze[ROWS][COLS]);
void renderGhost(Entity ghost);

#endif
