#include <stdio.h>

int maxDifference(int arr[], int n) {
    // เรียงลำดับอาเรย์โดยใช้ Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        
        if (!swapped) {
            break;
        }
    }

    // ผลต่างมากสุด = ค่าตัวสุดท้าย - ค่าตัวแรก
    return arr[n - 1] - arr[0];
}

int main() {
    int arr[] = {5, 13, 2, 8, 4, 12, 7, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maxDifference(arr, n);
    printf("Maximum Difference: %d\n", result);

    return 0;
}