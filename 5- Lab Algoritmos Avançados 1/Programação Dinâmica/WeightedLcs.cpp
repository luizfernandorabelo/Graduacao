#include <iostream>

#define ALPHABET_LENGTH 26

using namespace std;


int* readAlphabetLetterPrices() {

    int* letterPrices = new int[ALPHABET_LENGTH];

    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        cin >> letterPrices[i];
    }

    return letterPrices;
}


int** initializeLengthTable(int totalRows, int totalCols) {

    int** table = new int*[totalRows];

    for (int i = 0; i < totalRows; i++)
        table[i] = new int[totalCols];

    for (int i = 0; i < totalRows; i++)
        table[i][0] = 0;

    for (int j = 0; j < totalCols; j++)
        table[0][j] = 0;
    
    return table;
}


void deleteLengthTable(int** table, int totalRows) {

    for (int i = 0; i <= totalRows; i++)
        delete [] table[i];
    
    delete [] table;
}


int evaluateMostExpensiveCommonSubsequence(string const &str1, string const &str2, int len1, int len2, int* letterPrices) {

    if (len1 == 0 || len2 == 0)
        return 0;

    int** lengthTable = initializeLengthTable(len1 + 1, len2 + 1);

    for (int i = 1; i <= len1; i++) {
        char c1 = str1[i-1];
        for (int j = 1; j <= len2; j++) {
            char c2 = str2[j-1];
            if (c1 == c2)
                lengthTable[i][j] = max(lengthTable[i-1][j-1] + letterPrices[c1 - 'a'], max(lengthTable[i-1][j], lengthTable[i][j-1]));
            else
                lengthTable[i][j] = max(lengthTable[i-1][j], lengthTable[i][j-1]);
        }
    }

    int mostExpensive = lengthTable[len1][len2];

    deleteLengthTable(lengthTable, str1.length());

    return mostExpensive;
}


int main(void) {

    int len1, len2;
    cin >> len1 >> len2;

    int* letterPrices = readAlphabetLetterPrices();

    string str1, str2;
    cin >> str1 >> str2;

    cout << evaluateMostExpensiveCommonSubsequence(str1, str2, len1, len2, letterPrices) << "\n";

    delete [] letterPrices;

    return 0;
}

