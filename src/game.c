#include "game.h"
#include "maze.h"
#include "pacman.h"
#include "ghost.h"
#include "graphics.h"
#include <stdio.h>
#include "config.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

Entity pacman;
Entity ghost;

int initializeGame()
{
    if (!initializeSDL())
    {
        return 0;
    }

    pacman = (Entity){{19, 19}, 0, 1};
    ghost = (Entity){{19, 3}, 0, 1};

    return 1;
}

void runGame()
{
    int quit = 0;
    SDL_Event e;
    Uint32 lastGhostMoveTime = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            movePacman(&e, &pacman, maze);
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastGhostMoveTime >= ghost_movement_interval)
        {
            moveGhost(&ghost, &pacman, maze); // Move ghost
            lastGhostMoveTime = currentTime;  // Update last movement time
        }

        // Rendering
        clearScreen();
        renderMaze();
        renderPacman(pacman);
        renderGhost(ghost);
        // renderGhost(ghost);
        updateScreen();

        SDL_Delay(16); // Roughly 60 frames per second
    }
}

void shutdownGame()
{
    shutdownSDL();
}
