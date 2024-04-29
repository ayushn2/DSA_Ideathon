#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "utilities.h"

#define SIZE 8 // Chessboard size

// Structure to represent a cell on the chessboard
typedef struct Cell {
    int x, y; // x and y coordinates of the cell
    int f, g, h; // A* algorithm parameters
    struct Cell *parent; // Pointer to the parent cell
} Cell;


// Function to check if a cell is blocked (already visited)
bool isBlocked(int x, int y, bool **visited) {
    return (visited[x][y]);
}

// Function to calculate the heuristic (Manhattan distance) between two cells
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Function to find the shortest path using A* algorithm
int findPathAStar(int start_x, int start_y, int end_x, int end_y) {
    // Initialize the chessboard
    bool **visited = (bool **)malloc(SIZE * sizeof(bool *));
    for (int i = 0; i < SIZE; i++) {
        visited[i] = (bool *)malloc(SIZE * sizeof(bool));
        for (int j = 0; j < SIZE; j++) {
            visited[i][j] = false;
        }
    }

    // Define possible moves for a knight
    int dx[] = {-2, -1, 1, 2, -2, -1, 1, 2};
    int dy[] = {-1, -2, -2, -1, 1, 2, 2, 1};

    // Initialize the start and end cells
    Cell start = {start_x, start_y, 0, 0, 0, NULL};
    Cell end = {end_x, end_y, 0, 0, 0, NULL};

    // Create a list to store open cells
    Cell *openList = NULL;
    Cell *closedList = NULL;

    // Add the start cell to the open list
    openList = &start;

    // Loop until the open list is empty
    while (openList != NULL) {
        // Find the cell with the lowest 'f' value in the open list
        Cell *current = openList;
        Cell *temp = openList->parent;
        while (temp != NULL) {
            current = temp;
            temp = temp->parent;
        }

        // Remove the current cell from the open list
        if (current == openList) {
            openList = openList->parent;
        } else {
            Cell *tempOpen = openList;
            while (tempOpen->parent != current) {
                tempOpen = tempOpen->parent;
            }
            tempOpen->parent = current->parent;
        }
        
        // Add the current cell to the closed list
        current->parent = closedList;
        closedList = current;

        // If the current cell is the end cell, stop the search
        if (current->x == end.x && current->y == end.y) {
            // Free memory
            for (int i = 0; i < SIZE; i++) {
                free(visited[i]);
            }
            free(visited);
            // Return the length of the path
            return current->g;
        }

        // Generate all possible moves from the current cell
        for (int i = 0; i < 8; i++) {
            int new_x = current->x + dx[i];
            int new_y = current->y + dy[i];

            // Check if the new position is valid and not blocked
            if (isValid(new_x, new_y) && !isBlocked(new_x, new_y, visited)) {
                // Create a new cell for the move
                Cell *newCell = (Cell *)malloc(sizeof(Cell));
                newCell->x = new_x;
                newCell->y = new_y;
                newCell->g = current->g + 1;
                newCell->h = heuristic(new_x, new_y, end.x, end.y);
                newCell->f = newCell->g + newCell->h;
                newCell->parent = current;

                // Add the new cell to the open list
                newCell->parent = openList;
                openList = newCell;

                // Mark the new position as visited
                visited[new_x][new_y] = true;
            }
        }
    }

    // Free memory
    for (int i = 0; i < SIZE; i++) {
        free(visited[i]);
    }
    free(visited);
    
    // If no path is found, return -1
    return -1;
}
