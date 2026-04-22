#include <iostream>
#include "node.hpp"
using namespace std;

class RBTree {
    node* root;

    node* doublered(node* x) {
        node* y = x->parent;

        if (y == root) {
            if (y->isRed)   y->isRed = false;
            return y;
        }

        if (!sibling(y) || !sibling(y)->isRed) {
            if (y->left == x) {
                if (y->parent->left == y) {
                    //      z
                    //     /             y
                    //    y     ->      / \
                    //   /             x   z
                    //  x
                    zigright(y);
                    x->isRed = true;
                    y->isRed = false;
                    sibling(x)->isRed = true;
                    return y;
                } else {
                    //   z           z
                    //    \           \             x
                    //     y     ->    x     ->    / \
                    //    /             \         z   y
                    //   x               y
                    zigzagleft(y);
                    x->isRed = false;
                    y->isRed = true;
                    sibling(y)->isRed = true;
                    return x;
                }
            } else {
                if (y->parent->right == y) {
                    //  z
                    //   \               y
                    //    y     ->      / \
                    //     \           z   x
                    //      x
                    zigleft(y);
                    x->isRed = true;
                    y->isRed = false;
                    sibling(x)->isRed = true;
                    return y;
                } else {
                    //      z           z
                    //     /           /           x
                    //    y     ->    x     ->    / \
                    //     \         /           y   z
                    //      x       y
                    zigzagright(y);
                    x->isRed = false;
                    y->isRed = true;
                    sibling(y)->isRed = true;
                    return x;
                }
            }
        } else {
            y->isRed = false;
            y->parent->isRed = true;
            sibling(y)->isRed = false;
            return y->parent;
        }
    }

    void zigleft(node* y) {
        node* z = y->parent;

        z->right = y->left;
        if (y->left)    y->left->parent = z;
        y->left = z;
        y->parent = z->parent;
        if (z->parent) {
            if (z->parent->left == z)   z->parent->left = y;
            else                        z->parent->right = y;
        } else {
            root = y;
        }
        z->parent = y;
    }

    void zigright(node* y) {
        node* z = y->parent;

        z->left = y->right;
        if (y->right)    y->right->parent = z;
        y->right = z;
        y->parent = z->parent;
        if (z->parent) {
            if (z->parent->left == z)   z->parent->left = y;
            else                        z->parent->right = y;
        } else {
            root = y;
        }
        z->parent = y;
    }

    void zigzagleft(node* y) {
        zigright(y->left);
        zigleft(y->parent);
    }

    void zigzagright(node* y) {
        zigleft(y->right);
        zigright(y->parent);
    }

    node* sibling(node* n) {
        if (!n || !n->parent)       return nullptr;
        if (n->parent->left == n)   return n->parent->right;
        return n->parent->left;
    }

    void print_node(string prefix, node* n, bool isLeft) {
        cout << prefix;
        cout << (isLeft ? "+--L: " : "+--R: ");
        cout << n->elem << (n->isRed ? "R" : "B") << endl;
        if (n->left)    print_node(prefix + "|   ", n->left, true);
        if (n->right)   print_node(prefix + "|   ", n->right, false);
    }

    public:
    RBTree() {
        root = nullptr;
    }

    node* search(int num) {
        node* curr = root;

        while (curr) {
            if (num < curr->elem) {
                if (curr->left)     curr = curr->left;
                else return curr;
            } else if (num > curr->elem) {
                if (curr->right)    curr = curr->right;
                else return curr;
            } else {
                return curr;
            }
        }

        return curr;
    }

    bool insert(int num) {
        node* par = search(num);

        if (par && par->elem == num)    return false;

        node* n = new node;
        n->elem = num;
        n->parent = par;

        if (par == nullptr) {
            n->isRed = false;
            root = n;
            return true;
        } else {
            n->isRed = true;
            if (num < par->elem)    par->left = n;
            else                    par->right = n;
        }

        node* curr = n;
        while (curr != root) {
            cout << "loop" << endl;
            if (curr->isRed && curr->parent->isRed) {
                curr = doublered(curr);
            } else {
                break;
            }
        }

        root->isRed = false;
        return true;
    }

    void print(){
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }

        print_node("", root, false);
    }
};