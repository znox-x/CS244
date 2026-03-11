#include "list.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#pragma once
using namespace std;

class ArrayList : public List{
    int* array;
    int s;
    
    public:
    ArrayList(int n){
        s = n;
        array = (int*)malloc(s * sizeof(int));
    }
    
    void insert(int num){
        array[s++] = num;
    }
    
    int get(int pos){
        if(pos < 1 || pos > s){
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
};