#include <bits/stdc++.h>
using namespace std;

int findLHS(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int left = 0, maxLen = 0;
    for (int right = 0; right < nums.size(); right++)
    {
        while (nums[right] - nums[left] > 1)
            left++;
        if (nums[right] - nums[left] == 1)
            maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

void print(const vector<int> &vec)
{
    cout << "[";
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << ", ";
    cout << "\b\b]\n";
}

int main(int argc, char *argv[])
{
    vector<vector<int>> tests = {
        {1, 3, 2, 2, 5, 2, 3, 7},
        {1, 2, 3, 4},
        {1, 1, 1, 1}};

    for (auto &test : tests)
    {
        cout << "Input Vector: ";
        print(test);
        cout << "Result: " << findLHS(test) << endl;
    }
    return 0;
}