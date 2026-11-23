#include <bits/stdc++.h>
using namespace std;

void print(const vector<int> &arr)
{
    for (int element : arr)
        cout << element << " ";
    cout << endl;
}

void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> l(n1), r(n2);
    for (int i = 0; i < n1; i++)
        l[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        r[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        if (l[i] <= r[j]) // added equal comp for stability
            arr[k++] = l[i++];
        else
            arr[k++] = r[j++];
    while (i < n1)
        arr[k++] = l[i++];
    while (j < n2)
        arr[k++] = r[j++];
}

void mergeSort(vector<int> &arr)
{
    int n = arr.size();
    for (int width = 1; width < n; width *= 2)
        for (int left = 0; left < n;)
        {
            int mid = min(left + width - 1, n - 1);
            int right = min(left + width * 2 - 1, n - 1);
            if (mid < right)
                merge(arr, left, mid, right);
            left = right + 1;
        }
}

int main(int argc, char *argv[])
{
    vector<int> arr = {8, 10, 7, 9, 1, 5};
    cout << "Given Array: ";
    print(arr);
    mergeSort(arr);
    cout << "Sorted Array: ";
    print(arr);
    return 0;
}