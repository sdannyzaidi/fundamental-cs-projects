#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"
#include <iostream>

HashL::HashL(){
    tableSize = 1000; // you cant change this
    count = 0;
    hashTable = new block*[tableSize];
    for (int i=0; i<tableSize; i++)
    {
        hashTable[i] = NULL;
    }
}

HashL::~HashL(){
    delete [] hashTable;
}

unsigned long HashL :: hash(string value){
    unsigned long hash = bitHash(value);
    //unsigned long hash = polyHash(value);
    unsigned long key = hash%tableSize;
    return key;

}

void HashL::resizeTable(){
	block** prevTable = hashTable;
    int oldSize = tableSize;
	tableSize = tableSize*4;
	hashTable = new block*[tableSize];

	for (int i = 0; i < tableSize; i++)
	{
		hashTable[i] = NULL;
	}

	for (int i = 0; i < oldSize; i++)
	{
		if (prevTable[i] == NULL)
		{	
            continue;
		}
        else
        {
			insert(prevTable[i]->value);
        }
        
	}
	delete [] prevTable;
}

void HashL::insert(string value){
	if (count/tableSize > 0.6)
	{
		resizeTable();
	}

    int key = hash(value);
	block* temp = new block(key, value);
	for (int i =0; i < tableSize; i++)
	{
		if (hashTable[key] != NULL && hashTable[key]->key != -1)
		{
			key += 1;
            if (key == tableSize)
            {
                key = key % tableSize;
            }
		}
		else
		{
			hashTable[key] = temp;
			count++;
			return;
		}
	}
}

void HashL::deleteWord(string value){
	block* temp = lookup(value);
	if (temp == NULL)
	{
        return;
	}
    else
    {
		temp->value = "-1";
		temp->key = -1;
    }
    
}
block* HashL::lookup(string value){
    block *temp = NULL;
    int key = hash(value);
    while (hashTable[key] != NULL)
	{	
		if (key == tableSize)
		{
			key = 0;
		}
		if (hashTable[key]->value == value)
		{
			temp = hashTable[key];
            return temp;
		}
		else
        {
		    key++;
        }
	}
	return temp;
}
#endif
