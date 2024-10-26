#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>


typedef struct {
    int x; 
    int y; 
} Position;

typedef struct {
    Position pos;  
    int direction; 
    int speed;     
} Entity;

#endif  





