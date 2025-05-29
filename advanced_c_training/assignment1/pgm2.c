#include <stdio.h>
#include <stdlib.h>

void separateEvenAndOdd(int *array, int length) {
    int *buffer = (int *)malloc(length * sizeof(int));
    int *original = array;
    int *tempPtr = buffer;

    // Step 1: Transfer even elements
    for (int i = 0; i < length; i++) {
        if (*(original + i) % 2 == 0) {
            *tempPtr = *(original + i);
            tempPtr++;
        }
    }

    // Step 2: Transfer odd elements
    for (int i = 0; i < length; i++) {
        if (*(original + i) % 2 != 0) {
            *tempPtr = *(original + i);
            tempPtr++;
        }
    }

    // Step 3: Copy rearranged values back to the input array
    for (int i = 0; i < length; i++) {
        *(original + i) = *(buffer + i);
    }

    free(buffer);
}

// Demonstration
int main() {
    int numbers[] = {1, 2, 4, 3, 5, 6};
    int totalElements = sizeof(numbers) / sizeof(numbers[0]);

    separateEvenAndOdd(numbers, totalElements);

    for (int i = 0; i < totalElements; i++)
        printf("%d ", *(numbers + i));

    return 0;
}
