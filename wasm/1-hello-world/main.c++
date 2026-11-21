#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    vector<int> a = {1, 2, 3, 4};
    cout << "Hello!" << endl;
    for (int i : a)
        cout << i << " ";
    cout << endl;
    return 0;
}