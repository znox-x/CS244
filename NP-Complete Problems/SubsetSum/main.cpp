#include <iostream>
using namespace std;

bool hasSubset(int n, int* set, int T) {
    // initialize the dp table
    bool** dp = new bool*[n+1];
    for (int i = 0; i < n+1; i++) {
        dp[i] = new bool[T+1];
        for (int j = 0; j < T+1; j++) {
            if (j == 0) {
                dp[i][j] = true;
            } else {
                dp[i][j] = false;
            }
        }
    }

    // iterate
    for (int i = 1; i < n+1; i++) {
        for (int j = 0; j < T+1; j++) {
            if (set[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] || dp[i-1][j-set[i-1]];
            }
        }
    }

    return dp[n][T];
}

int main() {
    int n;

    cout << "Enter number of integers: ";
    cin >> n;

    int* set = new int[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> set[i];
    }

    int target;
    cout << "Enter target sum: ";
    cin >> target;

    cout << "Is there a subset that satisfies the target sum? ";
    if (hasSubset(n, set, target)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}