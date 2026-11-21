#include <bits/stdc++.h>
using namespace std;

bool carPooling(vector<vector<int>> &trips, int cap)
{
    vector<pair<int, int>> points;
    for (auto &trip : trips)
    {
        int passegers = trip[0], from = trip[1], to = trip[2];
        points.push_back({from, -passegers});
        points.push_back({to, passegers});
    }

    sort(points.begin(), points.end(), [](const pair<int, int> &a, const pair<int, int> &b) -> bool
         {
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first; });

    for (auto &point : points)
    {
        cap += point.second;
        if (cap < 0)
            return false;
    }
    return true;
}

void runTest(vector<vector<int>> &trips, int cap)
{
    cout << "Capacity: " << cap << endl
         << "[";
    int i = 0;
    for (; i < trips.size() - 1; i++)
        cout << "[" << trips[i][0] << ", " << trips[i][1] << ", " << trips[i][2] << "], ";
    cout << "[" << trips[i][0] << ", " << trips[i][1] << ", " << trips[i][2] << "]";
    cout << "]\n";
    cout << "Result: " << (carPooling(trips, cap) ? "true" : "false") << endl
         << endl;
}

int main(int argc, char *argv[])
{
    vector<vector<int>> trip1 = {{2, 1, 5}, {3, 3, 7}};
    vector<vector<int>> trip2 = {{3, 2, 7}, {3, 7, 9}, {8, 3, 9}};
    runTest(trip1, 4);
    runTest(trip1, 5);
    runTest(trip2, 11);
    runTest(trip2, 10);
    return 0;
}