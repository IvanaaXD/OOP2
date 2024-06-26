#include "sudoku.hpp"
#include "file.hpp"
#include "iostream"
#include "string"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

using std::to_string;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;

Sudoku::Sudoku(int size) : matrix(size, vector<int>(size, 0)), numOfErrors(0), numOfGoodValues(0), numOfGames(0), numOfFilled(0), counter(0) {
}

void Sudoku::setCounter(int num) {
    this->counter = num;
}

void Sudoku::setNumOfErrors(int num) {
    this->numOfErrors = num;
}

void Sudoku::setNumOfGoodValues(int num) {
    this->numOfGoodValues = num;
}

void Sudoku::setNumOfGames(int num) {
    this->numOfGames = num;
}

void Sudoku::setNumOfFilled(int num) {
    this->numOfFilled = num;
}

int Sudoku::getCounter() const {
    return counter;
}

int Sudoku::getNumOfGoodValues() const {
    return numOfGoodValues;
}

int Sudoku::getNumOfErrors() const {
    return numOfErrors;
}

int Sudoku::getNumOfGames() const {
    return numOfGames;
}

int Sudoku::getNumOfFilled() const {
    return numOfFilled;
}

void Sudoku::countNonZeroElements() {
    int count = 0;
    for (vector<vector<int>>::const_reference row : matrix) {
        for (int value : row) {
            if (value != 0) {
                count++;
            }
        }
    }
    setNumOfFilled(count);
}

void Sudoku::print() {

    int sum = 0;

    for (int i = 0; i < matrix.size(); ++i) {

        if (i > 0 && i % 3 == 0) {
            cout << " ------+-------+------" << endl;
        }

        for (int j = 0; j < matrix[i].size(); ++j) {

            if (j > 0 && j % 3 == 0) {
                cout << "| ";
            }

            if (j == 0) {
                cout << " ";
            }

            if (matrix[i][j] != 0) {
                cout << matrix[i][j] << " ";
                sum++;
            }
            else {
                cout << " " << " ";
            }
        }
        cout << endl;
    }
}

void Sudoku::resetMatrix(){
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            matrix[i][j] = 0;
        }
    }
}

bool Sudoku::checkMatrix() {

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (matrix[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::isSafe(int row, int col, int value) const {

    for (int i = 0; i < 9; ++i) {
        if (matrix[row][i] == value || matrix[i][col] == value) {
            return false;
        }
    }

    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (matrix[startRow + i][startCol + j] == value) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::solveSudokuHelper() {

    int num = 0;
    for (int i = 0; i < 81; ++i) {

        int row = i / 9;
        int col = i % 9;

        if (matrix[row][col] == 0) {

            for (int value = 1; value <= 9; value++) {

                if (isSafe(row, col, value)) {

                    matrix[row][col] = value;

                    if (checkMatrix()) {
                        setCounter(getCounter() + 1);

                        return true; 
                    }
                    else {
                        if (solveSudokuHelper()) {
                            return true; 
                        }
                    }
                }
            }
            matrix[row][col] = 0;
            return false; 
        }
    }

    return false;
}

bool Sudoku::solveSudoku() {
    
    this->setCounter(0);
    solveSudokuHelper();

    if (this->getCounter() > 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Sudoku::fillGrid() {

    vector<int> possibleNums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int row, col;

    for (int i = 0; i < 81; ++i) {
        row = i / 9;
        col = i % 9;
        if (matrix[row][col] == 0) {
            // generating a random permutation of possibleNums
            shuffle(possibleNums.begin(), possibleNums.end(), std::default_random_engine(std::random_device()()));

            for (int value : possibleNums) {
                if (isSafe(row, col, value)) {

                    matrix[row][col] = value;

                    if (solveSudokuHelper()) {
                        return true;
                    }
                    else {
                        matrix[row][col] = 0;
                    }
                }
            }
            return false;  // no valid value found for this cell
        }
    }
    return true;  // matrix is filled
}

void Sudoku::removeElementsFromGrid() {

    for (int rowStart = 0; rowStart < 9; rowStart += 3) {
        for (int colStart = 0; colStart < 9; colStart += 3) {
            // generaties a random number between 4 and 9 
            int numToRemove = rand() % 6 + 4;

            // creates a list of unique positions within the 3x3 matrix
            vector<int> positions;
            for (int i = 0; i < 9; ++i) {
                positions.push_back(i);
            }

            // shuffle the positions
            random_shuffle(positions.begin(), positions.end());

            // removes numToRemove elements from the shuffled positions
            for (int i = 0; i < numToRemove; ++i) {
                int position = positions[i];
                int row = rowStart + position / 3;
                int col = colStart + position % 3;

                // checks if the element is not already deleted
                if (matrix[row][col] != 0) {
                    matrix[row][col] = 0;
                }
            }
        }
    }
}

void Sudoku::generateSudoku() {

    fillGrid();
    removeElementsFromGrid();
};

bool Sudoku::isValidMatrix(int rowStart, int colStart) const {
    
    unordered_set<int> matrixSet;

    for (int i = rowStart; i < rowStart + 3; ++i) {
        for (int j = colStart; j < colStart + 3; ++j) {
            int val = matrix[i][j];
            if (val < 1 || val > 9 || matrixSet.count(val)) {
                return false;  // invalid value or duplicate found within the matrix
            }
            matrixSet.insert(val);
        }
    }

    return true;  // matrix is valid
}

bool Sudoku::checkRowErrors(int row, int col, int duplicate) {
    // Check in the entire grid for the same number in nest rows
    for (int j = col + 1; j < 9; j++) {
        if (matrix[row][j] == duplicate) {
            return true;  // Stop checking if an error is found
        }
    }

    // Check in the entire grid for the same number in previous rows
    for (int i = 0; i < col; i++) {
        if (matrix[row][i] == duplicate) {
            return true;  // Stop checking if an error is found
        }
    }

    return false;
}

bool Sudoku::checkColumnErrors(int row, int col, int duplicate) {
    // Check in the entire grid for the same number in next columns
    for (int i = row + 1; i < 9; i++) {
        if (matrix[i][col] == duplicate) {
            return true; 
        }
    }

    // Check in the entire grid for the same number in previous columns
    for (int j = 0; j < row; j++) {
        if (matrix[j][col] == duplicate) {
            return true;  
        }
    }

    return false;
}

bool Sudoku::validateSudoku() {
    numOfErrors = 0;  // resets the error count

    // iterate through each 3x3 matrix
    for (int rowStart = 0; rowStart < 9; rowStart += 3) {
        for (int colStart = 0; colStart < 9; colStart += 3) {
            if (!isValidMatrix(rowStart, colStart)) {
                // invalid matrix, checking row and col for errors
                for (int i = rowStart; i < rowStart + 3; i++) {
                    for (int j = colStart; j < colStart + 3; j++) {
                        int duplicate = matrix[i][j];
                        if (duplicate != 0) {
                            if (checkRowErrors(i, j, duplicate) && checkColumnErrors(i, j, duplicate)) {
                                numOfErrors++;
                                cout << numOfErrors;
                            }
                        }
                        else {
                            numOfErrors++;
                        }
                    }
                }
            }
        }
    }

    if (getNumOfErrors() > 0) {
        return false;
    }
    else
    {
        return true;
    }
};

bool Sudoku::checkSetUp(vector<vector<int>>& mat) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (mat[i][j] != 0 && mat[i][j] != matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
};
