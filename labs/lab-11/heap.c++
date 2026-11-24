#include <iostream>
#include <vector>
using namespace std;

class MaxHeap
{
private:
    vector<int> heap;
    // Helper method to heapify up (for insertion)
    void heapifyUp(int index)
    {
        while (index > 0 && heap[parent(index)] < heap[index])
        {
            swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }
    // Helper method to heapify down (for deletion)
    void heapifyDown(int index)
    {
        int size = heap.size();
        while (leftChild(index) < size)
        { // while there is a left child
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            if (heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;
            if (largest != index)
            {
                swap(heap[index], heap[largest]);
                index = largest;
            }
            else
            {
                break; // heap property satisfied
            }
        }
    }
    // Helper functions to get parent and children indices
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

public:
    // Insert a new value into the heap
    void insert(int value)
    {
        heap.push_back(value);      // Add value at the end
        heapifyUp(heap.size() - 1); // Restore heap property
    }
    // Remove the maximum element (the root)
    int extractMax()
    {
        if (heap.empty())
        {
            throw out_of_range("Heap is empty");
        }
        int maxValue = heap[0];
        heap[0] = heap.back(); // Move last element to root
        heap.pop_back();       // Remove the last element
        heapifyDown(0);        // Restore heap property
        return maxValue;
    }
    // Get the maximum element without removing it
    int getMax() const
    {
        if (heap.empty())
        {
            throw out_of_range("Heap is empty");
        }
        return heap[0];
    }
    // Check if the heap is empty
    bool isEmpty() const
    {
        return heap.empty();
    }
};
// Main function to demonstrate the MaxHeap class
int main()
{
    MaxHeap heap;
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);
    heap.insert(40);
    heap.insert(10);
    cout << "Max element: " << heap.getMax() << endl;
    cout << "Extracting max element: " << heap.extractMax() << endl;
    cout << "Max-element after extraction: ";
    cout << "Max element: " << heap.getMax() << endl;
}