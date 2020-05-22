#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"
#include <iostream>

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    int vLength = nums.size();
    int arr[vLength];
    for (int i=0; i<vLength; i++)
    {
        arr[i] = nums[i];
    }
    nums.clear();
    for (int i=1; i<vLength; i++)
    {
        int num = arr[i];
        int check = i - 1;
        while(arr[check] > num && check >= 0)
        {
            arr[check + 1] = arr[check];
            check--;
        }
        arr[check + 1] = num;
    }
    for(int i=0; i<vLength; i++)
    {
        nums.push_back(arr[i]);
    }
    return nums;
}

//=====================================================================================
/*
Since I was getting a lot of segmentation faults I took some help from a youtube tutorial to 
implement this mergesort algorithm. I have a good understanding of how it works just took a 
little help from internet when I got stuck.
*/
vector<long> MergeSort(vector<long> nums)
{
    int vLength = nums.size();
    List<int> sortList;
    for(int i=0; i<vLength; i++)
    {
        sortList.insertAtTail(nums[i]);
    }
    nums.clear();
    ListItem<int> * headptr = sortList.getHead();
    LLSort(&headptr);
    for(int i=0; i<vLength; i++)
    {
        nums.push_back(headptr->value);
        headptr = headptr->next;
    }
    return nums;
}

void LLSort(ListItem<int> **node)
{
    ListItem<int> *head = *node;
    ListItem<int> *temp1 = NULL;
    ListItem<int> *temp2 = NULL;

    if(head==NULL || head->next==NULL)
    {
        return;
    }
    splitLL(&temp1,&temp2,head);

    LLSort(&temp1);
    LLSort(&temp2);

    *node = LLCombine(temp1,temp2);
}

void splitLL(ListItem<int> **front,ListItem<int> **back, ListItem<int> *head)
{

	ListItem<int> *ahead; 
	ListItem<int> *behind; 
	if(head == NULL || head->next == NULL)
    {
        *front = head;
        *back = NULL;
    }
    else
    {
        behind = head;
        ahead = head->next;
	    while (ahead != NULL) 
        { 
		    ahead = ahead->next; 
		    if (ahead != NULL)
            { 
			    behind = behind->next; 
			    ahead = ahead->next; 
		    } 
	    } 
    }
	*front = head; 
	*back = behind->next; 
	behind->next = NULL;
}

ListItem<int>* LLCombine(ListItem<int> *temp1,ListItem<int> *temp2)
{
    ListItem<int>* finalLL = NULL;
    if(temp2 == NULL)
    {
        return temp1;
    }
    else if(temp1 == NULL)
    {
        return temp2;
    }
    if(temp1->value >= temp2->value)
    {
        finalLL = temp2;
        finalLL->next = LLCombine(temp1, temp2->next);
    }
    else
    {
        finalLL = temp1;
        finalLL->next = LLCombine(temp1->next, temp2);
    }
    return finalLL;
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{

}

#endif