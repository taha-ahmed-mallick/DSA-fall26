#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

using CharFreqPair = pair<int, unsigned char>; // {frequency, character byte}

class MinCharFreqHeap
{
private:
    vector<CharFreqPair> h;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return 2 * i + 1; }
    int right(int i) const { return 2 * i + 2; }

    // Min-heap sift-down on `vec` within [0 .. size - 1]
    void heapifyDown(int idx, int size, vector<CharFreqPair> &vec) const
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
    explicit MinCharFreqHeap(const vector<CharFreqPair> &items) : h(items)
    {
        int n = static_cast<int>(h.size());
        for (int i = n / 2 - 1; i >= 0; --i)
        {
            heapifyDown(i, n, h);
        }
    }

    // Heap Sort on a copy of the min-heap -> largest frequency ends up at index 0
    vector<CharFreqPair> sortDescendingByFreq() const
    {
        vector<CharFreqPair> sorted = h;
        int n = static_cast<int>(sorted.size());

        for (int sz = n; sz > 1; --sz)
        {
            swap(sorted[0], sorted[sz - 1]);
            heapifyDown(0, sz - 1, sorted);
        }
        return sorted;
    }
};

string frequencySort(const string &s)
{
    if (s.empty())
        return "";

    unordered_map<unsigned char, int> counts;
    counts.reserve(s.size());
    for (char ch : s)
    {
        ++counts[static_cast<unsigned char>(ch)];
    }

    vector<CharFreqPair> items;
    items.reserve(counts.size());
    for (const auto &kv : counts)
    {
        items.push_back({kv.second, kv.first});
    }

    MinCharFreqHeap heap(items);
    vector<CharFreqPair> desc = heap.sortDescendingByFreq();

    string result;
    result.reserve(s.size());
    for (const auto &entry : desc)
    {
        int freq = entry.first;
        char ch = static_cast<char>(entry.second);
        result.append(static_cast<size_t>(freq), ch);
    }

    return result;
}

int main()
{
    cout << "Example 1 (\"tree\"): " << frequencySort("tree") << "\n";     // e.g., "eert" or "eetr"
    cout << "Example 2 (\"cccaaa\"): " << frequencySort("cccaaa") << "\n"; // "cccaaa" or "aaaccc"
    return 0;
}