/**
 * Name of program: EECS 348 Assignment 4 - Sudoku Solver
 * Brief description of the program: Object-oriented recursive backtracking Sudoku solver reading puzzle files.
 * Inputs: puzzle1.txt, puzzle2.txt, puzzle3.txt, puzzle4.txt, puzzle5.txt
 * Output: Solved Sudoku grids or "No solution found" for each puzzle file.
 * All collaborators: None
 * Other sources for the code: None.
 * Author's full name: Dalton Brockert
 * Creation date: October 15, 2026
 */

#include <iostream>  // Include input/output stream library
#include <fstream>   // Include file stream library for reading puzzle files
#include <vector>    // Include vector container library for dynamic arrays
#include <string>    // Include string library for handling filenames

using namespace std; // Use standard namespace to avoid prefixing std::

// Class representing a Sudoku solver using object-oriented principles
class SudokuSolver {
private:
    char board[9][9]; // 2D character array representing the 9x9 Sudoku grid

    // Check if placing a number in a specific row, col, and block is valid
    bool isValid(int row, int col, char num) {
        for (int i = 0; i < 9; i++) { // Loop through each cell in the current row and column
            if (board[row][i] == num) return false; // Return false if number already exists in the row
            if (board[i][col] == num) return false; // Return false if number already exists in the column
        }
        int startRow = row - row % 3; // Calculate the starting row index of the 3x3 sub-grid
        int startCol = col - col % 3; // Calculate the starting column index of the 3x3 sub-grid
        for (int i = 0; i < 3; i++) { // Loop through the 3 rows of the sub-grid
            for (int j = 0; j < 3; j++) { // Loop through the 3 columns of the sub-grid
                if (board[i + startRow][j + startCol] == num) return false; // Return false if found in 3x3 block
            }
        }
        return true; // Return true if the placement is valid
    }

    // Recursive backtracking function to solve the Sudoku puzzle
    bool solve(int row, int col) {
        if (row == 9) return true; // Return true if we have successfully filled past the last row
        if (col == 9) return solve(row + 1, 0); // Move to the next row if we reach the end of the current column
        if (board[row][col] != '_') return solve(row, col + 1); // Skip pre-filled cells and move to the next column

        for (char num = '1'; num <= '9'; num++) { // Try every digit from '1' to '9' for the empty cell
            if (isValid(row, col, num)) { // Check if the current digit is valid in this position
                board[row][col] = num; // Place the digit into the board cell temporarily
                if (solve(row, col + 1)) return true; // Recursively attempt to solve for the next cell
                board[row][col] = '_'; // Backtrack and reset the cell to blank if solution fails
            }
        }
        return false; // Return false to trigger backtracking when no valid digits fit
    }

public:
    // Constructor to initialize an empty Sudoku board
    SudokuSolver() {
        for (int i = 0; i < 9; i++) { // Loop through all rows
            for (int j = 0; j < 9; j++) { // Loop through all columns
                board[i][j] = '_'; // Initialize each cell with an underscore character
            }
        }
    }

    // Method to load a Sudoku puzzle from a specified text file
    bool loadPuzzle(const string& filename) {
        ifstream file(filename); // Open the puzzle file for reading
        if (!file.is_open()) return false; // Return false if the file fails to open
        for (int i = 0; i < 9; i++) { // Loop through all 9 board rows
            for (int j = 0; j < 9; j++) { // Loop through all 9 board columns
                file >> board[i][j]; // Read a single character from the file into the board
            }
        }
        file.close(); // Close the file stream after reading is complete
        return true; // Return true indicating successful file load
    }

    // Method to print the current state of the Sudoku board to the console
    void printBoard() {
        for (int i = 0; i < 9; i++) { // Loop through each row of the board
            for (int j = 0; j < 9; j++) { // Loop through each column of the board
                cout << board[i][j] << " "; // Print the character followed by a space
            }
            cout << endl; // Print a newline character at the end of each row
        }
    }

    // Public wrapper method to start the solving process
    bool solvePuzzle() {
        return solve(0, 0); // Initiate recursive backtracking starting from top-left cell (0, 0)
    }
};

// Main execution function
int main() {
    string files[] = {"puzzle1.txt", "puzzle2.txt", "puzzle3.txt", "puzzle4.txt", "puzzle5.txt"}; // Array of the five puzzle filenames[cite: 1]

    for (int k = 0; k < 5; k++) { // Loop through each of the five puzzle files
        SudokuSolver solver; // Instantiate a new SudokuSolver object for each puzzle
        cout << "File: " << files[k] << endl; // Print the current puzzle filename[cite: 4]
        
        if (solver.loadPuzzle(files[k])) { // Load the puzzle from file and check for success
            cout << "Original Puzzle:" << endl; // Print header for initial puzzle state
            solver.printBoard(); // Print the unsolved puzzle grid to console[cite: 4]
            
            if (solver.solvePuzzle()) { // Execute solver and check if a solution exists
                cout << "Solution:" << endl; // Print header for solved state
                solver.printBoard(); // Print the solved puzzle grid to console[cite: 4]
            } else {
                cout << "No solution found" << endl; // Print failure message if no solution exists[cite: 4]
            }
        } else {
            cout << "Error opening file: " << files[k] << endl; // Print error message if file loading fails
        }
        cout << "-------------------------" << endl; // Print a separator line between puzzles
    }

    return 0; // Return 0 to indicate successful program termination
}