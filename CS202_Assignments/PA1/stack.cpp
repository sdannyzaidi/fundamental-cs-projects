#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
    ListItem<T> *temp = list.getHead();
    ListItem<T> *temp2 = list.getTail();
    temp = NULL;
    temp2 = NULL;
}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
    list = otherStack.list;
}

template <class T>
Stack<T>::~Stack()
{
    while(list.length() != 0)
    {
        list.deleteTail();
    }
}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
    T val = list.getHead()->value;
    return val;
}

template <class T>
T Stack<T>::pop()
{
    T val = list.getHead()->value;
    list.deleteHead();
    return val;
}

template <class T>
int Stack<T>::length()
{
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
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
