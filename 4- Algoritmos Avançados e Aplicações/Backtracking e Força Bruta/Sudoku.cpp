#include <iostream>

#define EMPTY_SPOT 0
#define GRID_DIMENSION 9
#define SQUARE_DIMENSION 3

using namespace std;


int** createSudokuGrid(void) {

    int** grid = new int*[GRID_DIMENSION];

    for (int i = 0; i < GRID_DIMENSION; i++) {
        grid[i] = new int[GRID_DIMENSION];
    }

    return grid;
}


int **readSudokuGrid(void) {

    int** grid = createSudokuGrid();

    for (int i = 0; i < GRID_DIMENSION; i++) {
        for (int j = 0; j < GRID_DIMENSION; j++) {
            cin >> grid[i][j];
        }
    }

    return grid;
}


void printSudokuGrid(int** sudokuGrid) {
    for (int i = 0; i < GRID_DIMENSION; i++) {
        for (int j = 0; j < GRID_DIMENSION; j++) {
            cout << sudokuGrid[i][j] << " ";
        }
        cout << "\n";
    }
}


bool isValidRow(int** sudokuGrid, int i, int insertedNumber) {

    for (int j = 0; j < GRID_DIMENSION; j++)
        if (sudokuGrid[i][j] == insertedNumber)
            return false;

    return true;
}


bool isValidColumn(int** sudokuGrid, int j, int insertedNumber) {

    for (int i = 0; i < GRID_DIMENSION; i++)
        if (sudokuGrid[i][j] == insertedNumber)
            return false;

    return true;
}


bool isValidSquare(int** sudokuGrid, int i, int j, int insertedNumber) {

    int topLeftRow = i / SQUARE_DIMENSION * 3, topLeftColumn = j / SQUARE_DIMENSION * 3;

    for (int m = 0; m < SQUARE_DIMENSION; m++) {
        for (int n = 0; n < SQUARE_DIMENSION; n++) {
            if (sudokuGrid[topLeftRow + m][topLeftColumn + n] == insertedNumber)
                return false;
        }
    }
    
    return true;
}


bool isValidPosition(int** sudokuGrid, int i, int j, int insertedNumber) {
    return isValidRow(sudokuGrid, i, insertedNumber) &&
           isValidColumn(sudokuGrid, j, insertedNumber) &&
           isValidSquare(sudokuGrid, i, j, insertedNumber);
}


bool solveSudoku(int** sudokuGrid, int i, int j) {

    if (j == GRID_DIMENSION) {
        i++;
        j = 0;
    }

    if (i == GRID_DIMENSION)
        return true;

    if (sudokuGrid[i][j] != EMPTY_SPOT)
        return solveSudoku(sudokuGrid, i, j + 1);

    for (int insertedNumber = 1; insertedNumber <= GRID_DIMENSION; insertedNumber++) {
        if (isValidPosition(sudokuGrid, i, j, insertedNumber)) {
            sudokuGrid[i][j] = insertedNumber;
            if (solveSudoku(sudokuGrid, i, j + 1))
                return true;
            sudokuGrid[i][j] = EMPTY_SPOT;
        }
    }

    return false;
}


int main(void) {

    int** sudokuGrid = readSudokuGrid();

    if (solveSudoku(sudokuGrid, 0, 0))
        printSudokuGrid(sudokuGrid);
    else
        cout << "No solution\n";

    return 0;
}
