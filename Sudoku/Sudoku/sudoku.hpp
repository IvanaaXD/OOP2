#ifndef SUDOKU_HPP
#define SUDOKU_HPP
#include <iostream>
#include <vector>

using std::vector;

class Sudoku {
private:
    int numOfErrors;
    int numOfGoodValues;
    int numOfGames;
    int numOfFilled;
    int counter;

public:
    vector<vector<int>> matrix;

    /*
    constructor for empty sudoku

    last edited 20.12.2023. by Ivana Radovanovic
    */
    Sudoku(int size);

    /*
    destructor for sudoku

    last edited 25.12.2023. by Ivana Radovanovic
    */
    ~Sudoku() {
        for (vector<int>& row : matrix) {
            row.clear();
        }
        matrix.clear();
    }

    /*
    counting number of elements that are not zero

    last edited 21.12.2023. by Ivana Radovanovic
    */
    void countNonZeroElements();

    /*
    printing sudoku matrix

    last edited 20.12.2023. by Ivana Radovanovic
    */
    void print();

    /*
    resets sudoku matrix

    last edited 28.12.2023. by Ivana Radovanovic
    */
    void resetMatrix();

    /*
    getters and setters for private attributes

    last edited 20.12.2023. by Ivana Radovanovic
    */

    void setCounter(int);
    void setNumOfErrors(int);
    void setNumOfGoodValues(int);
    void setNumOfGames(int);
    void setNumOfFilled(int);

    int getCounter() const;
    int getNumOfErrors() const;
    int getNumOfGoodValues() const;
    int getNumOfGames() const;
    int getNumOfFilled () const;

    /*
    checking if every element in matrix is different from 0

    last edited 21.12.2023. by Ivana Radovanovic
    */
    bool checkMatrix();

    /**
     * recursive helper function for solving the Sudoku puzzle 
     * using backtracking by iterating through each cell in the 
     * puzzle. If a cell is empty (contains a value of 0), it 
     * attempts to fill the cell with a valid value from 1 to 9. 
     * For each valid value, the function recursively calls itself 
     * to continue solving the puzzle. If a valid solution is found, 
     * the counter is incremented, and the function returns true.
     * If no valid solution is found, the function backtracks and tries 
     * a different value for the current cell. The process continues 
     * until all cells are filled, and at least one solution is found. 
     * The counter is updated to reflect the total number of solutions.
     * 
     * @return True if at least one solution is found, false otherwise.
     * 
     * last edited 27.12.2023. by Ivana Radovanovic
    */
    bool solveSudokuHelper();

    /**
     * attempts to solve the Sudoku puzzle using a backtracking 
     * algorithm by initializing a counter to keep track of the 
     * number of solutions found. It calls the solveSudokuHelper 
     * function to explore possible solutions. After the helper 
     * function is executed, the counter is checked to determine 
     * if at least one solution was found. If a solution is found, 
     * the function returns true; otherwise, it returns false.
     * 
     * @return True if at least one solution is found, false otherwise.
     *
     * last edited 27.12.2023. by Ivana Radovanovic
    */
    bool solveSudoku();

    /**
     * checks if it is safe to place a number in a specific cell of the 
     * Sudoku grid by checking for conflicts in the row, column, and 3x3 
     * subgrid of the specified cell. If the given value can be placed 
     * in the cell without violating the rules of Sudoku, the function 
     * returns true; otherwise, it returns false.
     * 
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param value The value to be placed in the cell.
     * @return True if it is safe to place the value in the cell, false otherwise.
     * 
     * last edited 27.12.2023. by Ivana Radovanovic
     */
    bool isSafe(int row, int col, int value) const;

    /**
     * recursively fills the Sudoku grid by placing numbers in empty cells
     * by iterating through each cell in the Sudoku grid. If the cell is
     * empty (contains 0), it generates a random permutation of possible 
     * numbers (1 to 9) and tries placing each number in the cell. It checks 
     * if the number is safe to place according to Sudoku rules. If a safe 
     * number is found, it places the number and recursively calls the function 
     * to fill the next cell. If the Sudoku can be filled successfully, the 
     * function returns true. If no valid number is found for a cell, it backtracks 
     * and resets the cell value to 0, trying different numbers until a valid 
     * combination is found or all possibilities are exhausted.
     * 
     * @return True if the Sudoku grid is successfully filled, false otherwise.
     *
     * last edited 27.12.2023. by Ivana Radovanovic
    */
    bool fillGrid();

    /*
    calls fillGrid and removeElementsFromGrid functions so
    the matrix is filled and than some elements are removed

    last edited 27.12.2023. by Ivana Radovanovic
    */
    void generateSudoku();

    /**
     * removes a random number of elements from each 3x3 matrix in 
     * the Sudoku grid by iterating through each 3x3 matrix, generating 
     * a random number between 4 and 9 to determine the number of elements 
     * to remove. It then creates a list of unique positions within the 
     * matrix, shuffles the positions randomly, and removes the specified 
     * number of elements from the shuffled positions. If an element is not 
     * already deleted, it sets the element to 0, representing an empty cell 
     * in the Sudoku grid.
     *
     * last edited 27.12.2023. by Ivana Radovanovic
    */
    void removeElementsFromGrid();

    /**
     * checks the validity of a 3x3 matrix within the Sudoku grid.
     * The function uses an unordered set to keep track of unique values
     * within the matrix. It iterates through the matrix, checking for
     * invalid values (less than 1 or greater than 9) or duplicates.
     *
     * @param rowStart The starting row index of the 3x3 matrix.
     * @param colStart The starting column index of the 3x3 matrix.
     * @return true if the matrix is valid, false if invalid values 
     * or duplicates are found.
     *
     * last edited 27.12.2023. by Ivana Radovanovic
    */
    bool isValidMatrix(int rowStart, int colStart) const;

    /**
     * checks for duplicate values in the same row as the specified
     * cell (row, col) of the Sudoku matrix by searching to the right 
     * and to the left of the specified cell.
     *
     * @param row - The row index of the current cell.
     * @param col - The column index of the current cell.
     * @param duplicate - The value to check for duplicates in the row.
     * @return true if a duplicate is found, indicating an error; false otherwise.
     * 
     * last edited 27.12.2023. by Ivana Radovanovic
     */
    bool checkRowErrors(int row, int col, int duplicate);
    
    /**
     * checks for duplicate values in the same column as the specified
     * cell (row, col) of the Sudoku matrix by searching up and down
     * of the specified cell.
     *
     * @param row - The row index of the current cell.
     * @param col - The column index of the current cell.
     * @param duplicate - The value to check for duplicates in the row.
     * @return true if a duplicate is found, indicating an error; false otherwise.
     *
     * last edited 27.12.2023. by Ivana Radovanovic
     */
    bool checkColumnErrors(int row, int col, int duplicate);
    
    /**
     * validates the current state of the sudoku matrix, checking
     * for errors in each 3x3 matrix
     * an error occurs if there are duplicate values within a row,
     * column, or 3x3 matrix. The number of errors is counted and
     * stored in the numOfErrors member variable.
     * returns true if the sudoku matrix is valid (no errors),
     * false otherwise.
     *
     * last edited 27.12.2023. by Ivana Radovanovic
    */
    bool validateSudoku();

    /**
     * checks if a given 9x9 matrix matches the initial setup of the 
     * Sudoku grid by comparing each element of the provided matrix
     * with the corresponding element in the internal matrix of the 
     * Sudoku object. 
     * If a non-zero value in the provided matrix differs from the 
     * internal matrix, the function returns false, indicating a 
     * mismatch. If all corresponding values match or are zero, the 
     * function returns true, signifying a correct setup.
     *
     * @param mat The 9x9 matrix to be checked against the internal Sudoku matrix.
     * @return true if the provided matrix matches the Sudoku setup, false otherwise.
     * 
     * last edited 27.12.2023. by Ivana Radovanovic
     */    
    bool checkSetUp(vector<vector<int>>& mat);
 };

#endif
