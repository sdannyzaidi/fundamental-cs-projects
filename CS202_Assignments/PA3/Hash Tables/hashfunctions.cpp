#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 15){
    unsigned long polyHash = 0;
    int length = value.length();
    unsigned long num = 1;
    for(int i=0; i<=length; i++)
    {
        num = a * num;
        polyHash += value[i]* num;
    }
    return polyHash;
}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
    unsigned long bitHash = 0;
    int length = value.length();
    for(int i=0; i<=length; i++)
    {
        bitHash ^= (bitHash << 5) + (bitHash >> 2) + value[i];
    }
    return bitHash;

}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
    unsigned long divFun = hash%size;
    return divFun;

}
//you may write your own program to test these functions.
#endif