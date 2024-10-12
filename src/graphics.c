#include "graphics.h"
#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include "maze.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ROWS 32
#define COLS 40
#define TILE_SIZE_X (WINDOW_WIDTH / COLS)
#define TILE_SIZE_Y (WINDOW_HEIGHT / ROWS)
#define TILE_SIZE (WINDOW_HEIGHT / ROWS)

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void shutdownSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);
}

void updateScreen() {
    SDL_RenderPresent(renderer);
}

void renderTile(int row, int col, int type) {
    SDL_Rect tile = {
        col * TILE_SIZE_X,  // Adjust X position
        row * TILE_SIZE_Y,  // Adjust Y position
        TILE_SIZE_X,        // Tile width
        TILE_SIZE_Y         // Tile height
    };

    switch (type) {
        case WALL:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue for walls
            break;
        case PATH:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black for paths
            break;
        // Add cases for PACMAN and GHOST if needed
    }

    SDL_RenderFillRect(renderer, &tile);
}


void renderEntity(Entity entity, int type) {
    // Define the rectangle based on the entity's position and the calculated tile size
    SDL_Rect tile = {
        entity.pos.y * TILE_SIZE_X,  // Use TILE_SIZE_X for width
        entity.pos.x * TILE_SIZE_Y,  // Use TILE_SIZE_Y for height
        TILE_SIZE_X,                  // Width of the tile
        TILE_SIZE_Y                   // Height of the tile
    };

    // Set color based on the entity type
    if (type == PACMAN) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow for Pac-Man
    } else if (type == GHOST) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red for Ghost
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Default to black for any other entity
    }

    // Render the rectangle
    SDL_RenderFillRect(renderer, &tile);
}

