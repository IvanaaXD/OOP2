#include "file.hpp"
#include "sudoku.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream; 
using std::runtime_error;
using std::istringstream;
using std::ios;

FileHandler::FileHandler() {
}

FileHandler::~FileHandler() {
}

void FileHandler::loadSudoku(Sudoku& sudoku, const string& filename) {

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw runtime_error("Error opening file: " + filename);
        return;
    }

    vector<vector<int>>& matrix = sudoku.matrix;

    string line;
    int row = 0;

    while (getline(inputFile, line)) {

        istringstream iss(line);
        string token;
        int col = 0;

        while (getline(iss, token, ',')) {

            matrix[row][col++] = stoi(token);
        }

        row++;

        if (row >= matrix.size()) {
            break;  
        }
    }

    inputFile.close();
}

void FileHandler::saveSudoku(const Sudoku& sudoku, const string& filename) {
    ofstream outputFile(filename, ios::app);

    if (!outputFile.is_open()) {
        throw runtime_error("Error opening file: " + filename);
        return;
    }

    const vector<vector<int>>& matrix = sudoku.matrix;

    for (const auto& row : matrix) {
        for (int i = 0; i < row.size(); ++i) {
            outputFile << row[i];
            if (i < row.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << endl;
    }
    outputFile << endl;
    outputFile.close();
}

void FileHandler::saveLastMatrix(const Sudoku& sudoku, const string& filename) {

    ofstream outputFile(filename, ios::trunc);

    if (!outputFile.is_open()) {
        throw runtime_error("Error opening file: " + filename);
        return;
    }

    const vector<vector<int>>& matrix = sudoku.matrix;

    for (const auto& row : matrix) {
        for (int i = 0; i < row.size(); ++i) {
            outputFile << row[i];
            if (i < row.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << endl;
    }
    outputFile << endl;
    outputFile.close();
}

vector<vector<int>> FileHandler::loadLastMatrix(const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw runtime_error("Error opening file: " + filename);
        return {};  // Return an empty matrix
    }

    vector<vector<int>> mat(9, vector<int>(9, 0));

    string line;
    int row = 0;

    while (getline(inputFile, line)) {

        istringstream iss(line);
        string token;
        int col = 0;

        while (getline(iss, token, ',')) {

            mat[row][col++] = stoi(token);
        }

        row++;

        if (row >= 9) {
            break;
        }
    }

    inputFile.close();
    return mat;
}
