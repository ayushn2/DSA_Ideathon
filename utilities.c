#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 8

bool isValid(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}