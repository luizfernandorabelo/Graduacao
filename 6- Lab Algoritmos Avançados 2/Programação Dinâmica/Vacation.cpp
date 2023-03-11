#include <iostream>

using namespace std;


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


int evaluateLCS(string const &str1, string const &str2) {

    int length1 = str1.length(), length2 = str2.length();
    int** lengthTable = initializeLengthTable(length1 + 1, length2 + 1);

    for (int i = 1; i <= length1; i++) {
        char c1 = str1[i-1];
        for (int j = 1; j <= length2; j++) {
            char c2 = str2[j-1];
            lengthTable[i][j] = c1 == c2 ? lengthTable[i-1][j-1] + 1 : max(lengthTable[i-1][j], lengthTable[i][j-1]);
        }
    }

    int lcs = lengthTable[length1][length2];  // longest common subsequence

    deleteLengthTable(lengthTable, length1);

    return lcs;
}


int main(void) {

    int currentCase = 1;
    string str1, str2;

    while (getline(cin, str1) && getline(cin, str2)) {
        cout << "Case #" << currentCase++ << ": you can visit at most " << evaluateLCS(str1, str2) << " cities.\n";
    }

    return 0;
}
