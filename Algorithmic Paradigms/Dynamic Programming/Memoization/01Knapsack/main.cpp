#include <iostream>
using namespace std;

int recursion(int i, int W, int** items, int** cache) {
    // if all items already recursed, return 0
    if (i == 0 || W == 0) {
        return 0;
    }

    // if the cell is already filled up, return its value
    if (cache[i][W] != -1) {
        return cache[i][W];
    }

    // if the current item exceeds current capacity, recurse to the next and store it in cache
    if (items[i-1][0] > W) {
        cache[i][W] = recursion(i-1, W, items, cache);
        return cache[i][W];
    }

    // two subproblems: to take or  to skip item
    int skip = recursion(i-1, W, items, cache);
    int take = items[i-1][1] + recursion(i-1, W - items[i-1][0], items, cache);

    // store the larger amount in the cache
    if (skip >= take) {
        cache[i][W] = skip;
    } else {
        cache[i][W] = take;
    }

    return cache[i][W];
}

int knapsack(int n, int W, int** items) {
    // initialize 2D array to -1
    int** cache = new int*[n+1];
    for (int i = 0; i < n+1; i++) {
        cache[i] = new int[W+1];
        for (int j = 0; j < W+1; j++) {
            cache[i][j] = -1;
        }
    }

    return recursion(n, W, items, cache);
}

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter maximum weight of knapsack: ";
    cin >> W;

    int** items = new int*[n];
    cout << "Enter weight and value of items: " << endl;
    for (int i = 0; i < n; i++) {
        items[i] = new int[2];
        cin >> items[i][0];
        cin >> items[i][1];
    }

    int res = knapsack(n, W, items);

    cout << "Maximum value in knapsack = " << res;
}