#include <iostream>
#include "node.hpp"
using namespace std;

class B24Tree {
    node* root;

    /* a helper function that searches 
    (1) which node the key must be inserted to; or
    (2) where the node containing the key is located
    */
    node* search(int num, node* n) {
        // condition: when root is null
        if (n == nullptr) {
            return nullptr;
        }

        // loop checking if num is less than the keys inside node* n
        // if num < keys[i], checks first if child #i exists
        //      if true, recursively calls the function but using child #i as the node to search
        //      else, returns the current node, meaning num must be in this node
        for (int i = 0; i < n->size; i++) {
            if (num < n->keys[i]) {
                if (n->children[i]) {
                    return search(num, n->children[i]);
                }
                return n;
            }
        }

        // necessary if above loop code does not satisfy
        // condition: checks if the num > the last key of node
        //      if true, calls the same function but passing the last children node
        //      else, returns the current node
        if (num > n->keys[n->size-1]) {
            if (n->children[n->size]) {
                return search(num, n->children[n->size]);
            }
            return n;
        }

        // a return for when num exists inside the node keys
        return n;
    }

    public:
    B24Tree() {
        root = nullptr;
    }

    bool insert(int num) {
        node* curr = search(num, root);

        if (curr == nullptr) {
            node* n = new node;
            n->parent = nullptr;
            n->insertKeyAt(num, 0);
            root = n;
            return true;
        }

        if (curr->contains(num)) {
            return false;
        }

        for (int i = 0; i < curr->size; i++) {
            if (num < curr->keys[i]) {
                curr->insertKeyAt(num, i);
                break;
            }
        }
        if (num > curr->keys[curr->size-1]) {
            curr->insertKeyAt(num, curr->size);
        }

        return true;
    }

    bool remove(int num) {
        return false;
    }

    void print() {
        node* curr = root;
        
        if (!curr) {
            cout << "EMPTY" << endl;
            return;
        }

        string prefix = "";
        while (curr->children[0]) {
            if (curr->parent == nullptr) {
                cout << "Root: ";
            } else {
                prefix = prefix + "\t";
            }

            
        }
    }
};