#include "../list/list.h"
template <typename T>
// TODO: use array to implement queue
class Queue: public List<T>
{
public:
    void enqueue(T const& e) {this->insertAsLast(e);}
    T dequeue() {return this->remove(this->first());}
    T& front() {return this->first()->data;}
};

// void RoundRobin()
// {
//     Queue Q(clients);
//     While (!ServiceClosed())
//     {
//         e - Q.dequeue();
//         server(e);
//         Q.enqueue(e);
//     }
// }

struct Customer {int window; unsigned int time;};

int bestWindow(Queue<Customer> windows[], int nWin)
{
    int minSize = windows[0].size(), optWin = 0;
    for (int i = 1; i < nWin; i++)
    {
        if (minSize > windows[i].size())
        {
            minSize = windows[i].size(); optWin = i;
        }
    }
    return optWin;
}

void simulate(int nWin, int servTime)
{
    Queue<Customer>* windows = new Queue<Customer>[nWin];
    for (int now = 0; now < servTime; now++)
    {
        if (rand() % (1 + nWin))
        {
            Customer c; c.time = 1 + rand() % 98;
            c.window = bestWindow(windows, nWin);
            windows[c.window].enqueue(c);
        }
    }
    delete [] windows;
}