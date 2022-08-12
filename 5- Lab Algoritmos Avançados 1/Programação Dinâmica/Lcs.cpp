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


int** buildLengthTable(string const &str1, string const &str2) {

    int length1 = str1.length(), length2 = str2.length();
    int** lengthTable = initializeLengthTable(length1 + 1, length2 + 1);

    for (int i = 1; i <= length1; i++) {
        char c1 = str1[i-1];
        for (int j = 1; j <= length2; j++) {
            char c2 = str2[j-1];
            lengthTable[i][j] = c1 == c2 ? lengthTable[i-1][j-1] + 1 : max(lengthTable[i-1][j], lengthTable[i][j-1]);
        }
    }

    return lengthTable;
}


string reconstructLcsFromLengthTable(int** lengthTable, string const &str1, string const &str2) {

    string lcs = "";
    int i = str1.length(), j = str2.length();

    while (i >= 1 && j >= 1) {
        if (str1[i-1] == str2[j-1]) {
            lcs = str1[i-1] + lcs;
            i--;
            j--;
        }
        else if (lengthTable[i-1][j] > lengthTable[i][j-1]) {
            i--;
        }
        else {
            j--;
        }
    }

    return lcs;
}


string evaluateLongestCommonSubsequence(string const &str1, string const &str2) {

    if (str1.length() == 0 || str2.length() == 0)
        return "";

    int** lengthTable = buildLengthTable(str1, str2);

    string lcs = reconstructLcsFromLengthTable(lengthTable, str1, str2);

    deleteLengthTable(lengthTable, str1.length());

    return lcs;
}


int main(void) {

    string str1, str2;
    cin >> str1 >> str2;

    string lcs = evaluateLongestCommonSubsequence(str1, str2);

    cout << lcs << "\n";

    return 0;
}
