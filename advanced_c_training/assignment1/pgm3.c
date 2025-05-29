#include <stdio.h>

// Function to search for a key in a row-wise and column-wise sorted matrix
int findInMatrix(int **matrix, int size, int target) {
    int r = 0, c = size - 1;

    while (r < size && c >= 0) {
        if (matrix[r][c] == target)
            return 1;  // Target located
        else if (matrix[r][c] > target)
            c--;      // Move left if current value is too large
        else
            r++;      // Move down if current value is too small
    }

    return 0;  // Target not found
}

int main() {
    // Predefined 4x4 matrix for demonstration
    int grid[4][4] = {
        {1, 4, 7, 11},
        {2, 5, 8, 12},
        {3, 6, 9, 16},
        {10, 13, 14, 17}
    };

    int targetValue;
    printf("Enter value to search: ");
    scanf("%d", &targetValue);

    // Create an array of pointers to simulate int**
    int *matrixPointers[4];
    for (int i = 0; i < 4; i++) {
        matrixPointers[i] = grid[i];
    }

    // Perform search
    if (findInMatrix(matrixPointers, 4, targetValue))
        printf("Value found in matrix.\n");
    else
        printf("Value not present in matrix.\n");

    return 0;
}
