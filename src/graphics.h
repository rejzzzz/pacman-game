#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "game.h"


#define WALL 1
#define PATH 0
#define PACMAN 2
#define GHOST 3
#include "entity.h"
#include <SDL2/SDL.h>

int initializeSDL();
void shutdownSDL();
void clearScreen();
void updateScreen();
void renderTile(int row, int col, int type);
void renderEntity(Entity entity, int type);
//SDL_Texture* loadTexture(const char* path);

extern SDL_Renderer* renderer;

#endif
