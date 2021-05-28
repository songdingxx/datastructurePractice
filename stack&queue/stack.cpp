#include "../vector/vector.h"

// TODO: implement stack using array
template <typename T> 
class Stack: public Vector<T>
{
public:
    // push elements to stack
    void push(T const& e) {insert(size(), e);}
    // pop out the top element
    T pop() {return remove(size() - 1);}
    // return last element
    T& top() {return (*this)[size() - 1];}
};

// convert to n base number
// version 1
void convert(Stack<char>& S, __int64 n, int base)
{
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if (0 < n)
    {
        S.push(digit[n % base]);
        convert(S, n / base, base);
    }
}

// version 2
void convert(Stack<char>& S, __int64 n, int base)
{
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    while (n > 0)
    {
        int remainder = (int)(n % base); S.push(digit[remainder]);
        n /= base;
    }
}

// parenthesis match
// Divide and conquer
// O(n^2)
// Can be done in O(n)
void trim(const char exp[], int& lo, int& hi)
{
    while((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')')) lo++;
    while((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')')) hi--;
}

int divide(const char exp[], int lo, int hi)
{
    int mi = lo; int crc = 1;
    while((0 < crc) && (++mi < hi))
    {
        if (exp[mi] == ')') crc--;
        if (exp[mi] == '(') crc++;
    }
    return mi;
}

bool paren(const char exp[], int lo, int hi)
{
    trim(exp, lo, hi); if (lo > hi) return true;
    if (exp[lo] != '(') return false;
    if (exp[hi] != ')') return false;
    int mi = divide(exp, lo, hi);
    return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
}

// by iteration
bool paren(const char exp[], int lo, int hi)
{
    Stack<char> S;
    for (int i = lo; i < hi; i++)
    {
        switch(exp[i])
        {
            case '(': case '[': case '{': S.push(exp[i]); break;
            case ')': if ((S.empty()) || ('(' != S.pop())) return false; break;
            case ']': if ((S.empty()) || ('[' != S.pop())) return false; break;
            case '}': if ((S.empty()) || ('{' != S.pop())) return false; break;
            default: break;
        }
    }
    return S.empty();
}

#define N_OPTR 9 //运算符总数
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
//加、减、乘、除、乘斱、阶乘、左括号、右括号、起始符不终止符
const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [弼前]
/* |-------------------- 弼 前 运 算 符 --------------------| */
/*          +    -    *    /    ^    !    (    )   \0 */
/* -- + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* |  - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* 栈 * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 顶 / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 运 ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
/* 算 ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
/* 符 ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
/* |  ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* --\0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

// TODO: implement those functions
float evaluate(char* S, char*& RPN)
{
    Stack<float> opnd; Stack<char> optr;
    optr.push('\0');
    while (!optr.empty())
    {
        if (isdigit(*S))
        {
            readNumber(S, opnd); append(RPN, opnd.top());
        }
        else
        {
            switch(orderBetween(optr.top(), *S))
            {
                case '<':
                    optr.push(*S); S++;
                    break;
                case '=':
                    optr.pop(); S++;
                    break;
                case '>':
                    {
                        char op = optr.pop(); append(RPN, op);
                        if ('!' == op)
                        {
                            float pOpnd = opnd.pop();
                            opnd.push(calcu(op, pOpnd));
                        }
                        else
                        {
                            float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
                            opnd.push(calcu(pOpnd1, op, pOpnd2));
                        }
                    }
                    break;
                default: exit(-1);
            }
        }
        return opnd.pop();
    }
}

// Reverse polish notation
// TODO: Implete this function
// rpnEvaluation(expr)
// 输入：RPN表达式expr（假定询法正确）
// 输出：表达式数值
// {
//  引入栈S，用以存放操作数;
//  while (expr尚未扫描完毕) {
//  从expr中读入下一元素x;
//  if (x是操作数) 将x压入S;
//  else { //x是运算符
//  从栈S中弹出运算符x所需数目癿操作数;
//  对弹出癿操作数实斲x运算，幵将运算结枅重新压入S;
//  } //else
//  } //while
//  迒回栈顶; //也是栈底
// }

// n queens
struct Queen
{
    int x, y;
    Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
    bool operator==(Queen const& q) const
    {
        return 
            (x == q.x)
            || (y == q.y)
            || (x + y == q.x + q.y)
            || (x - y == q.x - q.y);
    }
    bool operator!=(Queen const& q) const {return !(*this == q);}
};

void placeQueens(int N)
{
    Stack<Queen> solu;
    Queen q (0, 0);
    do
    {
        if (N <= solu.size() || N <= q.y)
        {
            q = solu.pop(); q.y++;
        }
        else {
            while ((q.y < N) && (0 <= solu.find(q)))
            {
                q.y++;
                // wtf is nCheck?
                // nCheck++;
            }
            if (N > q.y)
            {
                solu.push(q);
                if (N <= solu.size()) 
                    // wtf is nSolu? count solutions.
                    // nSolu++;
                q.x++; q.y = 0;
            }
        }
    // TODO: when it's gonna break?
    // q.x = 0 and q.x > N
    } while((0 < q.x) || (q.y < N));
}

// Find path
// unit's status
typedef enum {AVAILABLE, ROUTE, BACKRACKED, WALL} Status;

// directions
typedef enum {UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN;

inline ESWN nextESWN(ESWN eswn) {return ESWN(eswn + 1);}

struct Cell
{
    int x, y; Status status;
    ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];

// look for neighbors
inline Cell* neighbor(Cell* cell)
{
    switch(cell->outgoing)
    {
        case EAST: return cell + LABY_MAX;
        case SOUTH: return cell + 1;
        case WEST: return cell - LABY_MAX;
        case NORTH: return cell - 1;
        default: exit(-1);
    }
}

inline Cell* advance(Cell* cell)
{
    Cell* next;
    switch(cell->outgoing)
    {
        // TODO: why we don't need to overlaod + here? what does cell + int mean?
        case EAST: next = cell + LABY_MAX; next->incoming = WEST; break;
        case SOUTH: next = cell + 1; next->incoming = NORTH; break;
        case WEST: next = cell - LABY_MAX; next->incoming = EAST; break;
        case NORTH: next = cell - 1; next->incoming = SOUTH; break;
        default: exit(-1);
    }
    return next;
}

bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t)
{
    if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false;
    Stack<Cell*> path;
    s->incoming = UNKNOWN; s->status = ROUTE; path.push(s);
    do
    {
        Cell* c = path.top();
        if (c == t) return true;
        while (NO_WAY > (c->outgoing = nextESWN(c->outgoing)))
        {
            if (AVAILABLE == neighbor(c)->status) break;
        }
        if (NO_WAY <= c->outgoing)
        {
            // Why we assign value to c here?
            c->status = BACKRACKED; c = path.pop();
        }
        else
        {
            path.push(c = advance(c)); c->outgoing = UNKNOWN; c->status = ROUTE;
        }
    } while (!path.empty());
    return false;
}