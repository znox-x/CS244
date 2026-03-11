#include "list.hpp"
#include "node.hpp"
#include <cstdlib>
#include <iostream>
#pragma once
using namespace std;

class LinkedList : public List {
    node* create_node(int num) {
        node* n = (node*) malloc( sizeof(node) );
        n->element = num;
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

        void addTail(int num) {
            node* newest = create_node(num);
            if (tail != NULL) {
                tail->next = newest;
            }
            tail = newest;
            if (head == NULL) {
                head = newest;
            }
            index++;
        }

        void insert(int num) {
            addTail(num);
        }

        int get(int pos) {
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
            return -1;
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
                cout << currnode->element;
                if (currnode == tail) {
                	cout << endl;
                    return;
                }
                cout << " -> ";
                currnode = currnode->next;
            }
        }
};