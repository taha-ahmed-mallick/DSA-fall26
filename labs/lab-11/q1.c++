#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxHeap
{
private:
    vector<int> heap;

public:
    MaxHeap() : heap() {}
    MaxHeap(const vector<int> &arr) : heap(arr)
    {
        buildMaxHeap(this->heap);
    }
    void insert(int val)
    {
        heap.push_back(val);
        heapifyUp();
    }
    vector<int> sort()
    {
        vector<int> cp(heap);
        for (int heapSize = static_cast<int>(cp.size()); heapSize > 1; --heapSize)
        {
            swap(cp[0], cp[heapSize - 1]);    // Move current max to end of unsorted region
            heapifyDown(0, heapSize - 1, cp); // Restore max-heap on [0 .. heapSize - 2]
        }
        return cp;
    }
    int getMax() const
    {
        if (!heap.empty())
            return heap[0];
        return -1;
    };
    bool isEmpty() const { return heap.empty(); }
    void displayHeap() const
    {
        if (heap.empty())
        {
            cout << "[]\n";
            return;
        }
        cout << "[";
        for (int x : heap)
            cout << x << ", ";
        cout << "\b\b]\n";
    }

private:
    int parent(int idx) { return (idx - 1) / 2; }
    int lftChld(int idx) { return 2 * idx + 1; }
    int rghtChld(int idx) { return 2 * idx + 2; }

    void heapifyUp() { heapifyUp(this->heap.size() - 1); }
    void heapifyUp(int idx)
    {
        while (idx > 0 && heap[parent(idx)] < heap[idx])
        {
            swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    void heapifyDown() { heapifyDown(0, this->heap.size(), this->heap); }

    void heapifyDown(int idx) { heapifyDown(idx, this->heap.size(), this->heap); }

    void heapifyDown(int idx, int size) { heapifyDown(idx, size, this->heap); }

    // made this specific function so that sort() could pass its copy heap which has to be sorted
    void heapifyDown(int idx, int size, vector<int> &vec)
    {
        while (lftChld(idx) < size)
        {
            int largest = idx;
            int left = lftChld(idx);
            int right = rghtChld(idx);
            if (vec[left] > vec[largest])
                largest = left;
            if (right < size && vec[right] > vec[largest])
                largest = right;
            if (largest != idx)
            {
                swap(vec[largest], vec[idx]);
                idx = largest;
            }
            else
                break;
        }
    }

    void buildMaxHeap(vector<int> &vec)
    {
        int n = vec.size();
        for (int i = n / 2 - 1; i >= 0; --i)
        {
            heapifyDown(i, n, vec);
        }
    }
};

int main(int argc, char *argv[])
{
    vector<int> raw = {4, 10, 3, 5, 1};
    MaxHeap mh(raw);

    cout << "Max-Heap after bottom-up build: ";
    mh.displayHeap();

    vector<int> sorted = mh.sort();
    cout << "Sorted ascending: ";
    cout << "[";
    for (size_t i = 0; i < sorted.size(); ++i)
    {
        cout << sorted[i] << (i + 1 < sorted.size() ? ", " : "");
    }
    cout << "]\n";

    cout << "Original Max-Heap still intact: ";
    mh.displayHeap();

    return 0;
}