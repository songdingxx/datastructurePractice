#include <iostream>

using namespace std;

inline __int64 sqr(int a) {return a * a;}

__int64 power2(int n)
{
    if (n == 0) return 1;
    return (n & 1) ? sqr(power2(n >> 1)) << 1 : sqr(power2(n >> 1));
}

int main()
{
    cout << "Enter a number:";
    int x;
    while(true)
    {
        cin >> x;
        if (x < 0) break;
        cout << power2(x) << endl;
    }
}