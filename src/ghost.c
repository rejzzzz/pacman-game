#include "ghost.h"
#include "graphics.h"
#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include "maze.h"
#include <string.h>  // For memset

#include <stdbool.h>

#define ROWS 32
#define COLS 40

#define MAX_PATH_LENGTH 1000 // Arbitrary value for max path length

typedef struct {
    int x, y;
} Point;

Point path[ROWS * COLS]; // Maximum possible path length
int pathLength = 0;
bool visited[ROWS][COLS]; // Visited cells
//maze[ROWS][COLS]; // Your maze definition

bool dfs(int maze[ROWS][COLS], int x, int y, int targetX, int targetY) {
    // Check bounds and whether the current cell is already visited or a wall
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS || visited[x][y] || maze[x][y] != 0) {
        return false;
    }

    // Mark the current cell as visited
    visited[x][y] = true;

    // Add the current position to the path
    path[pathLength].x = x;
    path[pathLength].y = y;
    pathLength++;

    // Check if the current position is the target (Pac-Man's position)
    if (x == targetX && y == targetY) {
        return true; // Path found
    }

    // Explore neighboring cells (up, down, left, right)
    if (dfs(maze, x - 1, y, targetX, targetY)) return true; // Up
    if (dfs(maze, x + 1, y, targetX, targetY)) return true; // Down
    if (dfs(maze, x, y - 1, targetX, targetY)) return true; // Left
    if (dfs(maze, x, y + 1, targetX, targetY)) return true; // Right

    // Backtrack if no path is found
    pathLength--;
    visited[x][y] = false; // Mark as unvisited so other paths can explore this cell

    // Debugging output to track the backtracking
    //printf("Backtracking from: (%d, %d)\n", x, y);
    return false;
}



void moveGhost(Entity* ghost, Entity* pacman, int maze[ROWS][COLS]) {
    static Uint32 lastMoveTime = 0; // For timing movement
    
    Uint32 currentTime = SDL_GetTicks();

    
    if (currentTime - lastMoveTime >= 500) //every 0.5 secs the ghost moves
    {
        // Reset visited array and path length
        memset(visited, false, sizeof(visited));
        pathLength = 0;

        // Start DFS from the ghost's position to find a path to Pac-Man
        if (dfs(maze, ghost->pos.x, ghost->pos.y, pacman->pos.x, pacman->pos.y)) {
            // Move ghost to the next position in the path towards Pac-Man
            if (pathLength > 1) { // Check if there is at least one step to move
                ghost->pos.x = path[1].x; // Move to the next position in the path
                ghost->pos.y = path[1].y;
            }else {
                printf("Ghost reached Pac-Man!\n");
            }
        }else {
            printf("No valid path found for ghost from (%d, %d) to (%d, %d)\n", ghost->pos.x, ghost->pos.y, pacman->pos.x, pacman->pos.y);
        }

        // Update the last move time
        lastMoveTime = currentTime;
    }
    //for debugging
    //printf("Ghost Position: (%d, %d) Pac-Man Position: (%d, %d)\n", ghost->pos.x, ghost->pos.y, pacman->pos.x, pacman->pos.y);

    
}


void renderGhost(Entity ghost) {
    renderEntity(ghost, GHOST);
}
