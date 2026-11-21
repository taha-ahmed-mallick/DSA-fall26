
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long x;
    cin >> n >> x;

    vector<long long> vec(n);

    for (int i = 0; i < n; i++)
        cin >> vec[i];

    if (x < 0)
        x = -x;

    sort(vec.begin(), vec.end());

    int i = 0, j = 1;

    while (j < n)
    {
        if (i == j)
        {
            j++;
            continue;
        }

        long long diff = vec[j] - vec[i];

        if (diff == x)
        {
            cout << "Yes\n";
            return 0;
        }
        else if (diff < x)
        {
            j++;
        }
        else
        {
            i++;
        }
    }

    cout << "No\n";
    return 0;
}
