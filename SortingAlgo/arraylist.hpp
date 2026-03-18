#include "list.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#pragma once
using namespace std;

class ArrayList : public List{
    int* array;
    int capacity;
    int s;
    
    public:
    ArrayList(int n){
        s = 0;
        capacity = n;
        array = (int*)malloc(capacity * sizeof(int));
    }
    
    void insert(int num){
        array[s++] = num;
    }
    
    int get(int pos){
        if(pos < 1 || pos > capacity){
            throw logic_error("Invalid position");
        }
        
        return array[pos-1];
    }
    
    void print(){
        for(int i = 0; i<s; i++){
            if(i < s){
                cout << array[i] << " ";
            }
            else{
                cout << "? ";
            }
        }
        cout << endl;
    }
    
    int size(){
        return s;
    }

    void swap(int a, int b){
        int temp = array[a-1];
        array[a-1] = array[b-1];
        array[b-1] = temp;
    }
};