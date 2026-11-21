#include <iostream>
#include <emscripten.h>
using namespace std;

EMSCRIPTEN_KEEPALIVE
int addNums(int a, int b)
{
    return a + b;
}

int main()
{
    cout << "Hello, World! " << addNums(5, 3) << endl;
    return 0;
}