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