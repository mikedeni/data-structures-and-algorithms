#include <stdio.h>

// Function to perform ternary search
int ternarySearch(int array[], int left, int right, int target) {
    if (right >= left) {
        // Calculate two midpoints
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        // Check if the target is at one of the midpoints
        if (array[mid1] == target) {
            return mid1;
        }
        if (array[mid2] == target) {
            return mid2;
        }

        // Narrow the search range
        if (target < array[mid1]) {
            return ternarySearch(array, left, mid1 - 1, target); // Search in the left third
        } else if (target > array[mid2]) {
            return ternarySearch(array, mid2 + 1, right, target); // Search in the right third
        } else {
            return ternarySearch(array, mid1 + 1, mid2 - 1, target);
        }
    }

    // Target not found
    return -1;
}

int main() {
    int array[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int size = sizeof(array) / sizeof(array[0]);
    int target = 99;

    int result = ternarySearch(array, 0, size - 1, target);

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found in the array\n");
    }

    return 0;
}