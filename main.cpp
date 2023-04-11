#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstring>
using namespace std;

const int SIZE = 9;
const int BLOCK_SIZE = 3;

void printBoard(int board[SIZE][SIZE]) {
    for(int i=0; i<SIZE; i++) {
        if(i % BLOCK_SIZE == 0 && i != 0) {
            cout << "------+-------+------" << endl;
        }
        for(int j=0; j<SIZE; j++) {
            if(j % BLOCK_SIZE == 0 && j != 0) {
                cout << "| ";
            }
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    // Check row
    for(int i=0; i<SIZE; i++) {
        if(board[row][i] == num) {
            return false;
        }
    }

    // Check column
    for(int i=0; i<SIZE; i++) {
        if(board[i][col] == num) {
            return false;
        }
    }

    // Check block
    int blockRow = row / BLOCK_SIZE * BLOCK_SIZE;
    int blockCol = col / BLOCK_SIZE * BLOCK_SIZE;
    for(int i=0; i<BLOCK_SIZE; i++) {
        for(int j=0; j<BLOCK_SIZE; j++) {
            if(board[blockRow+i][blockCol+j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int board[SIZE][SIZE], int row, int col) {
    // Base case: board is filled
    if(row == SIZE) {
        return true;
    }

    // Compute next row and column indices
    int nextRow, nextCol;
    if(col == SIZE-1) {
        nextRow = row + 1;
        nextCol = 0;
    } else {
        nextRow = row;
        nextCol = col + 1;
    }

    // If cell is already filled, move to next cell
    if(board[row][col] != 0) {
        return solveSudoku(board, nextRow, nextCol);
    }

    // Try values 1 to 9 for current cell
    for(int num=1; num<=SIZE; num++) {
        if(isSafe(board, row, col, num)) {
            board[row][col] = num;
            if(solveSudoku(board, nextRow, nextCol)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    // Backtrack
    return false;
}

bool generateSudoku(int board[SIZE][SIZE]) {
    // Initialize board with zeros
    memset(board, 0, sizeof(board[0]) * SIZE * SIZE);

    // Fill board with random numbers
    vector<pair<int, int>> cells;
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end(), default_random_engine(time(nullptr)));
    for(auto cell : cells) {
        int row = cell.first;
        int col = cell.second;
        for(int num=1; num<=SIZE; num++) {
            if(isSafe(board, row, col, num)) {
                board[row][col] = num;
                if(!generateSudoku(board)) {
                    board[row][col] = 0;
                    continue;
                }
                return true;
            }
        }
        return false;
    }
    printBoard(board);
    return true;
}


bool isRowValid(int board[][SIZE], int row, int num) {
    for(int i = 0; i < SIZE; i++) {
        if(board[row][i] == num) {
            return false;
        }
    }
    return true;
}

bool isColValid(int board[][SIZE], int col, int num) {
    for(int i = 0; i < SIZE; i++) {
        if(board[i][col] == num) {
            return false;
        }
    }
    return true;
}

bool isBoxValid(int board[][SIZE], int boxStartRow, int boxStartCol, int num) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i+boxStartRow][j+boxStartCol] == num) {
                return false;
            }
        }
    }
    return true;
}

bool isValid(int board[][SIZE], int row, int col, int num) {
    return isRowValid(board, row, num) && isColValid(board, col, num) && isBoxValid(board, row - row%3, col - col%3, num);
}


bool findUnassignedLocation(int board[][SIZE], int& row, int& col) {
    for(row = 0; row < SIZE; row++) {
        for(col = 0; col < SIZE; col++) {
            if(board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int board[][SIZE]) {
    int row, col;
    if(!findUnassignedLocation(board, row, col)) {
        return true;
    }
    for(int num = 1; num <= SIZE; num++) {
        if(isValid(board, row, col, num)) {
            board[row][col] = num;
            if(solveSudoku(board)) {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int board[SIZE][SIZE];
    cout << "Original board:" << endl;
        generateSudoku(board);
    cout << endl;

    if(solveSudoku(board)) {
        cout << "Solution:" << endl;
        printBoard(board);
    } else {
    cout << "No solution exists." << endl;
}
return 0;
};
