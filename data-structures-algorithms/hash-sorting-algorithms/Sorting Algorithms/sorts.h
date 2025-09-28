#ifndef __SORTS_H
#define __SORTS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "list.cpp"

using namespace std;

vector<long> InsertionSort(vector<long> nums);
vector<long> MergeSort(vector<long> nums);
vector<long> HeapSort(vector<long> nums);
void LLSort(ListItem<int> **node);
void splitLL(ListItem<int> **front,ListItem<int> **back, ListItem<int> *head);
ListItem<int>* LLCombine(ListItem<int> *temp1,ListItem<int> *temp2);


#endif