#include <iostream>
#include <cstring>
using namespace std;

int lcs(string str1, string str2) {
    int** dp = new int*[str1.length()+1];
    for (int i = 0; i < str1.length()+1; i++) {
        dp[i] = new int[str2.length()+1];
        for (int j = 0; j < str2.length()+1; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i < str1.length()+1; i++) {
        for (int j = 1; j < str2.length()+1; j++) {
            if (str1.at(i-1) == str2.at(j-1)) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                int max;
                if (dp[i-1][j] >= dp[i][j-1]) {
                    max = dp[i-1][j];
                } else {
                    max = dp[i][j-1];
                }
                dp[i][j] = max;
            }
        }
    }

    for (int i = 0; i < str1.length()+1; i++) {
        for (int j = 0; j < str2.length()+1; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    return dp[str1.length()][str2.length()];
}

int main() {
    string str1, str2;

    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    int res = lcs(str1, str2);

    cout << "Longest common subsequence = " << res;
}