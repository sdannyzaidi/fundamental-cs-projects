#ifndef __TREE_CPP
#define __TREE_CPP

#include <iostream>
#include "tree.hpp"
using namespace std;


template <class T, class S>
Tree<T,S>::Tree(node<T,S> *root) {
	this->root = root;
}

template <class T, class S>
node<T,S>* Tree<T,S>::findKey(T key) {

	return findKeyHelper(root,key);
}

template <class T, class S>
node<T,S>* Tree<T,S>::findKeyHelper(node<T,S> *currNode, T key) {
	if (currNode == NULL)
	{
		return NULL;
	}
	else
	{
		if(currNode->key == key)
		{
			return currNode;
		}
		node<T,S> *nodeA = findKeyHelper(currNode->child,key);
		if (nodeA != NULL)
		{
			return nodeA;
		}
		node<T,S> *nodeB = findKeyHelper(currNode->sibling,key);
		if (nodeB != NULL)
		{
			return nodeB;
		}
	}
	return NULL;
}

template <class T, class S>
bool Tree<T,S>::insertChild(node<T,S> *child, T key) {
	node<T,S> *insertKey = findKey(key);
	if (insertKey == NULL)
	{
		return false;
	}
	if (findKey(child->key) != NULL)
	{
		return false;
	}
	if (insertKey->child == NULL)
	{
		insertKey->child = child;
		child->child = NULL;
		child->sibling = NULL;
	}
	else if (insertKey->child != NULL)
	{
		insertKey = insertKey->child;
		while (insertKey->sibling != NULL)
		{
			insertKey = insertKey->sibling;
		}
		insertKey->sibling = child;
		child->child = NULL;
		child->sibling = NULL;
	}
	return true;
}

template <class T, class S>
std::vector<node<T,S>*> Tree<T,S>::getAllChildren(T key) {
	node<T,S> *temp = findKey(key);
	std::vector<node<T,S>*> childern;
	if (temp == NULL)
	{
		return childern;
	}
	else if (temp->child == NULL)
	{
		return childern;
	}
	else if (temp->child != NULL)
	{
		temp = temp->child;
		childern.push_back(temp);
		while(temp->sibling != NULL)
		{
			temp = temp->sibling;
			childern.push_back(temp);
		}
	}
	return childern;
}

template <class T, class S>
int Tree<T,S>::findHeight() {

	return findHeightHelper(root);
}

template <class T, class S>
int Tree<T,S>::findHeightHelper(node<T,S> *currNode) {
	if (currNode == NULL)
	{
		return 0;
	}
	else
	{
		int height =  findHeightHelper(currNode->child);
		int length = findHeightHelper(currNode->sibling);
		height++;
		return height;
	}
	return 0;
}

template <class T, class S>
bool Tree<T,S>::deleteLeaf(T key) {
	node<T,S> *del = findKey(key);
	if (del->child != NULL)
	{
		return false;
	}
	else if(del == root || del == NULL)
	{
		return false;
	}
	else
	{
		deleteLeafHelper(root,key);
	}
	return true;
}

template <class T, class S>
node<T,S>* Tree<T,S>::deleteLeafHelper(node<T,S> *currNode, T key) {
	if (currNode == NULL)
    {
        return NULL;
    }
    else if (currNode->child != NULL)
    {
        if ((currNode->child)->key == key)
        {
            node<T,S>* parent = (currNode->child)->sibling;
            if (parent == NULL)
            {
                delete currNode->child;
                currNode->child=NULL;
            }
            else
            {
            	delete currNode->child;
            	currNode->child=parent;
            }
           return currNode;
        }
    }
    else if (currNode->sibling != NULL)
    {
        if((currNode->sibling)->key==key)
        {
            node<T,S>* parent = currNode->sibling;
            if (parent->sibling == NULL)
            {
                delete parent;
                currNode->sibling = NULL;
            }
            else
            {
                currNode->sibling = parent->sibling;
                delete parent;
            }
            return currNode;
        }
    }
    if (currNode->child != NULL)
	{
		return deleteLeafHelper(currNode->child,key);
	}
    else
	{
		return deleteLeafHelper(currNode->sibling,key);
	}
	return NULL;
}

template <class T, class S>
Tree<T,S>::~Tree() {

	deleteTree(root);
}

template <class T, class S>
void Tree<T,S>::deleteTree(node<T,S> *currNode) {
	if (currNode == NULL)
	{
		return;
	}
	else
	{
		return deleteTree(currNode->child);
		return deleteTree(currNode->sibling);
		delete currNode;
	}
	return;
}

template <class T, class S>
node<T,S>* Tree<T,S>::getRoot() {

	return root;
}

#endif