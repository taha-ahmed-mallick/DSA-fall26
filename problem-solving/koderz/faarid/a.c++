#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t t;
    cin >> t;
    while(t) {
        size_t n, len, total = 0;
        cin >> n;
        while (n)
        {
            cin >> len;
            total += len - 1;
            n--;
        }
        cout << total << endl;
        t--;
    }
    return 0;
}