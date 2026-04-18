#include <iostream>
#include "node.hpp"
using namespace std;

class B24Tree {
    node* root;

    void print_node(string prefix, node* n, int child_no) {
        cout << prefix;
        if (n == root)  cout << "Root: ";
        else            cout << "Child " << child_no << ": ";
        
        for (int i = 0; i < n->size; i++) {
            cout << n->keys[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < 5; i++) {
            if (n->children[i] != nullptr) {
                print_node(prefix + "    ", n->children[i], i+1);
            }
        }
    }

    /* a helper function that searches 
    (1) which node the key must be inserted to; or
    (2) where the node containing the key is located
    */
    node* search(int num, node* n) {
        // condition: when root is null
        if (n == nullptr) {
            return nullptr;
        }

        // loop checking if num is less than/equal the keys inside node* n
        // if num < keys[i], checks first if child #i exists
        //      if true, recursively calls the function but using child #i as the node to search
        //      else, returns the current node, meaning num must be in this node
        for (int i = 0; i < n->size; i++) {
            if (num == n->keys[i]) {
                return n;
            }
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
        if (n->children[n->size]) {
            return search(num, n->children[n->size]);
        }
        return n;
    }
    /*
    a function that is called when a node w violates size property
    */
    void overflow(node* w) {
        // replace w with two nodes w' and w''
        node* w1 = new node;
        node* w2 = new node;

        // w' is a 3-node with children c1, c2, c3 storing keys k1, k2
        for (int i = 0; i < 3; i++) {
            w1->children[i] = w->children[i];
            if (w->children[i]) w1->children[i]->parent = w1;
        }
        for (int i = 0; i < 2; i++) {
            w1->insertKeyAt(w->keys[i], i);
        }

        // w'' is a 2-node with children c4, c5 storing key k4
        w2->children[0] = w->children[3];
        w2->children[1] = w->children[4];
        if (w->children[3]) w->children[3]->parent = w2;
        if (w->children[4]) w->children[4]->parent = w2;
        w2->insertKeyAt(w->keys[3], 0);

        node* u;
        // if w is the root of T, create new root node u,
        // else, let u be the parent of w
        if (w == root) {
            u = new node;
            u->parent = nullptr;
            root = u;
        } else {
            u = w->parent;
        }

        // insert k3 into u and make w' and w'' children of u,
        // so that if w was child i of u, then w' and w'' become children i and i+1 of u, respectively
        if (u->size == 0) {
            u->insertKeyAt(w->keys[2], 0);
            u->children[0] = w1;
            u->children[1] = w2;
        } else {
            for (int i = 0; i < u->size; i++) {
                if (w->keys[2] < u->keys[i]) {
                    u->insertKeyAt(w->keys[2], i);
                    for (int j = u->size; j > i+1; j--) {
                        u->children[j] = u->children[j-1];
                    }
                    u->children[i] = w1;
                    u->children[i+1] = w2;
                    break;
                }
            }
            if (w->keys[2] > u->keys[u->size-1]) {
                u->insertKeyAt(w->keys[2], u->size);
                u->children[u->size-1] = w1;
                u->children[u->size] = w2;
            }
        }
        w1->parent = u;
        w2->parent = u;

        if (u->size == 4) {
            overflow(u);
        }
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
        if (num > curr->keys[(curr->size)-1]) {
            curr->insertKeyAt(num, curr->size);
        }

        if (curr->size == 4) {
            overflow(curr);
        }

        return true;
    }

    bool remove(int num) {
        return false;
    }

    void print() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }

        print_node("", root, 0);
    }
};