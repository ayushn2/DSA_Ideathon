
#ifndef ASTAR_H
#define ASTAR_H

#include <stdbool.h>

// Structure to represent a cell on the chessboard
typedef struct Cell {
    int x, y; // x and y coordinates of the cell
    int f, g, h; // A* algorithm parameters
    struct Cell *parent; // Pointer to the parent cell
} Cell;

// Function to find the shortest path using A* algorithm
int findPathAStar(int start_x, int start_y, int end_x, int end_y);

#endif /* ASTAR_H */