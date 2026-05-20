#include <iostream>
using namespace std;

bool checkAdjacents(int vertexNumber, int color, int n, int** matrix, int k, int* vertexColors) {
    for (int i = 0; i < n; i++) {
        if (matrix[vertexNumber][i] == 1) {
            if (vertexColors[i] == color) {
                return false;
            }
        }
    }
    return true;
}

bool backtrack(int vertexNumber, int n, int** matrix, int k, int* vertexColors) {
    if (vertexNumber == n) {
        return true;
    }

    for (int i = 1; i <= k; i++) {
        if (checkAdjacents(vertexNumber, i, n, matrix, k, vertexColors)) {
            vertexColors[vertexNumber] = i;
            if (backtrack(vertexNumber+1, n, matrix, k, vertexColors)) {
                return true;
            }
            vertexColors[vertexNumber] = 0;
        }
    }
    return false;
}

bool colorGraph(int n, int** matrix, int k) {
    // stored colors for each vertex (must be 1 to k)
    int* vertexColors = new int[n];
    for (int i = 0; i < n; i++) {
        vertexColors[i] = 0;
    }

    return backtrack(0, n, matrix, k, vertexColors);
}

int main() {
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    int vertex1 = 0, vertex2 = 0;
    cout << "Enter connected vertices (enter -1 -1 to stop): " << endl;
    while (vertex1 != -1 && vertex2 != -1) {
        cin >> vertex1;
        cin >> vertex2;

        if (vertex1 != -1 && vertex2 != -1) {
            matrix[vertex1][vertex2] = 1;
            matrix[vertex2][vertex1] = 1;
        }
    }

    int k;
    cout << "Enter number of colors: ";
    cin >> k;

    cout << endl << "Adjacency Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Is it possible to color the graph with " << k << " colors? ";
    if (colorGraph(n, matrix, k)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}