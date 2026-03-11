#include <iostream>
#include "arraylist.hpp"
#include "linkedlist.hpp"
#include "sortinglib.hpp"
using namespace std;

int main(){
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    List* list;
    while (true){
        int type;

        cout << "(1) ArrayList" << endl << "(2) LinkedList" << endl << "Enter a list type: ";
        cin >> type;

        if (type == 1){
            list = new ArrayList(n);
            break;
        }
        else if (type == 2){
            list = new LinkedList();
            break;
        }
        else{
            cout << "Invalid input." << endl;
        }
    }

    for (int i = 0; i < n; i++){
        int elem;
        cout << "Enter element #" << i+1 << ": ";
        cin >> elem;
        list->insert(elem);
    }

    while (true){
        int sorttype;

        cout << endl << "(1) Bubble Sort" << endl << "(2) Selection Sort" << endl << "(3) Insertion Sort" << endl << "(4) Merge Sort" << endl << "(5) Quick Sort" << endl << "Select a sorting type: ";
        cin >> sorttype;

        if (sorttype == 4){
            list = mergeSort((LinkedList*)list);
            cout << "Finished: ";
            list->print();
            break;
        }
    }
    
    
}