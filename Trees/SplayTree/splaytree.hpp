#include <iostream>
#include "node.hpp"
#include "binarytree.hpp"
using namespace std;

class SplayTree : public BinaryTree{
    BinaryTree* tree;

    // --- HELPER METHODS ---

    // accepts a node that will be splayed to the root
    void splay (node* x) {
        // ends recursion when the node passed is at the root
        if (x == tree->getRoot())   return;

        node* y = x->parent;
        node* z = y->parent;

        if (x == y->left) {
            if (!z) {
                zig_right(x, y);
            } else if (y == z->left) {
                
            }
        }
    }

    // rotation helpers
    void zig_left(node* x, node* y) {
        
    }

    void zig_right(node* x, node* y) {

    }

    void zig_zig_left(node* x, node* y, node* z) {
        zig_left(y, z);
        zig_left(x, y);
    }

    void zig_zig_right(node* x, node* y, node* z) {
        zig_right(y, z);
        zig_right(x, y);
    }

    void zig_zag_left(node* x, node* y) {
        
    }

    void zig_zag_right(node* x, node* y) {

    }

    public:
    SplayTree() {
        tree = new BinaryTree;
    }

    bool search(int num) {
        bool isFound = false;
        node* curr = tree->getRoot();
        while (curr) {
            if (num < curr->elem) {
                if (curr->left)     curr = curr->left;
                else                break;
            } else if (num > curr->elem) {
                if (curr->right)    curr = curr->right;
                else                break;
            } else {
                isFound = true;
                break;
            }
        }

        splay(curr);
        return isFound;
    }

    int insert(int num) {

    }

    int remove(int num) {

    }

    void print() {
        tree->print();
    }
};