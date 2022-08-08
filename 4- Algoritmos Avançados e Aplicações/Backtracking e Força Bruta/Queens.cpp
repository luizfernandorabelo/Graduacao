#include <iostream>
#include <cstring>

#define BOARD_DIMENSION 8
#define NONEXISTENT_INDEX -1

using namespace std;


int** readBoardSquares() {

    int** boardSquares = new int*[BOARD_DIMENSION];

    for (int i = 0; i < BOARD_DIMENSION; i++) {
        boardSquares[i] = new int[BOARD_DIMENSION];
        for (int j = 0; j < BOARD_DIMENSION; j++)
            cin >> boardSquares[i][j];
    }

    return boardSquares;
}


bool** createMarks() {

    bool** marks = new bool*[BOARD_DIMENSION];

    for (int i = 0; i < BOARD_DIMENSION; i++) {
        marks[i] = new bool[BOARD_DIMENSION];
        memset(marks[i], false, BOARD_DIMENSION);
    }

    return marks;
}


bool isColumnMarked(bool** marks, int i, int j) {

    for (int k = 0; k < i; k++) {
        if (marks[k][j])
            return true;
    }

    return false;
}


bool isDiagonalMarked(bool** marks, int i, int j) {

    for (int k = i - 1, l = 1; k >= 0; k--, l++) {
        if (j + l < BOARD_DIMENSION && marks[k][j+l])
            return true;
        if (j - l >= 0 && marks[k][j-l])
            return true;
    }

    return false;
}


int getNextUnmarkedColumn(bool** marks, int line, int lastUnmarkedColumn) {

    for (int j = lastUnmarkedColumn + 1; j < BOARD_DIMENSION; j++) {
        if (!isColumnMarked(marks, line, j) && !isDiagonalMarked(marks, line, j))
            return j;
    }
    
    return NONEXISTENT_INDEX;
}


void evaluateHighestScoreRec(int** boardSquares, bool** marks, int currentLine, int currentScore, int &highestScore) {

    if (currentLine == BOARD_DIMENSION) {
        highestScore = currentScore > highestScore ? currentScore : highestScore;
        return;
    }

    int availableColumn = NONEXISTENT_INDEX;
    
    for (int i = 0; i < BOARD_DIMENSION; i++) {

        availableColumn = getNextUnmarkedColumn(marks, currentLine, availableColumn);

        if (availableColumn == NONEXISTENT_INDEX)
            return;

        marks[currentLine][availableColumn] = true;

        evaluateHighestScoreRec(boardSquares, marks, currentLine + 1,
                           currentScore + boardSquares[currentLine][availableColumn], highestScore);
        
        marks[currentLine][availableColumn] = false;
    }

}


int evaluateHighestScore(int** boardSquares) {

    bool **marks = createMarks();
    int highestScore = 0;

    evaluateHighestScoreRec(boardSquares, marks, 0, 0, highestScore);

    return highestScore;
}


int main(void) {

    int totalBoards; cin >> totalBoards;

    for (int i = 0; i < totalBoards; i++) {
        int** boardSquares = readBoardSquares();
        int highestScore = evaluateHighestScore(boardSquares);
        int spaces = 5 - to_string(highestScore).length();
        cout << string(spaces, ' ') << highestScore << '\n';
    }

    return 0;
}
