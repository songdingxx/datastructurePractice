#include <iostream>

using namespace std;

void reverse(int* A, int lo, int hi)
{
    if (lo < hi)
    {
        swap(A[lo], A[hi]);
        reverse(A, lo + 1, hi - 1);
    }
}

void reverse(int* A, int n)
{
    reverse(A, 0, n-1);
}

int main()
{
    int test_arr_1[] = {1, 2, 3, 4, 5, 6, 7};
    reverse(test_arr_1, 3);
    for(int i = 0; i < sizeof(test_arr_1) / sizeof(test_arr_1[0]); i++)
    {
        cout << test_arr_1[i] << ",";
    }
}