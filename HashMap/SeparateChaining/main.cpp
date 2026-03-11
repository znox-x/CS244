#include <bits/stdc++.h>
#include "hashmap.hpp"
using namespace std;

int main(){
    cout << "SEPARATE CHAINING" << endl << endl;

    int n;
    cout << "Enter the size of your bucket array: ";
    cin >> n;

    HashMap* hashmap = new HashMap(n);

    int op;
    while (true)
    {
        cout << endl << "(1) Add a pair" << endl << "(2) Delete a pair" << endl << "(3) Exit" << endl;
        cout << "Op: ";
        cin >> op;

        if (op == 3)    break;

        string str;
        int value, res;

        switch (op){
            case 1:
                cout << endl << "Enter key (string): ";
                cin >> str;
                cout << "Enter value (int): ";
                cin >> value;

                res = hashmap->add(str, value);
                cout << "KV pair inserted at index " << res << endl;

                break;
            case 2:
                break;
        }

        
    }
    
    cout << endl << "Here is your final HashMap:" << endl;
    hashmap->print();
}