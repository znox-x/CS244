#include <iostream>
#include <stdexcept>
#include "node.hpp"
#include "binarytree.hpp"

class AVLTree : public BinaryTree {
    BinaryTree* tree;

    // --- HELPER METHODS ---

    // accepts a node and returns the node's balance factor (height of left subtree - height of right subtree)
    int balance_factor(node* n) {
        int left = n->left ? n->left->height() : 0;         // if no left  subtree = 0
        int right = n->right ? n->right->height() : 0;      //   ''  right      ''
        return left - right;
    }

    // function that recursively checks if the node follows the property of an avl tree
    // property: balance factor must be between -1 and 1 inclusive
    void bf_check(node* n) {
        cout << "Checking node " << n->elem << "..." << endl;

        int bf = balance_factor(n);

        if (bf < -1 || bf > 1) {
            restructure(n);
        }

        if (n == tree->getRoot()) {
            return;
        }

        bf_check(n->parent);
    }

    // function that is called when a node is not balanced
    void restructure(node* n) {
        cout << "Restructuring via ";
        int bf = balance_factor(n);
        
        if (bf == 2) {
            int bf_left = balance_factor(n->left);
            if (bf_left == 1) {
                cout << "zig right" << endl;
                zig_right(n->left->left, n->left, n);
            } else {
                cout << "zigzag right" << endl;
                zigzag_right(n->left->right, n->left, n);
            }
        } else {
            int bf_right = balance_factor(n->right);
            if (bf_right == -1) {
                cout << "zig left" << endl;
                zig_left(n->right->right, n->right, n);
            } else {
                cout << "zigzag left" << endl;
                zigzag_left(n->right->left, n->right, n);
            }
        }
    }

    void zig_left(node* x, node* y, node* z) {
        // z = left of y, x = right of y

        z->right = y->left;                                     // 1. right of z = T2
        if (y->left) y->left->parent = z;                       // ~1. parent of T2 = z (if T2 exists)
        y->left = z;                                            // 2. left of y = z
        y->parent = z->parent;                                  // 3. parent of y = parent of z
        if (z->parent) {                                        // ~3. node connecting the restructured tree must connect to new child (if not at root)
            if (z == z->parent->left)   z->parent->left = y;
            else                        z->parent->right = y;
        } else {
            tree->setRoot(y);
        }
        z->parent = y;                                          // ~2. parent of z = y
    }

    void zig_right(node* x, node* y, node* z) {
        // x = left of y, z = right of y

        z->left = y->right;                                     // 1. left of z = T3
        if (y->right) y->right->parent = z;                     // ~1. parent of T3 = z (if T3 exists)
        y->right = z;                                           // 2. right of y = z
        y->parent = z->parent;                                  // 3. parent of y = parent of z
        if (z->parent) {                                        // ~3. node connecting the restructured tree must connect to new child (if not at root)
            if (z == z->parent->left)   z->parent->left = y;
            else                        z->parent->right = y;
        } else {
            tree->setRoot(y);
        }
        z->parent = y;                                          // ~2. parent of z = y
    }

    void zigzag_left(node* x, node* y, node* z) {
        zig_right(x->left, x, y);
        zig_left(y, x, z);
    }

    void zigzag_right(node* x, node* y, node* z) {
        zig_left(x->right, x, y);
        zig_right(y, x, z);
    }

    public:
    AVLTree() {
        tree = new BinaryTree();
    }

    bool search(int num) {
        node* curr = tree->getRoot();
        while (curr) {
            if (num < curr->elem) {
                curr = tree->left(curr);
            } else if (num > curr->elem) {
                curr = tree->right(curr);
            } else {
                return true;
            }
        }
        return false;
    }

    int insert(int num) {
        if (search(num)) {
            return -1;
        }

        if (!tree->getRoot()) {
            tree->addRoot(num);
            return 0;
        }

        node* curr = tree->getRoot();
        node* n;
        while (curr) {
            if (num < curr->elem) {
                if (curr->left) {
                    curr = curr->left;
                } else {
                    n = tree->addLeft(curr, num);
                    break;
                }
            } else {
                if (curr->right) {
                    curr = curr->right;
                } else {
                    n = tree->addRight(curr, num);
                    break;
                }
            }
        }

        bf_check(curr);
        return n->parent ? n->parent->elem : 0;
    }

    int remove(int num) {
        if (!search(num)) {
            return -1;
        }

        node* curr = tree->getRoot();
        node* check;
        while (curr) {
            if (num < curr->elem) {
                curr = curr->left;
            } else if (num > curr->elem) {
                curr = curr->right;
            } else {
                if (curr->left && curr->right) {
                    node* next = curr->right;
                    while (next->left) {
                        next = next->left;
                    }
                    curr->elem = next->elem;
                    check = next->parent;
                    tree->remove(next);
                } else {
                    check = curr->parent;
                    tree->remove(curr);
                }
                break;
            }
        }

        if (check) {
            bf_check(check);
        } else {
            return 0;
        }
        
        return check->elem;
    }

    void print() {
        tree->print();
    }
};