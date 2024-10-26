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

#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

// Structure for position (x, y coordinates)
typedef struct {
    int x; // X position (Column in the maze)
    int y; // Y position (Row in the maze)
} Position;

// Structure for an entity (Pac-Man, Ghosts, etc.)
typedef struct {
    Position pos;  // Entity's current position in the maze
    int direction; // Movement direction (could be defined as an enum for directions)
    int speed;     // Speed of the entity's movement
} Entity;



#endif  // ENTITY_H
