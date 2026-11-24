#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <iomanip>
#include <stdexcept>
using namespace std;

struct Worker
{
    double ratio; // minimum wage per unit of quality: wage[i] / quality[i]
    int quality;
    int wage;
};

double mincostToHireWorkers(const vector<int> &quality, const vector<int> &wage, int k)
{
    int n = static_cast<int>(quality.size());
    if (k <= 0 || k > n || static_cast<int>(wage.size()) != n)
    {
        throw invalid_argument("Invalid input sizes or k");
    }

    vector<Worker> workers;
    workers.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        double r = static_cast<double>(wage[i]) / static_cast<double>(quality[i]);
        workers.push_back({r, quality[i], wage[i]});
    }

    sort(workers.begin(), workers.end(), [](const Worker &a, const Worker &b)
         { return a.ratio < b.ratio; });

    // 3. Max-heap of qualities (keeps at most k smallest qualities) + running quality sum
    priority_queue<int> maxQualityHeap;
    long long qualitySum = 0;
    double minCost = numeric_limits<double>::infinity();

    for (const Worker &w : workers)
    {
        maxQualityHeap.push(w.quality);
        qualitySum += w.quality;

        if (static_cast<int>(maxQualityHeap.size()) > k)
        {
            qualitySum -= maxQualityHeap.top();
            maxQualityHeap.pop();
        }

        if (static_cast<int>(maxQualityHeap.size()) == k)
        {
            double currentCost = w.ratio * static_cast<double>(qualitySum);
            if (currentCost < minCost)
                minCost = currentCost;
        }
    }

    return minCost;
}

int main()
{
    cout << fixed << setprecision(5);

    vector<int> q1 = {10, 20, 5};
    vector<int> w1 = {70, 50, 30};
    cout << "Example 1: " << mincostToHireWorkers(q1, w1, 2) << "\n"; // 105.00000

    vector<int> q2 = {3, 1, 10, 10, 1};
    vector<int> w2 = {4, 8, 2, 2, 7};
    cout << "Example 2: " << mincostToHireWorkers(q2, w2, 3) << "\n"; // 30.66667

    return 0;
}