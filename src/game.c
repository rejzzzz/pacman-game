#include "game.h"
#include "maze.h"
#include "pacman.h"
#include "ghost.h"
#include "graphics.h"
#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>

Entity pacman;
Entity ghost;

int initializeGame() {
    if (!initializeSDL()) {
        return 0;
    }

    pacman = (Entity) {{1, 1}, 0, 1};  // Pac-Man at (1, 1), direction 0, speed 1
    ghost = (Entity) {{19, 3}, 0, 1};  // Ghost at (10, 5), direction 0, speed 1


    return 1;
}

void runGame() {
    int quit = 0;
    SDL_Event e;
    Uint32 lastGhostMoveTime = 0;  // Store last ghost movement time

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            movePacman(&e, &pacman, maze);
            
        }
    
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastGhostMoveTime >= 500) 
    {  //every 0.5 secs the ghost moves
        moveGhost(&ghost, &pacman, maze);  // Move ghost
        lastGhostMoveTime = currentTime;   // Update last movement time
    }

        

        // Rendering
        clearScreen();
        renderMaze();
        renderPacman(pacman);
        renderGhost(ghost);
        updateScreen();

        SDL_Delay(16);  // Roughly 60 frames per second
    }
}

void shutdownGame() {
    shutdownSDL();
}
