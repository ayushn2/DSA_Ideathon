#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include "bfs.h"
#include "floydwarshall.h"
#include "astar.h"

#define SIZE 8

// Function to measure the execution time of a given algorithm
double measureExecutionTime(int (*algorithm_func)(int, int, int, int), int start_x, int start_y, int end_x, int end_y) {
    clock_t start_time = clock();
    algorithm_func(start_x, start_y, end_x, end_y);
    clock_t end_time = clock();
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

int main() {
    int start_x, start_y, end_x, end_y;

    // Input start and end positions
    printf("Enter start position (x y): ");
    scanf("%d %d", &start_x, &start_y);
    printf("Enter end position (x y): ");
    scanf("%d %d", &end_x, &end_y);

    // Measure execution time for BFS
    double bfs_time = measureExecutionTime(findPathBFS, start_x, start_y, end_x, end_y);
    int bfs_moves = findPathBFS(start_x, start_y, end_x, end_y);
    if (bfs_moves != INT_MAX) {
        printf("Minimum moves by BFS: %d\n", bfs_moves);
        printf("Execution time for BFS: %f seconds\n", bfs_time);
    } else {
        printf("BFS did not find a valid path.\n");
    }

    // Measure execution time for Floyd-Warshall
    double floyd_warshall_time = measureExecutionTime(findPathFloydWarshall, start_x, start_y, end_x, end_y);
    int fw_moves = findPathFloydWarshall(start_x, start_y, end_x, end_y);
    if (fw_moves != INT_MAX) {
        printf("Minimum moves by Floyd-Warshall: %d\n", fw_moves);
        printf("Execution time for Floyd-Warshall: %f seconds\n", floyd_warshall_time);
    } else {
        printf("Floyd-Warshall did not find a valid path.\n");
    }

    // Measure execution time for A*
    double a_star_time = measureExecutionTime(findPathAStar, start_x, start_y, end_x, end_y);
    int astar_moves = findPathAStar(start_x, start_y, end_x, end_y);
    if (astar_moves != -1) {
        printf("Minimum moves by A*: %d\n", astar_moves);
        printf("Execution time for A*: %f seconds\n", a_star_time);
    } else {
        printf("A* did not find a valid path.\n");
    }

    return 0;
}
