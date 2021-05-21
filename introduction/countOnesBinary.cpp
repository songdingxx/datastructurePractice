#include <iostream>

using namespace std;

int countOnes(unsigned int n)
{
    int ones = 0;
    while (n > 0)
    {
        ones += (1 & n);
        n >>= 1;
    }
    return ones;
}

int main()
{
    int x;
    cout << "Type a number: ";
    while (true)
    {
        cin >> x;
        if (x < 0) break;
        cout << countOnes(x) << endl;
    }
}