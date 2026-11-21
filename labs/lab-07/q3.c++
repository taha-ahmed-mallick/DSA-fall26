#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end(),
         [](const vector<int> &a, const vector<int> &b) -> bool
         {
             return a[0] < b[0];
         });
    vector<vector<int>> ans;
    int start = intervals[0][0], end = intervals[0][1];
    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] <= end)
        {
            if (intervals[i][1] > end)
                end = intervals[i][1];
        }
        else
        {
            ans.push_back({start, end});
            start = intervals[i][0];
            end = intervals[i][1];
        }
    }
    ans.push_back({start, end});
    return ans;
}

void printIntervals(const vector<vector<int>> &v)
{
    cout << "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << "[" << v[i][0] << "," << v[i][1] << "]";
        if (i + 1 < v.size())
            cout << ",";
    }
    cout << "]" << endl;
}

int main(int argc, char *argv[])
{
    vector<vector<vector<int>>> tests = {
        {{1, 4}, {4, 5}},
        {{1, 3}, {2, 6}, {8, 10}, {15, 18}},
        {{8, 10}, {1, 3}, {2, 6}},
        {{1, 10}, {2, 3}, {4, 5}},
        {{5, 7}}};
    for (auto &t : tests)
    {
        cout << "Input:  ";
        printIntervals(t);
        cout << "Output: ";
        printIntervals(merge(t));
        cout << endl;
    }
    return 0;
}