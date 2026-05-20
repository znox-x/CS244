#include <iostream>
#include <cstring>
using namespace std;

int recursion(int i, int j, string str1, string str2, int** cache) {
    if (i == 0 || j == 0) {
        return 0;
    }

    if (cache[i][j] != -1) {
        return cache[i][j];
    }

    if (str1.at(i-1) == str2.at(j-1)) {
        cache[i][j] = 1 + recursion(i-1, j-1, str1, str2, cache);
        return cache[i][j];
    }

    int skipstr1 = recursion(i-1, j, str1, str2, cache);
    int skipstr2 = recursion(i, j-1, str1, str2, cache);

    if (skipstr1 >= skipstr2) {
        cache[i][j] = skipstr1;
    } else {
        cache[i][j] = skipstr2;
    }

    return cache[i][j];
}

int lcs(string str1, string str2) {
    int** cache = new int*[str1.length() + 1];
    for (int i = 0; i < str1.length()+1; i++) {
        cache[i] = new int[str2.length()+1];
        for (int j = 0; j < str2.length()+1; j++) {
            cache[i][j] = -1;
        }
    }

    return recursion(str1.length(), str2.length(), str1, str2, cache);
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