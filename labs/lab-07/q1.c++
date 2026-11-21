#include <bits/stdc++.h>
using namespace std;

void print(const vector<int> &arr)
{
    for (int element : arr)
        cout << element << " ";
    cout << endl;
}

int partition(vector<int> &arr, int start, int end)
{
    int pivot = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);

    swap(arr[++i], arr[end]);
    return i;
}

void quickSort(vector<int> &arr)
{
    if (arr.empty())
        return;
    stack<pair<int, int>> st;
    st.push({0, static_cast<int>(arr.size() - 1)});
    while (!st.empty())
    {
        int start = st.top().first;
        int end = st.top().second;
        st.pop();
        if (start < end)
        {
            int pivot = partition(arr, start, end);
            st.push({start, pivot - 1});
            st.push({pivot + 1, end});
        }
    }
}

int main(int argc, char *argv[])
{
    vector<int> arr = {8, 10, 7, 9, 1, 5};
    cout << "Given Array: ";
    print(arr);
    quickSort(arr);
    cout << "Sorted Array: ";
    print(arr);
    return 0;
}