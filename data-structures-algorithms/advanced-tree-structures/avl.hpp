#include "avl.cpp"

#ifndef __AVL_HPP
#define __AVL_HPP


template <class T, class S>
struct node{
    T key;
    S value; 
    node *left;
    node *right;
    int height;
    
    node (T key, S value){
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};


template <class T, class S>
class AVL {
    node<T,S> *root;
    bool isAVL;
	void deleteAVL(node<T,S>*);
	node<T,S>* searchNodeHelper(node<T,S>*,T);
	node<T,S>* insertNodeHelperBST(node<T,S>*,node<T,S>*);
    node<T,S>* deleteNodeHelperBST(node<T,S>*,T);
    node<T,S>* deleteNodeHelperAVL(node<T,S>*,T);
    node<T,S>* insertNodeHelperAVL(node<T,S>*,node<T,S>*);
	node<T,S>* leftRotation(node<T,S>*);
	node<T,S>* rightRotation(node<T,S>*);
    int subtreeHeight(node<T,S>*);
    int maxHeight(int, int);
    int nodeBalance(node<T,S>*);



public:
    AVL(bool);
    ~AVL();
    void insertNode(node<T,S>*);
    void deleteNode(T k);    
    node<T,S>* searchNode(T k);
    node<T,S>* getRoot();
    int height (node<T,S>* p);
};


#endif