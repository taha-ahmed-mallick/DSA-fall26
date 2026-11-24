#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iomanip>
#include <stdexcept>
using namespace std;

vector<double> medianSlidingWindow(const vector<int> &nums, int k)
{
    int n = static_cast<int>(nums.size());
    if (k <= 0 || k > n)
    {
        throw invalid_argument("Invalid window size k");
    }

    priority_queue<int> maxHeap;                            // lower half
    priority_queue<int, vector<int>, greater<int>> minHeap; // upper half
    unordered_map<int, int> delayed;                        // lazy deletion counts

    int leftValid = 0;  // valid elements in maxHeap
    int rightValid = 0; // valid elements in minHeap

    auto pruneMax = [&]()
    {
        while (!maxHeap.empty() && delayed[maxHeap.top()] > 0)
        {
            --delayed[maxHeap.top()];
            maxHeap.pop();
        }
    };

    auto pruneMin = [&]()
    {
        while (!minHeap.empty() && delayed[minHeap.top()] > 0)
        {
            --delayed[minHeap.top()];
            minHeap.pop();
        }
    };

    auto rebalance = [&]()
    {
        while (leftValid > rightValid + 1)
        {
            pruneMax();
            if (maxHeap.empty())
                break;
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            --leftValid;
            ++rightValid;
        }
        while (leftValid < rightValid)
        {
            pruneMin();
            if (minHeap.empty())
                break;
            maxHeap.push(minHeap.top());
            minHeap.pop();
            --rightValid;
            ++leftValid;
        }
        pruneMax();
        pruneMin();
    };

    vector<double> ans;
    ans.reserve(n - k + 1);

    for (int i = 0; i < n; ++i)
    {
        int x = nums[i];
        pruneMax();

        if (maxHeap.empty() || x <= maxHeap.top())
        {
            maxHeap.push(x);
            ++leftValid;
        }
        else
        {
            minHeap.push(x);
            ++rightValid;
        }

        if (i >= k)
        {
            int outVal = nums[i - k];
            ++delayed[outVal];

            pruneMax();
            if (!maxHeap.empty() && outVal <= maxHeap.top())
            {
                --leftValid;
            }
            else
            {
                --rightValid;
            }
        }

        rebalance();

        if (i >= k - 1)
        {
            pruneMax();
            if (k % 2 == 1)
            {
                ans.push_back(static_cast<double>(maxHeap.top()));
            }
            else
            {
                pruneMin();
                long long sum = static_cast<long long>(maxHeap.top()) +
                                static_cast<long long>(minHeap.top());
                ans.push_back(static_cast<double>(sum) / 2.0);
            }
        }
    }

    return ans;
}

int main()
{
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<double> medians = medianSlidingWindow(nums, k);

    cout << fixed << setprecision(5) << "[";
    for (size_t i = 0; i < medians.size(); ++i)
    {
        cout << medians[i] << (i + 1 < medians.size() ? ", " : "");
    }
    cout << "]\n"; // [1.00000, -1.00000, -1.00000, 3.00000, 5.00000, 6.00000]

    return 0;
}