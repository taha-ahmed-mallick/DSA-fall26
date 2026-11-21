#include <iostream>
using namespace std;

void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int partition(int arr[], int start, int end) {
    int pivot = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);

    swap(arr[++i], arr[end]);
    return i;
}

void quickSort(int arr[], int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);
        quickSort(arr, start, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}

int main(int argc, char* argv[]) {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Given Array: ";
    printArr(arr, n);
    quickSort(arr, 0, n - 1);
    cout << "Sorted Array: ";
    printArr(arr, n);
    return 0;
}