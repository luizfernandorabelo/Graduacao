#include <iostream>
#include <vector>

using namespace std;


struct WordGrid {

    vector<vector<bool>> marks;
    vector<string> elements;
    int totalRows;
    int totalCols;

    WordGrid(int tRows, int tCols): 
        marks(tRows, vector<bool>(tCols, false))
    {
        totalRows = tRows;
        totalCols = tCols;
    }

};


WordGrid* readWordGrid() {

    int totalRows, totalCols;
    cin >> totalRows >> totalCols;

    WordGrid* wordGrid = new WordGrid(totalRows, totalCols);

    for (int i = 0; i < wordGrid->totalRows; i++) {
        string line; cin >> line;
        wordGrid->elements.push_back(line);
    }

    return wordGrid;
}


vector<pair<int,int>> getUnvisitedNeighborCoordinates(WordGrid* wordGrid, int i, int j) {

    vector<pair<int,int>> coordinates;

    if (i - 1 >= 0 && !wordGrid->marks[i-1][j])
        coordinates.push_back({ i-1, j });
    if (j + 1 < wordGrid->totalCols && !wordGrid->marks[i][j+1])
        coordinates.push_back({ i, j + 1 });
    if (i + 1 < wordGrid->totalRows && !wordGrid->marks[i+1][j])
        coordinates.push_back({ i+1, j });
    if (j - 1 >= 0 && !wordGrid->marks[i][j-1])
        coordinates.push_back({ i, j-1 });

    return coordinates;
}


bool isWordAtGridTheTargetWord(WordGrid* wordGrid, string &targetWord, string &currentWord, int i, int j) {

    if (wordGrid->elements[i][j] != targetWord[currentWord.length()])
        return false;

    string currentCopy = currentWord + wordGrid->elements[i][j];

    if (currentCopy == targetWord)
        return true;

    wordGrid->marks[i][j] = true;
    vector<pair<int,int>> neighborCoords = getUnvisitedNeighborCoordinates(wordGrid, i, j);

    for (auto neighbor : neighborCoords) {
        if (isWordAtGridTheTargetWord(wordGrid, targetWord, currentCopy, neighbor.first, neighbor.second))
            return true;
    }

    wordGrid->marks[i][j] = false;

    return false;
}


bool doesWordGridContainTargetWord(WordGrid* wordGrid, string &targetWord) {

    for (int i = 0; i < wordGrid->totalRows; i++) {
        for (int j = 0; j < wordGrid->totalCols; j++) {
            string currentWord = "";
            if (isWordAtGridTheTargetWord(wordGrid, targetWord, currentWord, i, j))
                return true;
        }
    }

    return false;
}


int main(void) {

    WordGrid* wordGrid = readWordGrid();
    
    string targetWord;
    cin >> targetWord >> targetWord;

    if (doesWordGridContainTargetWord(wordGrid, targetWord))
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}
