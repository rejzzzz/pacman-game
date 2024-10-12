#include "pacman.h"
#include "graphics.h"
#include "maze.h"
#include <SDL2/SDL.h>



void movePacman(SDL_Event* e, Entity* pacman, int maze[ROWS][COLS]) {
    if (e->type == SDL_KEYDOWN) {
        int newX = pacman->pos.x;
        int newY = pacman->pos.y;

        switch (e->key.keysym.sym) {
            case SDLK_UP:    newX--; break;  // Move up
            case SDLK_DOWN:  newX++; break;  // Move down
            case SDLK_LEFT:  newY--; break;  // Move left
            case SDLK_RIGHT: newY++; break;  // Move right
        }

        // Check boundaries and wall collision
        if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS) {
            // Assuming 1 is a path and 0 is a wall in the maze array
            if (maze[newX][newY] != WALL) {  // Move only if the new position is not a wall
                pacman->pos.x = newX;
                pacman->pos.y = newY;
            }
        }
    }
    //printf("Pac-Man Position: (%d, %d)\n", pacman->pos.x, pacman->pos.y);

}




void renderPacman(Entity pacman) {
    renderEntity(pacman, PACMAN);
}
