#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
   head = NULL;
   tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    if (otherLinkedList.head == NULL)
    {
        head = tail = NULL;
    }
    else
    {
        head = new ListItem<T>(otherLinkedList.head->value);
        ListItem<T> *temp = otherLinkedList.head->next;
        ListItem<T> *temp2 = head;
        while(temp!=NULL)
        {
            temp2->next = new ListItem<T> (temp->value);
            temp2 = temp2->next;
            temp = temp->next;
        }
        tail = temp2;
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    if(head == NULL)
    {
        return;
    }
    else
    {
        ListItem<T> *temp = head;
        while(head!= NULL)
        {
            ListItem<T> *curr = NULL;
            head = temp->next;
            curr = temp; 
            temp = temp->next;
            curr = NULL;
        }
        temp = NULL;
        tail = NULL;
    }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    ListItem<T> *temp = new ListItem<T>(item);
    if(head == NULL && tail==NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->next = head;
        head->prev = temp;
        temp->prev = NULL;
        head = temp;
    }
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    ListItem<T> *temp = new ListItem<T>(item);
    if(head == NULL && tail == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->prev = tail;
        tail->next = temp;
        temp->next = NULL;
        tail = temp;
    }
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    ListItem<T> *temp = searchFor(afterWhat);
    ListItem<T> *insertN = new ListItem<T>(toInsert);
    if (temp == tail)
    {
        insertN->prev = temp;
        insertN->next = NULL;
        temp->next = insertN;
        tail = insertN;
    }
    else
    {
        insertN->prev = temp;
        insertN->next = temp->next;
        (temp->next)->prev = insertN;
        temp->next = insertN;   
    }
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{   
    return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
    return tail;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{   

    ListItem<T> *temp = head;
    while(temp!=NULL)
    {
        if(temp->value == item)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    ListItem<T> *temp = searchFor(item);
    if(temp == head)
    {
        deleteHead();
    }
    else if (temp == tail)
    {
        deleteTail();
    }
    else
    {
        (temp->prev)->next = temp->next;
        (temp->next)->prev = temp->prev;
        temp = NULL;   
    } 
}

template <class T>
void LinkedList<T>::deleteHead()
{
    ListItem<T> *temp = head;
    if (temp == tail)
    {
        temp = NULL;
        head = NULL;
        tail = NULL;
    }
    else
    {
        head = temp->next;
        temp = NULL;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    ListItem<T> *temp = tail;
    if (temp == head)
    {
        temp = NULL;
        tail = NULL;
        head = NULL;
    }
    else
    {
        tail = temp->prev;
        (temp->prev)->next = NULL;
        temp->prev = NULL;
        temp = NULL;
    }  
}

template <class T>
int LinkedList<T>::length()
{
    ListItem<T> *temp = head;
    int counter = 0;
    while(temp!=NULL)
    {
        temp = temp->next;
        counter++;
    }
    return counter;
}

#endif