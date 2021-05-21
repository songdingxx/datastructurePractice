#include<iostream>

using namespace std;

int main()
{
    int capacity;
    int* a;
    a = new int[capacity = 3];
    for (int _size = 0; _size < capacity; a[_size++] = _size-1);
    for (int _size = 0; _size < capacity; cout<<a[_size++]<<endl);
    // cout << capacity << endl;
}