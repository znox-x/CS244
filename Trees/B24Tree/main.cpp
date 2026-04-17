#include <iostream>
#include "b24tree.hpp"
using namespace std;

int main() {
    B24Tree* tree = new B24Tree();
    char op;
    int num;
    do {
        cout << "Op: ";
        cin >> op;

        switch (op)
        {
        case 'i':   cin >> num;
                    if (tree->insert(num)) {
                        cout << "Key inserted." << endl;
                    } else {
                        cout << "Key already exists." << endl;
                    }
                    break;
        case 'r':   cin >> num;
                    if (tree->remove(num)) {
                        cout << "Key removed." << endl;
                    } else {
                        cout << "Key does not exist." << endl;
                    }
                    break;
        case 'p':   tree->print();
                    break;
        }
    } while (op != 'x');
}