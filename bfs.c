#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "utilities.h"

#define SIZE 8

// Function to calculate the minimum moves by knight to reach final position
int findPathBFS(int start_x, int start_y, int end_x, int end_y) {
    int dx[] = {-2, -1, 1, 2, -2, -1, 1, 2};
    int dy[] = {-1, -2, -2, -1, 1, 2, 2, 1};
    
    // Initialize the visited array and queue for BFS traversal
    bool visited[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            visited[i][j] = false;
        }
    }
    
    // Initialize the queue for BFS traversal
    typedef struct {
        int x, y, dist;
    } Node;
    Node queue[SIZE * SIZE];
    int front = 0, rear = 0;
    
    // Enqueue the starting position
    queue[rear++] = (Node){start_x, start_y, 0};
    visited[start_x][start_y] = true;
    
    // Perform BFS traversal
    while (front < rear) {
        Node curr = queue[front++];
        
        // If we reach the target position, return the distance
        if (curr.x == end_x && curr.y == end_y)
            return curr.dist;
        
        // Otherwise, enqueue all possible next positions
        for (int i = 0; i < 8; i++) {
            int new_x = curr.x + dx[i];
            int new_y = curr.y + dy[i];
            
            if (isValid(new_x, new_y) && !visited[new_x][new_y]) {
                visited[new_x][new_y] = true;
                queue[rear++] = (Node){new_x, new_y, curr.dist + 1};
            }
        }
    }
    
    // If we couldn't reach the target position, return INT_MAX to indicate failure
    return INT_MAX;
}
