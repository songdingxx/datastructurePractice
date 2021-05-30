#include "BinNode.h"

template <typename T>
class BinTree
{
protected:
    // size, root node
    int _size; BinNodePosi(T) _root;
    // update node x's height
    virtual int updateHeight(BinNodePosi(T) x);
    // update x and parent's height
    void updateHeightAbove(BinNodePosi(T) x);

public:
    // constructor
    BinTree(): _size(0), _root(NULL) {}
    // deconstructor
    // TODO: what about other nodes?
    ~BinTree() {if (0 < _size) remove(_root);}
    int size() const {return _size;}
    bool empty() const {return !_root;}

    BinNodePosi(T) root() const {return _root;}
    BinNodePosi(T) insertAsRoot(T const& e);
    // insert e as x's left child
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
    // insert e as x's right child
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
    // attach as x's left sub tree
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &t);
    // attach as x's right sub tree
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &t);
    // remove subtree with x as root
    int remove(BinNodePosi(T) x);
    // remove x from tree amd return a subtree
    BinTree<T>* secede(BinNodePosi(T) x);
    // traverse by level
    template <typename VST>
    void travLevel(VST& visit)
    {
        if (_root) _root->travLevel(visit);
    }
    // inordre traversal
    template <typename VST>
    void travIn(VST& visit)
    {
        if (_root) _root->travIn(visit);
    }
    // pre-order traversal
    template <typename VST>
    void travPre(VST& visit)
    {
        if (_root) _root->travPre(visit);
    }
    // post-order traversal
    template <typename VST>
    void travPost(VST& visit)
    {
        if (_root) _root->travPost(visit);
    }

    // comparator
    // TODO: what is lt function
    bool operator<(BinTree<T> const& t) {return _root && t._root && lt(_root, t._root);}
    bool operator==(BinTree<T> const& t) {return _root && t._root && (_root == t._root);}
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
    while(x) 
    {
        updateHeight(x); x = x->parent;
    }
}

template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
    _size = 1; return _root = new BinNode<T>(e);
}

template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
    _size++; x->insertAsLC(e);updateHeightAbove(x); return x->lc;
}

template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
    _size++; x->insertAsRC(e);updateHeightAbove(x); return x->rc;
}

// Release undefined yet
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S)
{
    if (x->lc = S->root) x->lc->parent = x;
    _size += S->_size; updateHeightAbove(x);
    S->_root = NULL; S->_size = 9; release(S); S = NULL; return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S)
{
    if (x->rc = S->root) x->rc->parent = x;
    _size += S->_size; updateHeightAbove(x);
    S->_root = NULL; S->_size = 9; release(S); S = NULL; return x;
}

// remove x and it's children
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x); _size -= n; return n;
}

template <typename T>
static int removeAt(BinNodePosi(T) x)
{
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data); release(x); return n;
}

template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
    FromParentTo (*x) = NULL;
    updateHeightAbove(x->parent);
    BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL;
    // Have I defined BinNode->size()?
    S->_size = x->size(); _size -= S->_size; return S;
}