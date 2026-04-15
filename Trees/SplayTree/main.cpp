#include <iostream>
#include "splaytree.hpp"
using namespace std;

int main() {
    SplayTree* splay = new SplayTree;
    char op;
    int num, res;
    do {
        cout << "Op: ";
        cin >> op;
        switch (op) {
            case 's':   cin >> num;
                        cout << "Does " << num << " exist? " << splay->search(num) << endl;
                        break;
            
            case 'i':   cin >> num;
                        res = splay->insert(num);
                        cout << "Node " << num << " moved to root" << endl;
                        break;
            
            case 'r':   cin >> num;
                        res = splay->remove(num);
                        if (res == -1) {
                            cout << "Node not found." << endl;
                        } else if (res == 0) {
                            cout << "Root " << num << " is removed" << endl;
                        } else {
                            cout << "Node " << num << " removed using child of " << res << endl;
                        }
                        break;

            case 'p':   splay->print();
        }
        cout << endl;
    } while (op != 'x');
}