#include <iostream>
#include "sudoku.hpp"  
#include "file.hpp"
#include "tests.hpp"
#include <cassert>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::stoi;
using std::string;
using std::numeric_limits;
using std::streamsize;
using std::runtime_error;

SudokuTest::SudokuTest() {};

SudokuTest::~SudokuTest() {};

bool SudokuTest::areMatricesEqual(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) const {
    // Check if matrices have the same size
    if (matrix1.size() != matrix2.size() || matrix1.empty() || matrix1[0].size() != matrix2[0].size()) {
        return false;
    }

    // Iterate through each element and compare
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[i].size(); ++j) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuTest::testSaveAndLoadSudoku() {
    // Create an instance of Sudoku
    Sudoku sudoku(9);

    // Initialize Sudoku with an unsolved board
    vector<vector<int>> unsolved = {
        {0, 3, 4, 6, 7, 8, 9, 1, 2},
        {0, 7, 0, 1, 9, 0, 3, 4, 8},
        {1, 0, 0, 0, 4, 2, 0, 0, 7},
        {8, 5, 0, 7, 6, 0, 0, 2, 3},
        {0, 0, 0, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 0, 0, 4, 0, 0, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {0, 0, 7, 4, 1, 9, 0, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    };

    sudoku.matrix = unsolved;

    // Save the Sudoku to a file
    const string filename = "test_sudoku.txt";
    FileHandler::saveSudoku(sudoku, filename);

    // Create another instance of Sudoku
    Sudoku loadedSudoku(9);

    // Load the Sudoku from the file
    FileHandler::loadSudoku(loadedSudoku, filename);

    // Check if the loaded matrix is equal to the original matrix
    if (areMatricesEqual(sudoku.matrix, loadedSudoku.matrix)) {
        cout << "testSaveAndLoadSudoku() passed" << endl;
        return true;
    }
    else {
        cout << "testSaveAndLoadSudoku() failed" << endl;
        return false;
    }
}

bool SudokuTest::testSolveSudokuGood() {
    // Create an instance of Sudoku
    Sudoku sudoku(9);

    // Fill Sudoku with a solvable puzzle
    vector<vector<int>> solvableSudoku = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    sudoku.matrix = solvableSudoku;

    // Copy the original puzzle for later comparison
    Sudoku originalSudoku = sudoku;

    // Solve the Sudoku
    if (sudoku.solveSudoku()) {
        // The Sudoku was successfully solved

        // Check if the solved Sudoku is different from the original
        if (areMatricesEqual(sudoku.matrix, originalSudoku.matrix)) {
            cout << "testSolveSudokuGood() failed" << endl;
            return false;
        }

        cout << "testSolveSudokuGood() passed" << endl;
        return true;
    }
    else {
        cout << "testSolveSudokuGood() failed" << endl;
        return false;
    }
}

bool SudokuTest::testSolveSudokuBad() {
    // Create an instance of Sudoku
    Sudoku sudoku(9);

    // Fill Sudoku with an unsolvable puzzle
    vector<vector<int>> unsolvableSudoku = {
        {1,2,3,7,4,5,0,0,0},
        {4,5,6,8,2,3,0,0,0},
        {7,8,9,6,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };

    sudoku.matrix = unsolvableSudoku;

    // Copy the original puzzle for later comparison
    Sudoku originalSudoku = sudoku;

    // Try to solve the Sudoku
    if (sudoku.solveSudoku()) {
        // The Sudoku was successfully solved (unexpected)
        cout << "testSolveSudokuBad() failed" << endl;
        return false;
    }
    else {
        // Check if the original puzzle is unchanged
        if (!areMatricesEqual(sudoku.matrix, originalSudoku.matrix)) {
            cout << "testSolveSudokuBad() failed" << endl;
            return false;
        }
        cout << "testSolveSudokuBad() passed" << endl;
        return true;
    }
}

bool SudokuTest::testValidateSudokuGood() {

    Sudoku sudoku1(9);
    Sudoku sudoku2(9);
    Sudoku sudoku3(9);

    // Test case 1: Valid Sudoku
    vector<vector<int>> validSudoku1 = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku1.matrix = validSudoku1;

    // Test case 2: Invalid Sudoku (duplicate in a row)
    vector<vector<int>> invalidSudoku1 = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 1}  // Duplicate 1 in the last row
    };
    sudoku2.matrix = invalidSudoku1;

    // Test case 3: Invalid Sudoku (duplicate in a column)
    vector<vector<int>> invalidSudoku2 = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 5}  // Duplicate 5 in the last column
    };
    sudoku3.matrix = invalidSudoku2;

    // Run the tests
    bool test1 = sudoku1.validateSudoku();
    bool test2 = !sudoku2.validateSudoku();
    bool test3 = !sudoku3.validateSudoku();

    if (test1 && test2 && test3) {
        cout << "testValidateSudokuGood() passed" << endl;
        return true;
    }
    else
    {
        cout << "testValidateSudokuGood() failed" << endl;
        return false;
    }
}

// Test function for validating bad Sudoku cases
bool SudokuTest::testValidateSudokuBad() {

    Sudoku sudoku1(9);
    Sudoku sudoku2(9);
    Sudoku sudoku3(9);

    // Test case 1: Two same numbers in a row
    vector<vector<int>> badSudoku1 = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 2}  // Duplicate 2 in the last row
    };
    sudoku1.matrix = badSudoku1;

    // Test case 2: Two same numbers in a column
    vector<vector<int>> badSudoku2 = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {9, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 9, 2, 8, 6, 1, 7, 9}  // Duplicate 9 in the last column and second column
    };
    sudoku2.matrix = badSudoku2;

    // Test case 3: One number in the same row and column as another
    vector<vector<int>> badSudoku3 = {
        {7, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 5}  // Duplicate 5 in the last row and column 
    };
    sudoku3.matrix = badSudoku3;

    // Run the tests
    sudoku1.validateSudoku();
    int errors1 = sudoku1.getNumOfErrors();

    sudoku2.validateSudoku();
    int errors2 = sudoku2.getNumOfErrors();

    sudoku3.validateSudoku();
    int errors3 = sudoku3.getNumOfErrors();

    if (errors1 == 1 && errors2 == 3 && errors3 == 2) {
        cout << "testValidateSudokuBad() passed" << endl;
        return true;
    }
    else
    {
        cout << "testValidateSudokuBad() failed" << endl;
        return false;
    }
}

// Test function for validating bad Sudoku cases
bool SudokuTest::testValidateSudokuEmpty() {

    Sudoku sudoku1(9);

    bool b = sudoku1.validateSudoku();

    if (!b) {
        cout << "testValidateSudokuEmpty() passed" << endl;
        return true;
    }
    else
    {
        cout << "testValidateSudokuEmpty() failed" << endl;
        return false;
    }
}

// Test function for generating and validating Sudoku
bool SudokuTest::testGenerateSudoku() {
    // Generate a Sudoku puzzle
    Sudoku sudoku(9);
    sudoku.fillGrid();

    // Validate the generated Sudoku puzzle
    bool isValid = sudoku.validateSudoku();

    if (isValid) {
        cout << "testGenerateSudoku() passed" << endl;
        return true;
    }
    else
    {
        cout << "testGenerateSudoku() failed" << endl;
        return false;
    }

}

// Function to test the generation with removal limit
bool SudokuTest::testGenerateSudokuWithLimit() {
    // Generate a Sudoku puzzle with removal limit

    Sudoku sudoku(9);
    sudoku.generateSudoku();

    // Validate the generated Sudoku puzzle
    bool isValid = sudoku.validateSudoku();

    int count = 0;
    for (int rowStart = 0; rowStart < 9; rowStart += 3) {
        for (int colStart = 0; colStart < 9; colStart += 3) {

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int row = rowStart + i;
                    int col = colStart + j;

                    // checks if the element is not 0
                    if (sudoku.matrix[row][col] != 0) {
                        count++;
                    }
                }
            }
        }
    }

    if (count < 54) {
        cout << "testGenerateSudokuWithLimit() passed" << endl;
        return true;
    }
    else
    {
        cout << "testGenerateSudokuWithLimit() failed" << endl;
        return false;
    }
}

bool SudokuTest::testSetUpGood() {
    Sudoku sudoku(9);

    vector<vector<int>> mat = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    sudoku.matrix = mat;

    // Test if the matrix is solved
    sudoku.solveSudoku();

    bool i = sudoku.checkSetUp(mat);

    if (i) {
        cout << "testSetUp() passed" << endl;
        return true;
    }
    else
    {
        cout << "testSetUp() failed" << endl;
        return false;
    }
}

bool SudokuTest::testSetUpBad() {
    Sudoku sudoku(9);

    vector<vector<int>> mat = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    sudoku.matrix = mat;

    // Test if the matrix is solved
    sudoku.solveSudoku();
    
    vector<vector<int>> mat1 = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 7, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };

    bool op = sudoku.checkSetUp(mat1);

    if (!op) {
        cout << "testSetUp() passed" << endl;
        return true;
    }
    else
    {
        cout << "testSetUp() failed" << endl;
        return false;
    }
}

void SudokuTest::runAllTests() {
    this->testSaveAndLoadSudoku();
    this->testSolveSudokuGood();
    this->testSolveSudokuBad();
    this->testValidateSudokuGood();
    this->testValidateSudokuBad();
    this->testValidateSudokuEmpty();
    this->testGenerateSudoku();
    this->testGenerateSudokuWithLimit();
    this->testSetUpGood();
    this->testSetUpBad();
}