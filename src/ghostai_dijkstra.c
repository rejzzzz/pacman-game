#include "ghost.h"
#include "graphics.h"
#include <stdio.h>
#include "config.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "maze.h"
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define ROWS 32
#define COLS 40
#define INF INT_MAX


typedef struct {
    int x, y;
} Point;

typedef struct {
    int distance;
    Point prev;
    bool visited;
} Node;

typedef struct {
    Point points[ROWS * COLS];
    int front;
    int rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    return q->front == -1;
}

// Add point to queue
void enqueue(Queue* q, Point p) {
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->points[q->rear] = p;
}

// Remove and return point from queue
Point dequeue(Queue* q) {
    Point p = q->points[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return p;
}

// Get distance between two points
int getDistance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Check if point is valid
bool isValid(int x, int y, int maze[ROWS][COLS]) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] != 1;
}

// Direction arrays for possible movements
const int dx[] = {-1, 1, 0, 0};  // up, down, left, right
const int dy[] = {0, 0, -1, 1};

// Implementation of Dijkstra's algorithm with some improvements
Point* findPath(int maze[ROWS][COLS], Point start, Point target, int* pathLength) {
    Node nodes[ROWS][COLS];
    Point* path = malloc(ROWS * COLS * sizeof(Point));
    *pathLength = 0;

    // Initialize nodes
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            nodes[i][j].distance = INF;
            nodes[i][j].visited = false;
            nodes[i][j].prev = (Point){-1, -1};
        }
    }

    // Initialize start node
    nodes[start.x][start.y].distance = 0;
    
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, start);

    while (!isEmpty(&queue)) {
        Point current = dequeue(&queue);
        
        if (current.x == target.x && current.y == target.y) {
            break;
        }

        if (nodes[current.x][current.y].visited) {
            continue;
        }

        nodes[current.x][current.y].visited = true;

        // Check all possible directions
        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, maze) && !nodes[newX][newY].visited) {
                int newDist = nodes[current.x][current.y].distance + 1;
                
                if (newDist < nodes[newX][newY].distance) {
                    nodes[newX][newY].distance = newDist;
                    nodes[newX][newY].prev = current;
                    enqueue(&queue, (Point){newX, newY});
                }
            }
        }
    }

    // Reconstruct path
    Point current = target;
    while (current.x != -1 && current.y != -1) {
        path[*pathLength] = current;
        (*pathLength)++;
        current = nodes[current.x][current.y].prev;
    }

    // Reverse path
    for (int i = 0; i < *pathLength / 2; i++) {
        Point temp = path[i];
        path[i] = path[*pathLength - 1 - i];
        path[*pathLength - 1 - i] = temp;
    }

    return path;
}

void moveGhost(Entity* ghost, Entity* pacman, int maze[ROWS][COLS]) {
    static Uint32 lastMoveTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    
    // Move ghost every 250ms
    if (currentTime - lastMoveTime >= ghost_movement_interval) {
        // Set target to pacman's position
        Point target = {
            .x = pacman->pos.x,
            .y = pacman->pos.y
        };

        // Find path to target
        int pathLength;
        Point* path = findPath(maze, 
                             (Point){ghost->pos.x, ghost->pos.y},
                             target,
                             &pathLength);

        // Move ghost along path
        if (pathLength > 1) {
            ghost->pos.x = path[1].x;
            ghost->pos.y = path[1].y;
        }

        free(path);
        lastMoveTime = currentTime;
    }
}

void renderGhost(Entity ghost) {
    renderEntity(ghost, GHOST);
}