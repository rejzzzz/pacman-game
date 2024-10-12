// if dfs is not working so i bfs, 
// change the file name in Makefile from ghost.c to ghost-bfs.c 
#include <stdio.h>
#include <stdbool.h>
#include <string.h> // For memset
#include "entity.h"
#define ROWS 32
#define COLS 40
#define MAX_QUEUE_SIZE (ROWS * COLS) // Maximum number of points in the queue
#include "ghost.h"
#include "graphics.h"

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pos;
    int dist;
} Node;

// Queue implementation
typedef struct {
    Node nodes[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

bool isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

bool enqueue(Queue* q, Node n) {
    if (q->rear == MAX_QUEUE_SIZE) {
        return false; // Queue is full
    }
    q->nodes[q->rear++] = n;
    return true;
}

bool dequeue(Queue* q, Node* n) {
    if (isQueueEmpty(q)) {
        return false; // Queue is empty
    }
    *n = q->nodes[q->front++];
    return true;
}

Point path[ROWS * COLS];
int pathLength = 0;
bool visited[ROWS][COLS]; // Visited cells

bool bfs(int maze[ROWS][COLS], int startX, int startY, int targetX, int targetY) {
    Queue q;
    initQueue(&q);

    // Directions for movement (up, down, left, right)
    int dirX[] = {-1, 1, 0, 0};
    int dirY[] = {0, 0, -1, 1};

    // Reset visited array
    memset(visited, false, sizeof(visited));

    // Start BFS by enqueuing the starting position
    Node start = {{startX, startY}, 0};
    enqueue(&q, start);
    visited[startX][startY] = true;

    while (!isQueueEmpty(&q)) {
        Node node;
        dequeue(&q, &node);

        int x = node.pos.x;
        int y = node.pos.y;

        // Add the current position to the path
        path[pathLength].x = x;
        path[pathLength].y = y;
        pathLength++;

        // Check if we reached the target
        if (x == targetX && y == targetY) {
            return true; // Path found
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int newX = x + dirX[i];
            int newY = y + dirY[i];

            // Check bounds and walls
            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS && maze[newX][newY] == 0 && !visited[newX][newY]) {
                Node neighbor = {{newX, newY}, node.dist + 1};
                enqueue(&q, neighbor);
                visited[newX][newY] = true;
            }
        }
    }

    return false; // No path found
}

void moveGhost(Entity* ghost, Entity* pacman, int maze[ROWS][COLS]) {
    static Uint32 lastMoveTime = 0; // For timing movement
    
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastMoveTime >= 500) //every 0.5 secs the ghost moves
    {
        // Reset visited array and path length
        memset(visited, false, sizeof(visited));
        pathLength = 0;

        // Start BFS from the ghost's position to find a path to Pac-Man
        if (bfs(maze, ghost->pos.x, ghost->pos.y, pacman->pos.x, pacman->pos.y)) {
            // Move ghost to the next position in the path towards Pac-Man
            if (pathLength > 1) {
                ghost->pos.x = path[1].x; // Move to the next position in the path
                ghost->pos.y = path[1].y;
            } else {
                printf("Ghost reached Pac-Man!\n");
            }
        } else {
            printf("No valid path found for ghost from (%d, %d) to (%d, %d)\n", ghost->pos.x, ghost->pos.y, pacman->pos.x, pacman->pos.y);
        }

        lastMoveTime = currentTime;
    }

    printf("Ghost Position: (%d, %d) Pac-Man Position: (%d, %d)\n", ghost->pos.x, ghost->pos.y, pacman->pos.x, pacman->pos.y);
}

void renderGhost(Entity ghost) {
    renderEntity(ghost, GHOST);
}