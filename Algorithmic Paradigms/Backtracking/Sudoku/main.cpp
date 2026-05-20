#include <iostream>
#include <cstdlib>
using namespace std;

bool checkRow(int row, int** sudoku, int val) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == val)  return false;
    }
    return true;
}

bool checkColumn(int col, int** sudoku, int val) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col] == val)  return false;
    }
    return true;
}

bool checkBox(int row, int col, int** sudoku, int val) {
    int box_r = row / 3;
    int box_c = col / 3;
    
    for (int i = box_r*3; i < (box_r+1)*3; i++) {
        for (int j = box_c*3; j < (box_c+1)*3; j++) {
            if (sudoku[i][j] == val)    return false;
        }
    }
    return true;
}

bool solve(int row, int col, int** sudoku) {
    if (row == 9) {
        return true;
    }
    if (col == 9) {
        return solve(row+1, 0, sudoku);
    }
    if (sudoku[row][col] != 0) {
        return solve(row, col+1, sudoku);
    }
    
    for (int i = 1; i <= 9; i++) {
        if (checkRow(row, sudoku, i) && checkColumn(col, sudoku, i) && checkBox(row, col, sudoku, i)) {
            sudoku[row][col] = i;
            if (solve(row, col+1, sudoku)) {
                return true;
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int** sudoku = (int**)malloc(9 * sizeof(int*));
    cout << "Enter the Sudoku board:" << endl;
    for (int i = 0; i < 9; i++) {
        sudoku[i] = (int*)malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
        }
    }
    
    if (solve(0, 0, sudoku)) {
        cout << endl << "Solved Board:" << endl;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << sudoku[i][j] << " ";
            }
            cout << endl;
        }
    }
}