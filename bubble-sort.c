#include <stdio.h>

// Function to perform bubble sort
void bubleSort(int arr[], int n)
{
    // Traverse through all array elements
    for (int i = 0; i < n - 1; i++)
    {
        // Last i elements are already sorted
        for (int j = 0; j < n - i - 1; j++)
        {
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print an array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    bubleSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}