/*
=============================================================
EECS 348: Software Engineering - Fall 2025
Lab 9 - C++ Programming: Matrix Operations

Author: Jaiden Green
Date: October 27, 2025
Description:
    This program performs several matrix operations:
    1. Read matrices from file
    2. Add two matrices
    3. Multiply two matrices
    4. Compute diagonal sums
    5. Swap rows
    6. Swap columns
    7. Update a specific element

Inputs:
    - Text file containing N followed by two N×N matrices.
Outputs:
    - Console output displaying formatted matrices and results.
=============================================================
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> // for setw formatting
using namespace std;

// Function declarations
void printMatrix(const vector<vector<int>> &matrix);
vector<vector<int>> loadMatrix(ifstream &file, int N);
vector<vector<int>> addMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B);
vector<vector<int>> multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B);
void diagonalSums(const vector<vector<int>> &matrix);
void swapRows(vector<vector<int>> &matrix, int r1, int r2);
void swapCols(vector<vector<int>> &matrix, int c1, int c2);
void updateElement(vector<vector<int>> &matrix, int row, int col, int newVal);

// Print a matrix with aligned columns
void printMatrix(const vector<vector<int>> &matrix) {
    for (const auto &row : matrix) {
        for (const auto &val : row)
            cout << setw(4) << val;
        cout << endl;
    }
    cout << endl;
}

// Load a single matrix from file
vector<vector<int>> loadMatrix(ifstream &file, int N) {
    vector<vector<int>> matrix(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> matrix[i][j];
    return matrix;
}

// Add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int N = A.size();
    vector<vector<int>> result(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

// Multiply two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int N = A.size();
    vector<vector<int>> result(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                result[i][j] += A[i][k] * B[k][j];
    return result;
}

// Calculate diagonal sums
void diagonalSums(const vector<vector<int>> &matrix) {
    int N = matrix.size();
    int mainSum = 0, secondarySum = 0;
    for (int i = 0; i < N; ++i) {
        mainSum += matrix[i][i];
        secondarySum += matrix[i][N - 1 - i];
    }
    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl << endl;
}

// Swap two rows
void swapRows(vector<vector<int>> &matrix, int r1, int r2) {
    int N = matrix.size();
    if (r1 >= 0 && r1 < N && r2 >= 0 && r2 < N) {
        swap(matrix[r1], matrix[r2]);
        cout << "Rows " << r1 << " and " << r2 << " swapped:\n";
        printMatrix(matrix);
    } else {
        cout << "Invalid row indices!\n\n";
    }
}

// Swap two columns
void swapCols(vector<vector<int>> &matrix, int c1, int c2) {
    int N = matrix.size();
    if (c1 >= 0 && c1 < N && c2 >= 0 && c2 < N) {
        for (int i = 0; i < N; ++i)
            swap(matrix[i][c1], matrix[i][c2]);
        cout << "Columns " << c1 << " and " << c2 << " swapped:\n";
        printMatrix(matrix);
    } else {
        cout << "Invalid column indices!\n\n";
    }
}

// Update a specific element in the matrix
void updateElement(vector<vector<int>> &matrix, int row, int col, int newVal) {
    int N = matrix.size();
    if (row >= 0 && row < N && col >= 0 && col < N) {
        matrix[row][col] = newVal;
        cout << "Updated matrix (" << row << "," << col << ") = " << newVal << ":\n";
        printMatrix(matrix);
    } else {
        cout << "Invalid row/column indices!\n\n";
    }
}

int main() {
    string filename;
    cout << "Enter matrix input file name: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Unable to open file.\n";
        return 1;
    }

    int N;
    infile >> N;
    vector<vector<int>> A = loadMatrix(infile, N);
    vector<vector<int>> B = loadMatrix(infile, N);

    cout << "\nMatrix A:\n";
    printMatrix(A);
    cout << "Matrix B:\n";
    printMatrix(B);

    // Matrix addition
    cout << "Matrix A + B:\n";
    printMatrix(addMatrices(A, B));

    // Matrix multiplication
    cout << "Matrix A × B:\n";
    printMatrix(multiplyMatrices(A, B));

    // Diagonal sums
    cout << "Diagonal sums for Matrix A:\n";
    diagonalSums(A);

    // Swap rows
    swapRows(A, 0, 2);

    // Swap columns
    swapCols(A, 1, 3);

    // Update a matrix element
    updateElement(A, 2, 2, 99);

    infile.close();
    return 0;
}
