#include <iostream>
using namespace std;

void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    cout << left << " " << mid << " " << right << endl;
    int l[n1], r[n2];
    for (int i = 0; i < n1; i++)
        l[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        r[i] = arr[mid + i + 1];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        if (l[i] <= r[j])
            arr[k++] = l[i++];
        else
            arr[k++] = r[j++];

    while (i < n1)
        arr[k++] = l[i++];

    while (j < n2)
        arr[k++] = r[j++];
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main(int argc, char *argv[])
{
    int arr[] = {40, 2, 10, 4, 1, 19, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Given Array: ";
    printArr(arr, size);
    mergeSort(arr, 0, size - 1);
    cout << "Sorted Array: ";
    printArr(arr, size);
    return 0;
}