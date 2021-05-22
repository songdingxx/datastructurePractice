#include <iostream>
#include "../fibonacci/Fib.h"

typedef int Rank;

#define DEFAULT_CAPACITY 3

template <typename T> 
class Vector
{
protected:
    // Size, capacity and pointer to data
    // _size: The length of the vector
    // _capacity: The total capacity of the vector
    // _elem: The private array
    Rank _size; int _capacity; T* _elem;
    // Copy from lo to hi
    void copyFrom (T const* A, Rank lo, Rank hi);
    // Expand when capacity is full
    void expand();
    // Shrink when the capacity is mostly not used
    void shrink();
    // Scan
    bool bubble(Rank lo, Rank hi);
    // Bubble sort the vector
    void bubbleSort(Rank lo, Rank hi);
    // Get the max element
    Rank max(Rank lo, Rank hi);
    // Selection sort
    void selectionSort(Rank lo, Rank hi);
    // Merge algorithm
    void merge(Rank lo, Rank mi, Rank hi);
    // Merge sort
    void mergeSort(Rank lo, Rank hi);
    // Partition - don't know what is this for
    Rank partition(Rank lo, Rank hi);
    // Quick sort algorithm
    void quickSort(Rank lo, Rank hi);
    // Heap sort
    void heapSort(Rank lo, Rank hi);

public:
// Construction method
    // Capacity = default_capacity, size = s, initial values for all elemetes are v
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
    // Create array and assign value to _capacity
    _elem = new T[_capacity = c];
    // Initialize array and _size
    for (_size = 0; _size < s; _elem[_size++]=v);
    }
    // Copy vector
    Vector(T const* A, Rank n){copyFrom(A, 0, n);}
    // Copy from low to high
    Vector(T const* A, Rank lo, Rank hi){copyFrom(A, lo, hi);}
    // Copy using vector's reference
    Vector(Vector<T> const& V) {copyFrom(V._elem, 0, V._size);}
    // Copy using pointer's reference and lo, hi
    Vector(Vector<T> const& V, Rank lo, Rank hi){copyFrom(V._elem, lo, hi);}

// Deconstructor
    ~Vector() {delete [] _elem;}

// Read only function
    // Return size
    Rank size() const {return _size;}
    // Judge whether the vector is empty
    bool empty() const {return !_size;}
    // Judge whether the vector is sorted
    int disordered() const;
    // Find element
    // TODO: Why reference here?
    Rank find(T const& e) const {return find(e, 0, _size);}
    // Find element in an interval
    Rank find(T const& e, Rank lo, Rank hi) const;
    // Search element
    Rank search(T const& e) const {return (0 >= _size) ? -1 : search(e, 0, _size);}
    // Search element in an interval
    Rank search(T const& e, Rank lo, Rank hi) const;

// Reac write function
    // Reload indices?
    // TODO: Don't understand
    T& operator[] (Rank r) const;
    // Don't understand
    Vector<T> & operator = (Vector<T> const&); 
    // Remove element with rank r
    T remove(Rank r);
    // Remove elements in [lo, hi)
    int remove(Rank lo, Rank hi);
    // Insert element
    Rank insert(Rank r, T const& e);
    // Insert at last
    Rank insert(T const& e) {return insert(_size, e);}
    // Sort for elements in [lo, hi)
    void sort(Rank lo, Rank hi);
    // Sort all elements
    void sort() {sort(0, _size);}
    // Unsort for elements in [lo, hi)
    void unsort(Rank lo, Rank hi);
    // Unsort all elements
    void unsort() {unsort(0, _size);}
    // Delete duplicated elements in unsorted vector
    int deduplicate();
    // Delete duplicated elements in sorted vector
    int uniquify();

// Traverse
    // TODO: What's the difference?
    // Don't understand the syntax here
    void traverse(void (*) (T&));
    // traverse
    template <typename VST> void traverse(VST&);
};

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
    while(lo < hi)
        _elem[_size++] = A[lo++];
}

// Rewrite operator =
// TODO: Write some examples to understand this
template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V)
{
    // Delete original content
    if (_elem) delete [] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

// Expand space
// Apply for a bigger space and move elements to the bigger space
template <typename T> void Vector<T>::expand()
{
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    // Double the space
    T* oldElem = _elem; _elem = new T[_capacity <<= 1];
    for(int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

// Shrink
// copy to a smaller array
template <typename T> void Vector<T>::shrink()
{
    if(_capacity < DEFAULT_CAPACITY << 1) return;
    if(_size << 2 > _capacity) return;
    // Return space by half
    T* oldElem = _elem; _elem = new T[_capacity >>= 1];
    for(int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete [] oldElem;
}

// Re-write operator []
template <typename T> T& Vector<T>::operator[] (Rank r) const
{
    return _elem[r];
}

// Unsort machine
// Permute: basic idea of unsort
template <typename T> void permute(Vector<T>& V)
{
    for(int i = V.size(); i > 0; i--)
        swap(V[i - 1], V[rand() %  i]);
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi)
{
    T* V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
}

// Comparator
template <typename T> static bool lt(T* a, T* b) {return lt(*a, *b);}
template <typename T> static bool lt(T& a, T& b) {return a < b;}
template <typename T> static bool eq(T* a, T* b) {return eq(*a, *b);}
template <typename T> static bool eq(T& a, T& b) {return a == b;}

// Find function
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
    while((lo < hi--) && (e != _elem[hi]));
    return hi;
}

// Insert
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
    expand();
    for (int i = _size; i > r; i--) _elem[i] = _elem[i-1];
    _elem[r] = e; _size++;
    return r;
}

// Remove
// re-assign values to elements, instead of deleting
template <typename T> int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi) return 0;
    while (hi < _size) _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

// Remove single element
template <typename T> T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

// Remove duplicated elements
template <typename T> int Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while(i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - _size;
}

// Traverse
// Use function's pointer as input?
template <typename T> void Vector<T>::traverse(void (*visit) (T&))
{
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

// Use function reference
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit)
{
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

// Increase function
// Re-write ()
// TODO: Don't understand the meaning of this struct

// workflow
// increase function calls traverse fucntion
// traverse function uses operator (), input is element in _elem
// Increase's () operator increase element's value by 1
template <typename T> struct Increase
{
    virtual void operator() (T& e) {e++;}
};

template <typename T> void increase(Vector<T> &V)
{
    V.traverse(Increase<T>());
}

// Check order
template <typename T> int Vector<T>::disordered() const
{
    int n = 0;
    for(int i = 1; i < _size; i++)
        if (_elem[i - 1] > _elem[i]) n++;
    return n;
}

// Remove duplicated elements for ordered vector
// time complexity - O(n)
template <typename T> int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i; shrink();
    return j - i;
}

// Search in sorted vector
template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
    // 50% chance uses binary serach, 50% chance uses fibonacci serach
    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

// Binary search, search e in sorted interval [lo, hi)
// Version A: 
//      cannot return the result with biggest rank
//      cannot specify the position that failure happens 
// template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
// {
//     while (lo < hi)
//     {
//         Rank mi = (lo + hi) >> 1;
//         if (e < A[mi]) hi = mi;
//         else if (A[mi] < e) lo = mi + 1;
//         else return mi;
//     }
//     return -1;
// }

// Binary search
// Version B: 
//      divide into two cases
// template <typename T> static Rank binSearch(T* A, T const & e, Rank lo, Rank hi)
// {
//     while (1 < hi - lo)
//     {
//         Rank mi = (lo + hi) >> 1;
//         (e < A[mi]) ? hi = mi : lo = mi;
//     }

//     return (e == A[lo]) ? lo : -1;
// }

// Binary serach
// Version C:
//      
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
{
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

// Fibonacci search
// TODO: Don't get it for now - 05/21
template <typename T> static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi)
{
    Fib fib (hi-lo);
    while (lo < hi)
    {
        while (hi - lo < fib.get()) fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else return mi;
    }
    return -1;
}

// Sort
template <typename T> void Vector<T>::sort(Rank lo, Rank hi)
{
    switch(rand() % 5)
    {
        case 1: bubbleSort(lo, hi); break;
        case 2: selectionSort(lo, hi); break;
        case 3: mergeSort(lo, hi); break;
        case 4: heapSort(lo, hi); break;
        default: quickSort(lo, hi); break;
    }
}

// Bubble sort
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--));
}

template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi)
{
    bool sorted = true;
    while(++lo < hi)
        if (_elem[lo - 1] > _elem[lo])
        {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
}

// Merge sort
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if (hi - lo < 2) return;
    int mi = (lo + hi) / 2;
    mergeSort(lo, mi); mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    T* A = _elem + lo;
    int lb = mi - lo; T* B = new T[lb];
    for (Rank i = 0; i < lb; B[i] = A[i++]);
    int lc = hi - mi; T* C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
    {
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (C[k] <= B[j]))) A[i++] = C[k++];
    }
    delete [] B;
}



int main()
{

}