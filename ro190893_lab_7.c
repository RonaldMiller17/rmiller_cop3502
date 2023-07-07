#include <stdio.h>

void bubbleSort(int arr[], int n, int swaps[]) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps[j]++;
            }
        }
    }
}

void main() {
    int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int n = 9;
    int swaps[n];
    for (int i = 0; i < n; i++) {
        swaps[i] = 0;
    }

    bubbleSort(arr, n, swaps);

    printf("\n\nNumber of swaps for each index:\n");
    for (int i = 0; i < n; i++) {
        printf("Index %d: %d swaps\n", i, swaps[i]);
    }
}


