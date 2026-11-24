#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

using FreqPair = pair<int, int>; // {frequency, value}

class MinFreqHeap
{
private:
    vector<FreqPair> h;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return 2 * i + 1; }
    int right(int i) const { return 2 * i + 2; }

    // Min-heap sift-down on any target vector within [0 .. size - 1]
    void heapifyDown(int idx, int size, vector<FreqPair> &vec) const
    {
        while (left(idx) < size)
        {
            int smallest = idx;
            int l = left(idx);
            int r = right(idx);

            if (vec[l] < vec[smallest])
                smallest = l;
            if (r < size && vec[r] < vec[smallest])
                smallest = r;

            if (smallest != idx)
            {
                swap(vec[idx], vec[smallest]);
                idx = smallest;
            }
            else
            {
                break;
            }
        }
    }

public:
    MinFreqHeap(const vector<FreqPair> &items) : h(items)
    {
        int n = static_cast<int>(h.size());
        for (int i = n / 2 - 1; i >= 0; --i)
        {
            heapifyDown(i, n, h);
        }
    }

    // Heap Sort on min-heap copy -> places largest frequency at index 0
    vector<FreqPair> sortDescendingByFreq() const
    {
        vector<FreqPair> sorted = h;
        int n = static_cast<int>(sorted.size());

        for (int sz = n; sz > 1; --sz)
        {
            swap(sorted[0], sorted[sz - 1]);
            heapifyDown(0, sz - 1, sorted);
        }
        return sorted;
    }
};

vector<int> topKFrequent(const vector<int> &nums, int k)
{
    unordered_map<int, int> counts;
    for (int x : nums)
        ++counts[x];

    vector<FreqPair> items;
    items.reserve(counts.size());
    for (const auto &kv : counts)
        items.push_back({kv.second, kv.first});

    MinFreqHeap heap(items);
    vector<FreqPair> desc = heap.sortDescendingByFreq();

    vector<int> ans;
    int limit = min(k, static_cast<int>(desc.size()));
    ans.reserve(limit);
    for (int i = 0; i < limit; ++i)
    {
        ans.push_back(desc[i].second);
    }
    return ans;
}

void printVec(const vector<int> &v)
{
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    cout << "]\n";
}

int main()
{
    vector<int> ex1 = {1, 1, 1, 2, 2, 3};
    cout << "Example 1 (k=2): ";
    printVec(topKFrequent(ex1, 2)); // [2, 1] or [1, 2]

    vector<int> ex2 = {1};
    cout << "Example 2 (k=1): ";
    printVec(topKFrequent(ex2, 1)); // [1]

    return 0;
}