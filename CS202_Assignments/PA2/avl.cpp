#ifndef __AVL_CPP
#define __AVL_CPP

#include <iostream>
#include "avl.hpp"
using namespace std;


template <class T, class S>
AVL<T,S>::AVL(bool isAVL){
	this->root = NULL;
    this->isAVL = isAVL;
}

template <class T, class S>
AVL<T,S>:: ~AVL(){
    deleteAVL(root);
}

template <class T, class S>
void AVL<T,S>::deleteAVL(node<T,S> *currNode) {
	if (currNode == NULL)
	{
		return;
	}
	else
	{
		return deleteAVL(currNode->left);
		return deleteAVL(currNode->right);
		delete currNode;
	}
	return;
}

template <class T, class S>
int AVL<T,S> :: height (node<T,S>* p){
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        int heightLeft = height(p->left);
        heightLeft++;
        int heightRight = height(p->right);
        heightRight++;
        if (heightLeft < heightRight)
        {
            return heightRight;
        }
        else if (heightRight < heightLeft)
        {
            return heightLeft;
        }
        else
        {
            return heightLeft;
        }
        
    }
    return 0;
}

template <class T, class S>
void AVL<T,S> :: insertNode(node<T,S>* newNode){
    if (!(isAVL))
    {
        root = insertNodeHelperBST(root,newNode);
    }
    else
    {
        root = insertNodeHelperAVL(root,newNode);
    }
    return;
}

template <class T, class S>
node<T,S>* AVL<T,S>::leftRotation(node<T,S>* currNode){

    node<T,S> *temp = currNode->right;  
    node<T,S> *temp2 = temp->left;
    temp->left = currNode;  
    currNode->right = temp2;  
    currNode->height = maxHeight(subtreeHeight(currNode->left), subtreeHeight(currNode->right)) + 1;  
    temp->height = maxHeight(subtreeHeight(temp->left), subtreeHeight(temp->right)) + 1;  
    return temp;
}


template <class T, class S>
node<T,S>* AVL<T,S>::rightRotation(node<T,S>* currNode){
    node<T,S> *temp = currNode->left;  
    node<T,S> *temp2 = temp->right;  
    temp->right = currNode;  
    currNode->left = temp2;  
    currNode->height = maxHeight(subtreeHeight(currNode->left), subtreeHeight(currNode->right)) + 1;  
    temp->height = maxHeight(subtreeHeight(temp->left), subtreeHeight(temp->right)) + 1;  
    return temp;
}

template <class T, class S>
int AVL<T,S>::subtreeHeight(node<T,S> *currNode){
    int height = 0;
    if (currNode == NULL)
    {
        height = 0;
    }
    else
    {
        height = currNode->height;
    }
    return height;
}

template <class T, class S>
int AVL<T,S>::maxHeight(int hL, int hR){
    int max = 0;
    if (hL > hR)
    {
        max = hL;
    }
    else
    {
        max = hR;
    }
    return max;
}

template <class T, class S>
int AVL<T,S>::nodeBalance(node<T,S>* currNode){
    int difference = 0;
    if (currNode == NULL)
    {
        difference = 0;
    }
    else
    {
        difference = subtreeHeight(currNode->left) - subtreeHeight(currNode->right);
    }
    return difference;
}

template <class T, class S>
node<T,S>* AVL<T,S>::insertNodeHelperAVL(node<T,S>* currNode,node<T,S>* newNode){
    if (currNode == NULL)
    {
        currNode = newNode;
        return currNode;
    }
    if (newNode->key < currNode->key)
    {
        currNode->left = insertNodeHelperAVL(currNode->left,newNode);
    }
    else if (newNode->key > currNode->key)
    {
        currNode->right = insertNodeHelperAVL(currNode->right,newNode);
    }
    else
    {
        return currNode;
    }
    currNode->height = 1 + maxHeight(subtreeHeight(currNode->left),subtreeHeight(currNode->right));  
    int getBalance = nodeBalance(currNode); 
  
    // LL Case  
    if ((getBalance > 1) && (newNode->key < (currNode->left)->key))
    {
        return rightRotation(currNode);  

    }
    // RR Case  
    if ((getBalance < -1) && (newNode->key > (currNode->right)->key))  
    {
        return leftRotation(currNode);  

    }
    // LR Case  
    if ((getBalance > 1) && (newNode->key > (currNode->left)->key))  
    {  
        currNode->left = leftRotation(currNode->left);  
        return rightRotation(currNode);  
    }
    // RL Case  
    if ((getBalance < -1) && (newNode->key < (currNode->right)->key))  
    {  
        currNode->right = rightRotation(currNode->right);  
        return leftRotation(currNode);  
    }  
    return currNode;
}

template <class T, class S>
node<T,S>* AVL<T,S>::insertNodeHelperBST(node<T,S>* currNode,node<T,S>* newNode){
    if (currNode == NULL)
    {
        currNode = newNode;
        return currNode;
    }
    if (newNode->key < currNode->key)
    {
        currNode->left = insertNodeHelperBST(currNode->left,newNode);
    }
    else if (newNode->key > currNode->key)
    {
        currNode->right = insertNodeHelperBST(currNode->right,newNode);
    }
    else
    {
        return currNode;
    }
    return currNode;
}

template <class T, class S>
node<T,S>* AVL<T,S> :: searchNode(T key){
    return searchNodeHelper(root,key);
}

template <class T, class S>
node<T,S>* AVL<T,S>::searchNodeHelper(node<T,S> *currNode, T key){
    if (currNode == NULL)
    {
        return NULL;
    }
    else
    {
        if (currNode->key == key)
        {
            return currNode;
        }
		node<T,S> *nodeA = searchNodeHelper(currNode->left,key);
		if (nodeA != NULL)
		{
			return nodeA;
		}
		node<T,S> *nodeB = searchNodeHelper(currNode->right,key);
		if (nodeB != NULL)
		{
			return nodeB;
		}
    }
    return NULL;
}


template <class T, class S>
void AVL<T,S>::deleteNode(T k){
    if (!(isAVL))
    {
        root = deleteNodeHelperBST(root,k);
    }
    else
    {
        root = deleteNodeHelperAVL(root,k);
    }
    return;
}

template <class T, class S>
node<T,S>* AVL<T,S> ::deleteNodeHelperAVL(node<T,S> *currNode, T key){
    if (currNode == NULL)
    {
        return currNode;
    }
    if (key < currNode->key)
    {
        currNode->left = deleteNodeHelperAVL(currNode->left,key);
    }
    else if (key > currNode->key)
    {
        currNode->right = deleteNodeHelperAVL(currNode->right,key);
    }
    else
    {
		if( (currNode->right == NULL) || (currNode->left == NULL) ) 
		{ 
			node<T,S> *temp = currNode->left ? currNode->left : currNode->right; 

			if (temp == NULL) 
			{ 
				temp = currNode; 
				currNode = NULL; 
			}
			else
            {
                currNode = temp;
			    temp = NULL; 
            }
        }
		else
		{ 
            node<T,S> *temp = currNode->right;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }  
			currNode->key = temp->key;  
			currNode->right = deleteNodeHelperAVL(currNode->right, temp->key); 
		}

    }
    if(currNode == NULL)
    {
        return currNode;
    }
    currNode->height = 1 + maxHeight(subtreeHeight(currNode->left),subtreeHeight(currNode->right));  
    int getBalance = nodeBalance(currNode); 
  
    // LL Case  
    if ((getBalance > 1) && (nodeBalance(currNode->left) >= 0))
    {
        return rightRotation(currNode);  
    }   
    // RR Case  
    if ((getBalance < -1) && (nodeBalance(currNode->left) <= 0))
    {
        return leftRotation(currNode);  

    }
    // LR Case  
    if ((getBalance > 1) && (nodeBalance(currNode->right) < 0))  
    {  
        currNode->left = leftRotation(currNode->left);  
        return rightRotation(currNode);  
    }  
  
    // RL Case  
    if ((getBalance < -1) && (nodeBalance(currNode->right) > 0))  
    {  
        currNode->right = rightRotation(currNode->right);  
        return leftRotation(currNode);  
    }  
    return currNode;   
}

template <class T, class S>
node<T,S>* AVL<T,S> ::deleteNodeHelperBST(node<T,S> *currNode, T key){

    if (currNode == NULL)
    {
        return currNode;
    }  
    if (key < currNode->key)
    {
        currNode->left = deleteNodeHelperBST(currNode->left, key);
    }
    else if (key > currNode->key)
    {
        currNode->right = deleteNodeHelperBST(currNode->right, key);
    } 
    else
    {  
        node<T,S> *temp;
        if (currNode->left == NULL) 
        { 
            temp = currNode;
            currNode = currNode->right;
            delete temp;
        } 
        else if (currNode->right == NULL) 
        { 
            temp = currNode;
            currNode = currNode->left;
            delete temp;
        }
        else
        {
            temp = currNode->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            temp->left = currNode->left;
            temp = currNode;
            currNode = currNode->right;
            delete temp;
        }
    } 
    return currNode; 
}

template <class T, class S>
node<T,S>* AVL<T,S>::getRoot(){
    return root;
}

#endif