#include "linkedlist.hpp"
#include "arraylist.hpp"
#include <iostream>
#include <cmath>
using namespace std;

List* mergeSort(LinkedList* list){
    // base case: list size is 1
    if(list->size() <= 1){
        return list;
    }

    // two SLL for division of list
    List* left = new LinkedList();
    List* right = new LinkedList();

    // finding the index on where to split the list
    int mid = ceil(list->size()/2.0);

    // initialization for the loop (curr for traversing, ctr for counting index)
    node* curr = list->head;
    int ctr = 1;

    // looping through the list while assigning left- and right- head and tail by pointing it to the nodes in the list
    while (curr){
        if (ctr == 1){
            ((LinkedList*)left)->head = curr;
        }
        if (ctr == mid){
            ((LinkedList*)left)->tail = curr;
        }
        if (ctr == mid+1){
            ((LinkedList*)right)->head = curr;
        }
        if (ctr == list->size()){
            ((LinkedList*)right)->tail = curr;
        }

        curr = curr->next;
        ctr++;
    }

    // updating left and right SLL tails and sizes
    ((LinkedList*)left)->tail->next = NULL;
    ((LinkedList*)right)->tail->next = NULL;
    ((LinkedList*)left)->index = mid;
    ((LinkedList*)right)->index = list->size() - mid;

    // recursion calls
    cout << "My left list: ";
    left->print();
    left = mergeSort((LinkedList*)left);

    cout << "My right list: ";
    right->print();
    right = mergeSort((LinkedList*)right);

    // a sorted SLL to store the sorted list
    List* sorted = new LinkedList();

    // initialization of left, right, and sorted nodes for traversing their respective lists inside the loop
    node* l_curr = ((LinkedList*)left)->head;
    node* r_curr = ((LinkedList*)right)->head;
    node* s_curr = ((LinkedList*)sorted)->head;

    /* loop that runs until one of the lists have all of their nodes stored in the sorted list
        logic:  if left<right, s_curr will store the node(l_curr) and vice versa
                loop will update sorted->head if it is the first node to be added
                if not, then the node will be stored in the s_curr's next to connect it
    */
    while (l_curr && r_curr){
        if (l_curr->element < r_curr->element){
            if (!s_curr){
                s_curr = l_curr;
                ((LinkedList*)sorted)->head = s_curr;
            } else {
                s_curr->next = l_curr;
                s_curr = s_curr->next;
            }
            l_curr = l_curr->next;
        } else {
            if (!s_curr){
                s_curr = r_curr;
                ((LinkedList*)sorted)->head = s_curr;
            } else {
                s_curr->next = r_curr;
                s_curr = s_curr->next;
            }
            r_curr = r_curr->next;
        }
    }

    // connect the remaining nodes (either in the left/right list) to the sorted list and update the sorted list's tail and index
    if (l_curr){
        s_curr->next = l_curr;
        ((LinkedList*)sorted)->tail = ((LinkedList*)left)->tail;
    }
    if (r_curr){
        s_curr->next = r_curr;
        ((LinkedList*)sorted)->tail = ((LinkedList*)right)->tail;
    }
    ((LinkedList*)sorted)->index = list->size();

    cout << "Sorted: ";
    sorted->print();
    return sorted;
}

List* mergeSort(ArrayList* list){
    
}