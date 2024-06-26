#include "sudoku.hpp"
#include "file.hpp"
#include "tests.hpp"
#include <iostream>
#include <fstream> 
#include <limits>
#include <stdexcept>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::stoi;
using std::string;
using std::numeric_limits;
using std::streamsize; 
using std::runtime_error;

void game(string file1, string file2, string file3);
void testing();

/*
last edited 27.12.2023. by Ivana Radovanovic
*/

int main(int argc, char* argv[]) {

    string fileInput = argv[1];
    string fileOutput = argv[2];
    string fileSolutions = argv[3];

    try {

        if (argc != 4) {
            throw runtime_error("Not using the correct number of arguments");
        }

        game(fileInput, fileOutput, fileSolutions);
        //testing();
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;  // indicates an error
    }

    return 0;
}

void game(string fileInput,string fileOutput,string fileSolutions) {

    cout << "Welcome to Sudoku Game!" << endl;
    Sudoku sudoku(9);
    int menuChoice;
    bool playAgain = true;

    while (playAgain) {

        sudoku.resetMatrix();
        cout << "\n1. Load sudoku from file" << endl;
        cout << "2. Generate a new sudoku" << endl;
        cout << "3. Quit" << endl;
        cout << "\nEnter your choice: ";

        if (!(cin >> menuChoice)) {
            cout << "\nInvalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (menuChoice) {
        case 1:
        {
            FileHandler::loadSudoku(sudoku, fileInput);
            break;
        }

        case 2:
        {
            sudoku.generateSudoku();
            FileHandler::saveLastMatrix(sudoku, fileInput);
            break;
        }
        case 3:
        {
            playAgain = false;
            sudoku.~Sudoku();
            cout << "Exiting the game. Goodbye!" << endl;
            return;
        }
        default:
            cout << "Invalid choice. Please choose again." << endl;
        }

        sudoku.countNonZeroElements();
        FileHandler::saveSudoku(sudoku, fileSolutions);

        int solveOption;
        sudoku.setNumOfGames(sudoku.getNumOfGames() + 1);

        cout << "\nOriginal Sudoku:\n " << endl;
        sudoku.print();

        cout << "\nChoose an option:" << endl;
        cout << "1. Let the computer solve sudoku" << endl;
        cout << "2. Solve sudoku by yourself" << endl;
        cout << "3. Quit" << endl;
        cout << "\nEnter your choice: ";
        cin >> solveOption;

        if (cin.fail()) {
            cout << "\nInvalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (solveOption) {
        case 1:
        {
            bool k = sudoku.solveSudoku();
            if (k == false) {
                cout << "\nNot able to find solutin." << endl;
            }
            else {
                cout << "\nSolved Sudoku: " << endl;
                FileHandler::saveSudoku(sudoku, fileSolutions);
            };

            sudoku.print();
            break;
        }

        case 2:
        {
            string n;
            cout << "\nClick enter when you solve the puzzle: ";
            cin >> n;

            FileHandler::loadSudoku(sudoku, fileOutput);
            FileHandler::saveSudoku(sudoku, fileSolutions);

            vector<vector<int>> mat = FileHandler::loadLastMatrix(fileInput);

            if (sudoku.checkSetUp(mat)) {
                cout << "\nWrong sudoku puzzle solved." << endl;
                continue;
            }
            sudoku.print();
 
            break;
        }

        case 3:
        {
            playAgain = false;
            sudoku.~Sudoku();
            cout << "Exiting the game. Goodbye!" << endl;
            return;
        }
        default:
            cout << "Invalid choice. Returning to main menu." << endl;
        }

        if (sudoku.validateSudoku()) {
            cout << "Solution is good." << endl;
        }
        else {
            cout << "Solution is not good." << endl;
        }

        cout << "\nGame Statistics:" << endl;
        int num = 81 - sudoku.getNumOfErrors();
        sudoku.setNumOfGoodValues(num);
        cout << "Number of correctly placed fields: " << sudoku.getNumOfGoodValues() - sudoku.getNumOfFilled() << endl;
        cout << "Number of errors: " << sudoku.getNumOfErrors() << endl;
        cout << "Number of played games: " << sudoku.getNumOfGames() << endl;

        int playAgainChoice;

        cout << "\nDo you want to play again?  (1 for Yes, 0 for No): " << endl;
        cin >> playAgainChoice;

        if (playAgainChoice == 1) {
            playAgain = true;
        }
        else if (playAgainChoice == 0) {
            sudoku.~Sudoku();
            cout << "\nExiting the game. Goodbye!" << endl;
            playAgain = false;
        }
        else {
            cout << "\nInvalid input. Please enter 0 or 1." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    };
};

void testing() {
    SudokuTest test;
    test.runAllTests();
}
