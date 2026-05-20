#include <iostream>
using namespace std;

int knapsack(int n, int w, int items[][2]) {
    int table[n+1][(w/5)+1];
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w/5; j++) {
            if (i == 0 || j == 0) {
                table[i][j] = 0;
                continue;
            }
            
            int value = 0;
            if (items[i][1] <= j*5) {
                value = items[i][0] + table[i-1][j - (items[i][1]/5)];
            }
            
            if (value > table[i-1][j]) {
                table[i][j] = value;
            } else {
                table[i][j] = table[i-1][j];
            }
        }
    }
    
    return table[n][w/5];
}


int main() {
    int n, w;
    cout << "Enter number of items and weight capacity: ";
    cin >> n;
    cin >> w;
    
    int items[n+1][2];
    items[0][0] = 0;
    items[0][1] = 0;
    cout << "Enter value and weight of each item:" << endl;
    for (int i = 1; i <= n; i++) {
        cin >> items[i][0];
        cin >> items[i][1];
    }
    
    int res = knapsack(n, w, items);
    cout << "Maximum value in Knapsack = " << res;
}