#include "game.h"
#include<stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    if (!initializeGame()) {
        printf("Failed to initialize the game!\n");
        return -1;
    }

    runGame();

    shutdownGame();
    return 0;
}
