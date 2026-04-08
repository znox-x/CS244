#include <iostream>
#include "splaytree.hpp"
using namespace std;

int main() {
    SplayTree* splay = new SplayTree;
    char op;
    int num, parent;
    do {
        cout << "Op: ";
        cin >> op;
        switch (op) {
            case 's':   cin >> num;
                        cout << "Does " << num << " exist? " << splay->search(num) << endl;
                        break;
            
            case 'i':   cin >> num;
                        parent = splay->insert(num);
                        if (parent == -1) {
                            cout << "Node already exists" << endl;
                        } else if (parent == 0) {
                            cout << "Node " << num << " added as root" << endl;
                        } else {
                            cout << "Node " << num << " located as child of " << parent << endl;
                        }
                        break;
            
            case 'r':   cin >> num;
                        parent = splay->remove(num);
                        if (parent == -1) {
                            cout << "Node not found." << endl;
                        } else if (parent == 0) {
                            cout << "Root " << num << " is removed" << endl;
                        } else {
                            cout << "Node " << num << " removed using child of " << parent << endl;
                        }
                        break;

            case 'p':   splay->print();
        }
        cout << endl;
    } while (op != 'x');
}