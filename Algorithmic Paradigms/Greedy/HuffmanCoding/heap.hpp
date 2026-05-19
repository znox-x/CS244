#include "node.hpp"
#include <iostream>
#include <climits>
using namespace std;
class Heap {
	public:
	node* array[25];
	int s = 0;
	
    // TODO insert
	void insert(node* n) {
        array[s++] = n;
        
        // bubble-up
        int i = s-1;
        while (i > 0) {
            if (array[i]->weight < array[(i-1)/2]->weight) {
                node* temp = array[i];
                array[i] = array[(i-1)/2];
                array[(i-1)/2] = temp;
                
                i = (i-1)/2;
            } else {
                break;
            }
        }
	}

    // TODO removeMin
	node* removeMin() {
	    node* min = array[0];
	    array[0] = array[--s];
	    
	    // bubble-down
	    int i = 0;
	    while (true) {
	        int left = (2*i+1 < s) ? 2*i+1 : -1;
	        int right = (2*i+2 < s) ? 2*i+2 : -1;
	        int smallest = i;
	        
	        if (left != -1) {
	            if (array[left]->weight < array[smallest]->weight) {
	                smallest = left;
	            }
	        }
	        if (right != -1) {
	            if (array[right]->weight < array[smallest]->weight) {
	                smallest = right;
	            }
	        }
	        if (smallest == i)  break;
	        
	        node* temp = array[i];
            array[i] = array[smallest];
            array[smallest] = temp;
	        
	        i = smallest;
	    }
	    
	    array[s] = nullptr;
		return min;
	}

    // TODO size
	int size() {
		return s;
	}
};