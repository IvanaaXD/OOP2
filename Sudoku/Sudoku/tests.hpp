#ifndef TESTS_HPP
#define TESTS_HPP
#include "sudoku.hpp"  // Include your Sudoku class header
#include "file.hpp"
#include <iostream>

using std::cout;

using std::endl;
using std::cin;
using std::cerr;
using std::stoi;
using std::string;
using std::numeric_limits;
using std::streamsize;
using std::runtime_error;

class SudokuTest {
public:

    /*
     *last edited 27.12.2023.by Ivana Radovanovic
     */

    SudokuTest();
    ~SudokuTest();

    bool areMatricesEqual(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) const;
    bool testSolveSudokuGood();
    bool testSolveSudokuBad();
    bool testValidateSudokuGood();
    bool testValidateSudokuBad();
    bool testValidateSudokuEmpty();
    bool testGenerateSudoku();
    bool testGenerateSudokuWithLimit();
    bool testSetUpGood();
    bool testSetUpBad();
    bool testSaveAndLoadSudoku();
    
    void runAllTests();
};

#endif