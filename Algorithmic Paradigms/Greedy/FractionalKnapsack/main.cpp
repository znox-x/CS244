#include <iostream>
#include "item.hpp"
using namespace std;

int findMaximum(item** items, int n, double W) {
    // compute ratio for each item

    double ratios[n][2];                    // col 1 = item; col 2 = ratio
    for (int i = 0; i < n; i++) {
        ratios[i][0] = i;
        ratios[i][1] = items[i]->value / items[i]->weight;
    }

    // sort from biggest to smallest (bubble)
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (ratios[j][1] < ratios[j+1][1]) {
                double tempitem = ratios[j][0];
                double tempratio = ratios[j][1];
                ratios[j][0] = ratios[j+1][0];
                ratios[j][1] = ratios[j+1][1];
                ratios[j+1][0] = tempitem;
                ratios[j+1][1] = tempratio;
            }
        }
    }

    // calculate
    // note: ratios[_][0] is used key for the items[]
    double total = 0;
    for (int i = 0; i < n; i++) {
        if (W - items[(int)ratios[i][0]]->weight > 0) {
            total += items[(int)ratios[i][0]]->value;
            W -= items[(int)ratios[i][0]]->weight;
        } else {
            total += ((items[(int)ratios[i][0]]->value * W) / items[(int)ratios[i][0]]->weight);
            W -= W;
            break;
        }
    }

    return (int)total;
}

int main() {
    int n;
    double W;

    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter weight capacity: ";
    cin >> W;

    item** items = new item*[n];
    cout << "Enter value and weight of each item: " << endl;
    for (int i = 0; i < n; i++) {
        items[i] = new item();
        cin >> items[i]->value;
        cin >> items[i]->weight;
    }

    int max = findMaximum(items, n, W);

    cout << "Maximum possible value: " << max;
}