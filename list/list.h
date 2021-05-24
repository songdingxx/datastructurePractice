#include "listNode.h"

template <typename T> class List
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
    // Get first node
    ListNodePosi(T) first() const {return header->succ;}
    // Get last node
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
    void merge(List<T>& L) {merge(first(), size, L, L.first(), L_size);}
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