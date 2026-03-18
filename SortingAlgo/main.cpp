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

        if (sorttype == 1){
            cout << "Start: ";
            list->print();
            if (ArrayList* check = dynamic_cast<ArrayList*>(list)) {
                list = bubbleSort((ArrayList*)list, n);
            } else {
                list = bubbleSort((LinkedList*)list, n);
            }
            cout << "Finished: ";
            list->print();
            break;
        }
        else if (sorttype == 2){
            cout << "Start: ";
            list->print();
            if (ArrayList* check = dynamic_cast<ArrayList*>(list)) {
                list = selectionSort((ArrayList*)list, 1);
            } else {
                list = selectionSort((LinkedList*)list, 1);
            }
            cout << "Finished: ";
            list->print();
            break;
        }
        else if (sorttype == 4){
            if (ArrayList* check = dynamic_cast<ArrayList*>(list)) {
                list = mergeSort((ArrayList*)list);
            } else {
                list = mergeSort((LinkedList*)list);
            }
            cout << "Finished: ";
            list->print();
            break;
        }
    }
    
}