#ifndef FILE_HPP
#define FILE_HPP
#include "string"
#include "sudoku.hpp"

using std::string;

class FileHandler {
public:
	/**
	* default constructor
	* 	 
	* last edited 20.12.2023. by Ivana Radovanovic
	*/
	FileHandler();

	/**
	 * destructor
	 * 	 
	 * last edited 20.12.2023. by Ivana Radovanovic
	 */
	~FileHandler();

	/**
	 * loads a Sudoku puzzle from a file into the given Sudoku object.
	 * The function opens the specified file and reads the puzzle's values,
	 * populating the matrix of the Sudoku object. Each line of the file
	 * corresponds to a row in the matrix, and values are separated by commas.
	 * The function stops reading if the end of the matrix is reached or
	 * the end of the file is reached.
	 *
	 * @param sudoku The Sudoku object to load the puzzle into.
	 * @param filename The name of the file containing the Sudoku puzzle.
	 * @throw runtime_error If there is an error opening the file.
	 *
	 * last edited 20.12.2023. by Ivana Radovanovic
	 */
	static void loadSudoku(Sudoku& sudoku, const string& filename);

	/**
	 * saves the current state of a Sudoku puzzle to a file.
	 * The function opens the specified file in append mode and writes the
	 * matrix values of the Sudoku object to the file. Each row of the matrix
	 * is written as a line in the file, with values separated by commas.
	 * After writing the matrix, an empty line is added for better readability.
	 *
	 * @param sudoku The Sudoku object to save.
	 * @param filename The name of the file to save the Sudoku puzzle to.
	 * @throw runtime_error If there is an error opening the file.
	 *
	 * last edited 20.12.2023. by Ivana Radovanovic
	 */
	static void saveSudoku(const Sudoku& sudoku, const string& filename);
	
	static void saveLastMatrix(const Sudoku& sudoku, const string& filename);


	/**
	 * loads the last 9x9 matrix from a file and returns it as a vector of vectors.
	 * The function opens the specified file and reads the values line by line,
	 * populating a 9x9 matrix. Each line in the file represents a row in the matrix,
	 * and values are separated by commas. The function returns the populated matrix.
	 * If there is an error opening the file, a runtime_error is thrown, and an
	 * empty matrix is returned.
	 *
	 * @param filename The name of the file containing the Sudoku puzzle.
	 * @return A 9x9 matrix representing the last puzzle in the file.
	 * @throw runtime_error If there is an error opening the file.
	 *
	 * last edited 20.12.2023. by Ivana Radovanovic
	 */
	static vector<vector<int>> loadLastMatrix(const string& filename);

};

#endif
