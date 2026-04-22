#include <iostream>
#include "rbtree.hpp"
using namespace std;

int main() {
    RBTree* tree = new RBTree;
    char op;
    int num;

    do {
        cout << "Enter op: ";
        cin >> op;
        switch (op) {
            case 'i':   cin >> num;
                        if (tree->insert(num)) {
                            cout << "Node inserted." << endl;
                        } else {
                            cout << "Node not inserted." << endl;
                        }
                        break;
            case 'p':   tree->print();
                        break;
        }
    } while (op != 'x');
    
}
