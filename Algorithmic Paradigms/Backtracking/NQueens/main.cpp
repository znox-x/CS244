#include <iostream>
using namespace std;

bool checkcol(int n, int** chessboard, int col) {
    for (int i = 0; i < n; i++) {
        if (chessboard[i][col] == 1) {
            return false;
        }
    }
    return true;
}

bool checkdiagonal(int n, int** chessboard, int row, int col) {
    // to top-left
    for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) {
        if (chessboard[i][j] == 1) {
            return false;
        }
    }

    // to top-right
    for (int i = row-1, j = col+1; i >= 0 && j < n; i--, j++) {
        if (chessboard[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool nqueen(int n, int** chessboard, int row) {
    if (row == n) {
        return true;
    }

    // iterates columns per row (left-to-right)
    for (int i = 0; i < n; i++) {
        if (checkcol(n, chessboard, i) && checkdiagonal(n, chessboard, row, i)) {
            chessboard[row][i] = 1;
            if (nqueen(n, chessboard, row+1)) {
                return true;
            }
            chessboard[row][i] = 0;
        }
    }

    return false;
}

int main() {
    int n;

    cout << "Enter size of chessboard (n x n): ";
    cin >> n;

    int** chessboard = new int*[n];
    for(int i = 0; i < n; i++) {
        chessboard[i] = new int[n];
        for (int j = 0; j < n; j++) {
            chessboard[i][j] = 0;
        }
    }

    cout << endl;
    if (nqueen(n, chessboard, 0)) {
        cout << "Solution:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << (chessboard[i][j] == 1 ? "Q" : ".") << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution";
    }
}