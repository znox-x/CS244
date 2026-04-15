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
        
        // getting access to the nodes parent & grandparent for structure checking
        node* y = x->parent;
        node* z = y->parent;

        cout << "Performing ";

        if (z) {                                            // z is null when your node x's parent is the root
            if (z->right == y) {
                if (y->right == x) {                        // structure looks like "\"
                    cout << "zig-zig left..." << endl;
                    zig_zig_left(x);
                } else {                                    // structure looks like ">"
                    cout << "zig-zag left..." << endl;
                    zig_zag_left(x);
                }
            } else {
                if (y->left == x) {                         // structure looks like "/"
                    cout << "zig-zig right..." << endl;
                    zig_zig_right(x);
                } else {                                    // structure looks like "<"
                    cout << "zig-zag right..." << endl;
                    zig_zag_right(x);
                }
            }
        } else {
            if (y->left == x) {                             // "/" but with two nodes only
                cout << "zig right..." << endl;
                zig_right(x);
            } else {                                        // "\" but with two nodes only
                cout << "zig left..." << endl;
                zig_left(x);
            }
        }

        // recursive call (passes itself since only the tree structure has changed, not this pointer)
        splay(x);
    }

    // rotation helpers
    /* 
    basically the same implementation with the avl restructure,
    but take note that the parameters are using the node that is being splayed
    */
    void zig_left(node* x) {                                        // check step-by-step in the .png file (wip)
        node* y = x->parent;

        cout << "x = " << x->elem << ", y = " << y->elem << endl;
        
        y->right = x->left;
        if (x->left)    x->left->parent = y;
        x->left = y;
        x->parent = y->parent;
        if (y->parent) {
            if (y->parent->left == y)   y->parent->left = x;
            else                        y->parent->right = x;
        } else {
            tree->setRoot(x);
        }
        y->parent = x;
    }

    void zig_right(node* x) {
        node* y = x->parent;

        cout << "x = " << x->elem << ", y = " << y->elem << endl;

        y->left = x->right;
        if (x->right)    x->right->parent = y;
        x->right = y;
        x->parent = y->parent;
        if (y->parent) {
            if (y->parent->left == y)   y->parent->left = x;
            else                        y->parent->right = x;
        } else {
            tree->setRoot(x);
        }
        y->parent = x;
    }

    void zig_zig_left(node* x) {
        zig_left(x->parent);
        zig_left(x);
    }

    void zig_zig_right(node* x) {
        zig_right(x->parent);
        zig_right(x);
    }

    void zig_zag_left(node* x) {
        zig_right(x);
        zig_left(x);
    }

    void zig_zag_right(node* x) {
        zig_left(x);
        zig_right(x);
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
        node* curr = tree->getRoot();

        if (!curr) {
            tree->addRoot(num);
            return 0;
        }

        node* n;
        while (curr) {
            if (num < curr->elem) {
                if (curr->left) {
                    curr = curr->left;
                } else {
                    n = tree->addLeft(curr, num);
                    break;
                }
            } else if (num > curr->elem) {
                if (curr->right) {
                    curr = curr->right;
                } else {
                    n = tree->addRight(curr, num);
                    break;
                }
            } else {
                cout << "Node already exists." << endl;
                n = curr;
                break;
            }
        }

        cout << "Splaying..." << endl;
        splay(n);
        return 1;
    }

    int remove(int num) {
        return -1;
    }

    void print() {
        tree->print();
    }
};