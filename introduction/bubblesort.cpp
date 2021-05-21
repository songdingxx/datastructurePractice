#include <algorithm>
#include <iostream>

using namespace std;

void bubblesort1A(int A[], int n)
{   
    bool sorted = false;
    while(!sorted)
    {
        sorted = true;
        for(int i = 0; i < n-1; i++)
        {
            if(A[i] > A[i+1])
            {
                sorted = false;
                swap(A[i], A[i+1]);
            }
        }
        n--;
    }
}

int main()
{
    int test_arr_1[] = {1123, 24, 3, 10};
    bubblesort1A(test_arr_1, 3);
    for (int i = 0; i < 4; i++) cout << test_arr_1[i] << endl;
}