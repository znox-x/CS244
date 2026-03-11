#include <bits/stdc++.h>
#include "arraylist.hpp"
#include "linkedlist.hpp"
#include "entry.hpp"
using namespace std;

class HashMap {
    public:
    LinkedList** list;
    int size;

    HashMap(int n){
        size = n;
        list = (LinkedList**)malloc(size * sizeof(LinkedList*));
        for (int i = 0; i < size; i++){
            list[i] = new LinkedList();
        }
    }

    int add(string key, int value){
        // hash function
        int hashcode = 0;
        int strSize = key.size();
        for (int i = 0; i < strSize; i++){
            hashcode = hashcode + ((int)key[i] * pow(31, strSize-1-i));
        }
        
        // compression function
        int index = hashcode % size;

        // insert
        entry* e = new entry;
        e->key = key;
        e->value = value;
        list[index]->insert(e);

        return index;
    }

    void print(){
        for (int i = 0; i < size; i++){
            cout << "bucketArray[" << i << "]: ";
            list[i]->print();
        }
    }
};