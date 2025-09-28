#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
    ListItem<T> *temp = list.getHead();
    ListItem<T> *temp2 = list.getTail();
    temp = NULL;
    temp2 = NULL;
}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
    list = otherQueue.list;
}

template <class T>
Queue<T>::~Queue()
{
    while(list.length() != 0)
    {
        list.deleteTail();
    }
}

template <class T>
void Queue<T>::enqueue(T item)
{
    list.insertAtTail(item);  
}

template <class T>
T Queue<T>::front()
{
    T val = list.getHead()->value;
    return val;
}

template <class T>
T Queue<T>::dequeue()
{
    T val = list.getHead()->value;
    list.deleteHead();
    return val;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
    if(!(list.length()))
    {
        return true;
    }
    else
    {
        return false;
    }
}


#endif
