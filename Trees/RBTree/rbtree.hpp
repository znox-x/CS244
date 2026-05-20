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

        if (!sibling(y, y->parent) || !sibling(y, y->parent)->isRed) {
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
                    sibling(x, x->parent)->isRed = true;
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
                    sibling(y, y->parent)->isRed = true;
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
                    sibling(x, x->parent)->isRed = true;
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
                    sibling(y, y->parent)->isRed = true;
                    return x;
                }
            }
        } else {
            y->isRed = false;
            y->parent->isRed = true;
            sibling(y, y->parent)->isRed = false;
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

    node* sibling(node* n, node* parent) {
        if (!parent) return nullptr;
        if (!n)      return parent->left ? parent->left : parent->right;
        if (parent->left == n) return parent->right;
        return parent->left;
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

    bool remove(int num) {
        node* n = search(num);

        if (!n) return false;
        
        // u is the node physically being removed, v is a child of u
        node *u, *v;

        /* ------------- BST DELETE ------------- */ 

        // (1) if both children exist, find smallest number in right subtree and use its value to replace it
        // note: u will be the smallest number in the right subtree
        if (n->left && n->right) {
            u = n->right;

            while (u->left != nullptr) {
                u = u->left;
            }
            n->elem = u->elem;
        }
        // note: else, u will be the original found node
        else {
            u = n;
        }

        // find a valid child of u
        v = u->left ? u->left : u->right;

        // (2) if one child exist, connect child to the node's parent
        if (v) {
            v->parent = u->parent;
        }
        if (u->parent) {
            if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
        } else {
            root = v;
        }

        /* ------------- EASY EDGE CASES ------------- */

        // if removed node u is RED, no fixes, return
        if (u->isRed) {
            delete u;
        } else {
            // if removed node u is BLACK but child is RED, recolor v to BLACK, return
            if (v && v->isRed) {
                v->isRed = false;
                delete u;
            } else {
                /* ------------- DOUBLE BLACK CASES ------------- */
                
                // initialize:  mark node v as db (doubleblack)
                //              let node par be parent of db (used parent of u since db can be null)
                //              let node w be a sibling of db
                node* db = v;
                node* par = u->parent;
                node* w = sibling(db, par);
                delete u;

                while (true) {
                    // Base Case: db is at the root, meaning par is null and w will be also null
                    if (!par)   break;

                    // Case 1: w is RED
                    // do rotation about w and z (w->parent); will be either Case 2 or 3 after adjustment
                    // w will be BLACK, z will be RED
                    // rotation causes db to have a new sibling, therefore update node w to be the new sibling of db
                    if (w && w->isRed) {
                        node* z = w->parent;
                        if (z->left == w) {
                            zigright(w);
                        } else {
                            zigleft(w);
                        }
                        w->isRed = false;
                        z->isRed = true;

                        w = sibling(db, par);
                    }
                    
                    if (!w || !w->isRed) {
                    // Case 2: w is BLACK, both children are BLACK
                    // recoloring: w to RED, if w->parent is RED then turn to BLACK and finish, if w->parent is BLACK then db = w->parent
                    // if db is changed, update also par and w
                        if ((!w->left || !w->left->isRed) && (!w->right || !w->right->isRed)) {
                            w->isRed = true;
                            if (w->parent->isRed == true) {
                                w->parent->isRed = false;
                                break;
                            } else {
                                db = w->parent;
                                par = db->parent;
                                w = sibling(db, par);
                            }
                        }
                    // Case 3: w is BLACK, has RED child x
                    // restructure between x, y (parent of x), and z (grandparent of x)
                    // recoloring: x and z to BLACK, y to the former color of z
                    // finish
                        else {
                            node *x, *y, *z;
                            if (w->left && w->left->isRed) {
                                x = w->left;
                            } else {
                                x = w->right;
                            }
                            y = x->parent;
                            z = y->parent;

                            if (y == z->left) {
                                if (x == y->left) {
                                    zigright(y);
                                } else {
                                    zigzagright(y);
                                }
                            } else {
                                if (x == y->left) {
                                    zigzagleft(y);
                                } else {
                                    zigleft(y);
                                }
                            }

                            y->isRed = z->isRed;
                            x->isRed = false;
                            z->isRed = false;
                            break;
                        }
                    }
                }
            }
        }

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