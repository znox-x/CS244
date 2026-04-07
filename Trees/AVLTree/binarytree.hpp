#include <iostream>
#include <stdexcept>
#include "node.hpp"
using namespace std;

// tree object of AVL tree
class BinaryTree {
    node* root;
    int size;

    // helpers
    node* create_node(int e, node* par) {
        node* n = new node;
        n->elem = e;
        n->parent = par;
        n->left = nullptr;
        n->right = nullptr;
        size++;
        return n;
    }

    void print_node(string prefix, node* n, bool isLeft) {
        cout << prefix;
        cout << (isLeft ? "+--L: " : "+--R: ");
        cout << n->elem << endl;
        if (n->left)    print_node(prefix + "|   ", n->left, true);
        if (n->right)   print_node(prefix + "|   ", n->right, false);
    }

    public:
    BinaryTree() {
        root = nullptr;
        size = 0;
    }

    node* left(node* n){
        return n->left;
    }

	node* right(node* n){
        return n->right;
    }

	void addRoot(int e){
        if (root) {
            throw logic_error("Already has root");
        }

        node* n = create_node(e, nullptr);
        root = n;
    }

	node* addLeft(node* p, int e){
        if (p->left) {
            throw logic_error(to_string(p->elem) + " already has left child");
        }

        node* n = create_node(e, p);
        p->left = n;
        return n;
    }

	node* addRight(node* p, int e){
        if (p->right) {
            throw logic_error(to_string(p->elem) + " already has right child");
        }

        node* n = create_node(e, p);
        p->right = n;
        return n;
    }

	void remove(node* n){
        if (n->left && n->right) {
            throw logic_error("Cannot remove node with two children");
        }

        node* child = n->left ? n->left : n->right;

        if (child) {
            child->parent = n->parent;
        }

        if (n->parent) {
            if (n == n->parent->left) {
                n->parent->left = child;
            } else {
                n->parent->right = child;
            }
        } else {
            root = child;
        }

        delete n;
        size--;
    }

	node* getRoot(){
        return root;
    }

    void setRoot(node* n){
        root = n;
    }

    int getSize(){
        return size;
    }

	void print(){
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }

        print_node("", root, false);
    }
    
	node* sibling(node* n){
        if (n == root) {
            throw logic_error(to_string(n->elem) + " has no parent, is a root");
        }
        
        if (n->parent->left == n) {
            return n->parent->right;
        } else {
            return n->parent->left;
        }
    }
};