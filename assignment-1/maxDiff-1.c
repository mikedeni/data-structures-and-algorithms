#include <stdio.h>

int maxDifference(int arr[], int n) {
    int min_value = arr[0];
    int max_value = arr[0];

    // หาค่ามากสุดและน้อยสุด
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }

        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    // ผลต่างมากสุด = ค่ามากสุด - ค่าน้อยสุด
    int max_diff = max_value - min_value;

    return max_diff;
}

int main() {
    int arr[] = {5, 13, 2, 8, 4, 12, 7, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maxDifference(arr, n);
    printf("Maximum Difference: %d\n", result);

    return 0;
}