#include<time.h>

#include "./BinTree.h"
typedef BinTree<char> PFCTree;

#include "./vector/vector.h"
typedef Vector<PFCTree*> PFCForest;

// Not defined yet
// #include "../Bitmap/Bitmap.h"
// #include "../Skiplist/Skiplist.h"

// what does 0x80 - 0x20 stands for?
#define N_CHAR (0x80 - 0x20)

PFCForest* initForest()
{
    PFCForest* forest = new PFCForest;
    for (int i = 0; i < N_CHAR; i++)
    {
        forest->insert(i, new PFCTree());
        (*forest)[i]->insertAsRoot(0x20 + i);
    }
    return forest;
}

PFCTree* generateTree(PFCForest* forest)
{
    // define rand seed
    srand((unsigned int) time(NULL));
    while (1 < forest->size())
    {
        PFCTree* s = new PFCTree; s->insertAsRoot('^');
        Rank r1 = rand() % forest->size();
        s->attachAsLC(s->root(), (*forest)[r1]);
        forest->remove(r1);
        Rank r2 = rand() % forest->size();
        s->attachAsRC(s->root(), (*forest)[r2]);
        forest->remove(r2);
        forest->insert(forest->size(), s);
    }
    return (*forest)[0];
}

// TODO: missing bitmap and pfctable
// 5/31 - preorder traversal
//        bit map is used to record the nth node is left child or right child
//        bits2string method is used to create binary string using lenght and bitmap's value - true, false
//        bitmap, pfctable not implemented yet
void generateCT(Bitmap* code, int length, PFCTable* table, BinNodePosi(char) v)
{
    if (ISLeaf(*v)) {table->put(v->data, code->bits2string(length)); return;}
    if (HasLChild(*v)) {code->clear(length); generateCT(code, length + 1, table, v->lc);}
    if (HasRChild(*v)) {code->set(length); generateCT(code, length + 1, table, v->rc));}
}

PFCTable* generateTable(PFCTree* tree)
{
    PFCTable* table = new PFCTable;
    Bitmap* code = new Bitmap;
    generateCT(code, 0, table, tree->root());
    release(code); return table;
}

// encode string to binary code
int encode(PFCTAble* table, Bitmap& codeString, char* s)
{
    int n = 0;
    for (size_t m = strlen(s), i = 0; i < m; i++)
    {
        char** pCharCode = table->get(s[i]);
        if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a');
        if (!pCharCode) pCharCode = table->get(' ');
        printf("%s", *pCharCode);
        for (size_t m = strlen(*pcharCode), j = 0; j < m; j++)
        {
            '1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
        }
    }
    return n;
}

// decode binary string
void decode(PFCTree* tree, Bitmap& code, int n)
{
    BinNodePosi(char) x = tree->root();
    for (int i = 0; i < n; i++)
    {
        x = code.test(i) ? x->rc : x->lc;
        if (IsLeaf(*x)) {printf("%c", x->data); x = tree->root();}
    }
}


int main(int argc, char* argv[])
{
    PFCForest* forest = initForest();
    PFCTree* tree = generateTree(forest); release(forest);
    PFCTable* table = generateTable(tree);
    for (int i = 1; i < argc; i++)
    {
        Bitmap  codeString;
        int n = encode(table, codeString, argv[i]);
        decode(tree, codeString, n);
    }
    release(table); release(tree); return 0;
}