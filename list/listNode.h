typedef int Rank;

#define ListNodePosi(T) ListNode<T>*
#define NULL nullptr

template <typename T> struct ListNode
{
    // member
    // data, pointer to predecessor, pointer to successor
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ;

    // Construct function
    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        : data (e), pred(p), succ(s) {}
    // Operation
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, pred, this);
    pred->succ = x; pred = x;
    return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x; succ = x;
    return x;
}