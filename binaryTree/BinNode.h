#include <cstdlib>
#include "../stackAddQueue/stack.h"
#include "../stackAddQueue/queue.h"

// Get node's pointer
#define BinNodePosi(T) BinNode<T>*
// Get height
#define stature(p) ((p) ? (p)->height : -1)

// for readable
#define IsRoot(x) (!((x).parent))
// TODO: which is the parameter for ==? &(x) or (x).parent->something?
//          Assume x is an object
//          (x).parent->lc is a pointer
//          &(x) is a pointer too
//          == accept two object rathen two pointers
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))

#define IsLeaf(x) (!HasChild(x))
// p is pointer now, fuck, what a mess
// whether p has siblings or not
#define sibling(p) (IsLChild(*(p)) ? (x)->parent->rc : (p)->parent->lc)
// siblings to x's parent
// TODO:whatif parent is root?
//      IsLChild(*((x)->parent)) return false
//      goto (x)->parent->parent->lc
//      (x)->parent->parent = nullptr, get error
//      fuck this code
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
// can we assign value to (x).parent->lc in this way?
// isn't (x).parent->lc == *(x)?
// (FromParentTo(x) = something) == ((x).parent->lc = something)?
// what is _root?
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

// TODO: for rand() in template function
//       learn about template and namespace
// using namespace std;

// Node color?
// updata: used for red black tree
typedef enum {RB_RED, RB_BLACK} RBColor;

template <typename T>
struct BinNode
{
    // data
    T data;
    // parent node, left child, right child
    BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc;
    int height;
    // null path length, diffence from height?
    int npl;
    RBColor color;

// Constructor
    BinNode():
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED):
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

// interface
    // Get the number of all childrens 
    int size();
    // Insert as left chlid
    BinNodePosi(T) insertAsLC(T const&);
    // Insert as right chlid
    BinNodePosi(T) insertAsRC(T const&);
    // Get successor of current node
    // TODO: what is successor?
    BinNodePosi(T) succ();
    // traverse by level
    template <typename VST> void travLevel(VST&);
    // Preorder traversal
    template <typename VST> void travPre(VST&);
    // Inorder traversal
    template <typename VST> void travIn(VST&);
    // Postorder traversal
    template <typename VST> void travPost(VST&);

// re-load operator
// TODO: why the parameter is reference rather than pointer? 
    bool operator<(BinNode const& bn) {return data < bn.data;}
    bool operator==(BinNode const& bn) {return data == bn.data;}

};

// insert as left child
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
    // TODO: don't updata child's h and l here?
    return lc = new BinNode(e, this);
}

// insert as right child
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
    return rc = new BinNode(e, this);
}

// Traverse
template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST& visit)
{
    switch(std::rand() % 5)
    {
        case 1: travIn_I1(this, visit); break;
        case 2: travIn_I2(this, visit); break;
        case 3: travIn_I3(this, visit); break;
        case 4: travIn_I4(this, visit); break;
        default: travIn_R(this, visit); break;
    }
}

// Pre-order traversal
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)
{
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_L(x->rc, visit);
}

// updated version
template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S)
{
    while (x)
    {
        visit(x->data);
        if (x->rc) S.push(x->rc);
        x = x->lc;
    }
}

template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit)
{
    Stack<BinNodePosi(T)> S;
    while (true)
    {
        visitAlongLeftBranch(x, visit, S);
        if (S.empty()) break;
        x = S.pop();
    }
}

// Post-order traversal
template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit)
{
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

// TODO: what if push(nullptr)
template <typename T>
static void gotoHLVFL(Stack<BinNodePosi(T)>& S)
{
    while (BinNodePosi(T) x = S.top())
    {
        if (HasLChild(*x))
        {
            if (HasRChild(*x)) S.push(x->rc);
            S.push(x->lc);
        }
        else S.push(x->rc);
    }
    S.pop();
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit)
{
    Stack<BinNodePosi(T)> S;
    if (x) S.push(x);
    while (!S.empty())
    {
        if (S.top() != x->parent) gotoHLVFL(S);
        x = S.pop(); visit(x->data);
    }
}

// Inorder traversal
template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit)
{
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

// updated version
template <typename T, typename VST>
static void visitAlongLeftBranch_In(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S)
{
    while (x)
    {
        S.push(x);
        x = x->lc;
    }
}

// iteration - version 1
template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST& visit)
{
    Stack<BinNodePosi(T)> S;
    while (true)
    {
        visitAlongLeftBranch_In(x, S);
        if (S.empty()) break;
        x = S.pop(); visit(x->data);
        x = x->rc;
    }
}

// iteration - version 2
template <typename T, typename VST>
void tracIn_I2(BinNodePosi(T) x, VST& visit)
{
    Stack<BinNodePosi(T)> S;
    while (true)
    {
        if (x)
        {
            S.push(x);
            x = x->lc;
        }
        else if (!S.empty())
        {
            x = S.pop();
            visit(x->data);
            x = x->rc;
        }
        else break;
    }
}

// iteration - version 3
template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST& visit)
{
    bool backtrack = false;
    while (true)
    {
        if (!backtrack && HasLChilld(*x)) x = x->lc;
        else 
        {
            visit(x->data);
            if (HasRChild(*x))
            {
                x = x->rc;
                backtrack = false;
            }
            else
            {
                if (!(x = x->succ())) break;
                backtrack = true;
            }
        }
    }
}

// traverse by level
template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST& visit)
{
    Queue<BinNodePosi(T)> Q;
    Q.enuqeue(this);
    while(!Q.empty())
    {
        BinNodePosi(T) x = Q.dequeue(); visit(x->data);
        if (HasLChild(*x)) Q.enqueue(x->lc);
        if (HasRChild(*x)) Q.enqueue(x->rc);
    }
}
// direct successor in inorder
template <typename T>
BinNodePosi(T) BinNode<T>::succ()
{
    BinNodePosi(T) s = this;
    if (rc)
    {
        s = rc;
        while (HasLChild(*s)) s = s->lc;
    }
    else
    {
        while (IsRChild(*s)) s = s->parent;
        s = s->parent;
    }
    return s;
}

