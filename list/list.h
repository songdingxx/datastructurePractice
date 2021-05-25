#include "listNode.h"
#include <cstdlib>

template <typename T> class List
// header -> first -> last -> trailer
{
private:
    // Size, head node, tail node
    int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;

protected:
    // Initialization
    void init();
    // Delete all nodes
    int clear();
    // Copy all nodes start from p
    void copyNodes(ListNodePosi(T), int);
    // Merge lists
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
    // Merge sort
    void mergeSort(ListNodePosi(T)&, int);
    // Selection sort
    void selectionSort(ListNodePosi(T), int);
    // Insertion sort
    void insertionSort(ListNodePosi(T), int);

public:
// Constructor
    List() {init();}
    List(List<T> const& L);
    List(List<T> const& L, Rank r, int n);
    List(ListNodePosi(T) p, int n);
// Destructor
    ~List();
// Read only interface
    // get size
    Rank size() const {return _size;}
    // judge whether is empty or not
    bool empty() const {return _size <= 0;}
    // Re-write [] operator to support access by index
    T& operator[] (Rank r) const;
    // Get first node's pointer
    ListNodePosi(T) first() const {return header->succ;}
    // Get last node's pointer
    ListNodePosi(T) last() const {return trailer->pred;}
    // judge whether is valid
    bool valid(ListNodePosi(T) p) {return p && (trailer != p) && (header != p);}
    // judge whether the list is sorted or not
    int disordered() const;
    // search in disordered list
    // Note: different from search in ordered list - time complexity
    ListNodePosi(T) find(T const& e) const {return find(e, _size, trailer);}
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
    // search in ordered list
    ListNodePosi(T) search(T const& e) const {return search(e, _size, trailer);}
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
    // Select max node in n nodes that are after node p
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax() {return selectMax(header->succ, _size);}

//  writable interfaces
    ListNodePosi(T) insertAsFirst(T const& e);
    ListNodePosi(T) insertAsLast(T const& e);
    // insert as a successor of node p
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
    // insert as a predecessor of node p
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);
    // Delete node p (already verified as valid)
    T remove(ListNodePosi(T) p);
    // Merge two list
    // TODO: why use l.first() and L._size as parameters here? Why not read these two variables in function?
    void merge(List<T>& L) {merge(first(), size, L, L.first(), L._size);}
    // sort within inteval n
    void sort(ListNodePosi(T) p, int n);
    // sort the whole list
    void sort() {sort(first(), _size);}
    // remove duplicated nodes in unsorted list
    int deduplicate();
    // remove duplicated nodes in sorted list
    int uniquify();
    // reverse list
    void reverse();

// Traverse list
    // Pass function
    void traverse(void (*) (T&));
    // Use reference to traverse
    // Difference: can re-write () operator, instead of using function only
    template <typename VST>
    void traverse(VST&);
};

// Init funciton
template <typename T> void List<T>::init()
{
    header = new ListNode<T>;
    trailer - new ListNode<T>;
    header->succ = trailer; header->pred = NULL;
    trailer->pred = header; trailer->succ = NULL;
    _size = 0;
}

// Rewrite [] operator
template <typename T>
T& List<T>::operator[] (Rank r) const
{
    ListNodePosi(T) p = first();
    while(0 < r--) p = p->succ;
    return p->data;
}

// search
// unsorted list
// before node p
template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
    while(0 < n--)
        if (e == (p = p->pred)->data) return p;
    return NULL;
}

// sorted list
template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
    while (0 <= n--)
        if ((p = p->pred)->data <= e) break;
    return p;
}

// insertion
template <typename T> ListNodePosi(T) List<T>::insertAsFirst (T const& e)
{
    _size++; return header->insertAsSucc(e);
}

template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
    _size++; return trailer->insertAsPred(e);
}

template <typename T> ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)
{
    _size++; return p->insertAsSucc(e);
}

template <typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
{
    _size++; return p->insertAsPred(e);
}

// copynodes
template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
    init();
    while (n--) {insertAsLast(p->data); p = p->succ;}
}

// Init list using copy
template <typename T>
List<T>::List(ListNodePosi(T) p, int n) {copyNodes(p, n);}

// copy the whole list
template <typename T>
List<T>::List(List<T> const& L) {copyNodes(L.first(), L._size);}

// copy from node r
template <typename T>
List<T>::List(List<T> const& L, int r, int n) {copyNodes(L[r], n);}

// Delete
template <typename T> 
T List<T>::remove(ListNodePosi(T) p)
{
    T e = p->data;
    p->pred->succ = p->succ; p->succ->pred = p->pred;
    delete p; _size--;
    return e;
}

// Deconstruction
template <typename T>
List<T>::~List() {clear(); delete header; delete trailer;}

template <typename T> 
int List<T>::clear()
{
    int oldSize = _size;
    while (0 < _size) remove(header -> succ);
    return oldSize;
}

// remove duplicated elements
// unsorted list
template <typename T>
int List<T>::deduplicate()
{
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header; Rank r = 0;
    while (trailer != (p = p->succ))
    {
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}

// sorted list
template <typename T>
int List<T>::uniquify()
{
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = first(); ListNodePosi(T) q;
    while (trailer != (q = p->succ))
    {
        if (p->data != q->data) p = q;
        else remove(q);
    }
    return oldSize - _size;
}

// Traverse
// use function's pointer?
template <typename T>
void List<T>::traverse(void (*visit) (T&))
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

// Use reference
template <typename T> template <typename VST>
void List<T>::traverse(VST& visit)
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

// Sort
template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
    switch (std::rand() % 3)
    {
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
}

// Insertion sort
template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n)
{
    for (int r = 0; r < n; r++)
    {
        insertA(serach(p->data, r, p), p->data);
        p = p->succ; remove(p->pred);
    }
}

// Selection sort
template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
    ListNodePosi(T) max = selectMax(head->succ, n);
    insertB(tail, remove(max));
    tail = tail->pred; n--;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) max = p;
    for (ListNodePosi(T) cur = p; 1 < n; n--)
    {
        if (!lt((cur = cur->succ)->data, max->data)) max = cur;
    }
    return max;
}

// Merge sort
// Use pointer's reference to mark the start of intervals - bravo! so clever.
template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
{
    ListNodePosi(T) pp = p->pred;
    while (0 < m)
    {
        if ((0 < n) && (p->data <= q->data))
        {
            if (q == (p = p->succ)) break; n--;
        }
        else
        {
            insertB(p, L.remove((q = q->succ)->pred)); m--;
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n)
{
    if (n < 2) return;
    int m = n >> 1;
    ListNodePosi(T) q = p; for (int i = 0; i < m; i++) q = q->succ;
    mergeSort(p, m); mergeSort(q, n-m);
    merge(p, m, *this, q, n-m);
}