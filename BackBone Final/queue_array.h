//
// Created by J on 8/31/2021.
//

#ifndef UNTITLED_QUEUEARRAY_H
#define UNTITLED_QUEUEARRAY_H
#include <iostream>
#include <queue>

using namespace std;
template <class type>
class QueueArray
{
private:
    int size = 0;
    queue<type>* q;
public:
    QueueArray<type>(int i);
    ~QueueArray<type>();
    int Enqueue(const type item, const int index);
    int Qsize(int index);
    int Asize();

    int QAsize()
    {
        int s = 0;
        for (int i = 0; i < size; i++)
        {
            s += q[i].size();
        }
        return s;
    }
    type Dequeue()
    {
        //find first non empty queue
        type a;
        for (int i = 0; i < size; i++)
        {
            if (q[i].size() > 0) {
                a = q[i].front();
                q[i].pop();
                break;
            }
        }
        return a;
    }
    type* Qstate(int index);
    queue<type>copyqueue(const queue<type> &Q);
    bool isEmpty()
    {
        if (size == 0) return true;
        else return false;
    }
    queue<type> returnQueue(int index)
    {
        return q[index];
    }
};
template <class type>
QueueArray<type>::~QueueArray()
{
    //empty all queues
    for (int i = 0; i < size; i++)
    {
        for(int j = 0; j < q[i].size(); j++)
        {
            q[i].pop();
        }
    }
    q = nullptr;
}
template <class type>
int QueueArray<type>::Enqueue(const type item, int index)
{
    if (index > size || index == size)//from Andrew Fuller
    {
        return -1;
    }
    else if (size > index)
    {
        q[index].push(item);
        return 1;
    }
    else
    {
        return 0;
    }
}
template <class type>
int QueueArray<type>::Qsize(int index)
{
    int a = q[index].size();
    if (index > size) return -1;
    else return a;
}
template <class type>
int QueueArray<type>::Asize()
{
    return size;
}
template <class type>
QueueArray<type>::QueueArray(int i)
{
    size = i;
    q = new queue<type>[i];
    if( q == NULL)
    {
        cout << "Not enough memory to create the array" << endl;
        exit(-1);
    }
}
template <class type>
type* QueueArray<type>::Qstate(int index) {
    if (index >= size) return nullptr;
    else
    {
        //first we copy the contents of the queue to a new queue. copy_queue is used so the original has no chance of being modified
        queue<type> Q2 = copyqueue(q[index]);
        //now that we have this queue, we can modify it as much as we like!
        //make new array that is the length of q2
        type* arr = NULL;
        arr = new type[q[index].size()];
        for(int i = 0; i < q[index].size(); i++)
        {
            arr[i] = Q2.front();
            Q2.pop();
        }
        //done with that, now return pointer to array
        return arr;
    }
}
template<class type>
queue<type> QueueArray<type>::copyqueue(const queue<type> &Q) {
    //this is here to ensure the original queue doesnt get modifed
    queue<type>Q2 = Q;
    return Q2;
}
// ref1: https://stackoverflow.com/questions/36458741/can-you-set-queues-equal-to-each-other
// Got help from Samuel Walker, Colton Gaines, Andrew Fuller
#endif //UNTITLED_QUEUEARRAY_H