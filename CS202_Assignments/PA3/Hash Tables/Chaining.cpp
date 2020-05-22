#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
    tableSize = size;
    hashTable = new LinkedList<string>[tableSize];
}
HashC::~HashC(){
    delete hashTable;
}

unsigned long HashC :: hash(string input){
    unsigned long hash = polyHash(input);
    //unsigned long hash = bitHash(input);
    unsigned long key = hash%tableSize;
    return key;
}

void HashC::insert(string word){
    unsigned long key = hash(word);
    hashTable[key].insertAtHead(word);
    return;
} 

ListItem<string>* HashC :: lookup(string word){
    unsigned long key = hash(word);
    return hashTable[key].searchFor(word);
}

void HashC :: deleteWord(string word){
    unsigned long key = hash(word);
    hashTable[key].deleteElement(word);
    return;
}


#endif