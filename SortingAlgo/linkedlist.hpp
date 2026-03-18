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

        void swap(int a, int b) {
            if (a == b) return;

            node *m = NULL;
            node *m_prev = NULL;
            node *n = NULL;
            node *n_prev = NULL;
            
            node *currnode = head;
            int count = 0;
            while (currnode != NULL) {
                count++;
                if (count == a-1) {
                    m_prev = currnode;
                }
                if (count == a) {
                    m = currnode;
                }
                if (count == b-1) {
                    n_prev = currnode;
                }
                if (count == b) {
                    n = currnode;
                }

                currnode = currnode->next;
            }
            
            if (m == head) {
                if (m->next != n) {
                    n_prev->next = m;
                }

                node* temp = m->next;
                m->next = n->next;
                n->next = temp;
                
                if (n == tail) {
                    tail = m;
                }
                head = n;
            } else {
                if (m->next == n) {
                    m_prev->next = n;
                    m->next = n->next;
                    n->next = m;
                } else {
                    m_prev->next = n;
                    n_prev->next = m;

                    node* temp = m->next;
                    m->next = n->next;
                    n->next = temp;
                }

                if (n == tail) {
                    tail = m;
                }
            }
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