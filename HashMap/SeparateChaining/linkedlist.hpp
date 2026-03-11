#include "node.hpp"
#include <cstdlib>
#include <iostream>
#pragma once
using namespace std;

class LinkedList{
    node* create_node(entry* e) {
        node* n = (node*) malloc( sizeof(node) );
        n->element = e;
        n->next = NULL;
        return n;
    }

    public:
    node* head;
    node* tail;
    int index;

    LinkedList() {
        index = 0;
        head = NULL;
        tail = NULL;
    }

        void addTail(entry* e) {
            node* newest = create_node(e);
            if (tail != NULL) {
                tail->next = newest;
            }
            tail = newest;
            if (head == NULL) {
                head = newest;
            }
            index++;
        }

        void insert(entry* e) {
            addTail(e);
        }

        entry* get(int pos) {
            node* currnode = head;
            int count = 0;
            while (currnode != NULL) {
                count++;
                if (pos == count) {
                    return currnode->element;
                } else {
                    currnode = currnode->next;
                }
            }
            return NULL;
        }

        int size() {
            return index;
        }

        void print() {
            node* currnode = head;
            if (head == NULL && tail == NULL) {
                cout << "(empty)" << endl;
                return;
            }
            while (true) {
                string str = currnode->element->key;
                int num = currnode->element->value;

                cout << "(" << str << ", " << num << ")";
                if (currnode == tail) {
                	cout << endl;
                    return;
                }
                cout << " -> ";
                currnode = currnode->next;
            }
        }
};