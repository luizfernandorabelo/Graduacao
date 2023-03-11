#include <iostream>

#define MISMATCH_PENALTY 1
#define GAP_PENALTY 1

using namespace std;

typedef unsigned int uint;


int **createAlignmentMatrix(uint str1Length, uint str2Length) {

    int **matrix = new int*[str1Length + 1];

    for (uint i = 0; i <= str1Length; i++)
        matrix[i] = new int[str2Length + 1];

    return matrix;
}


void fillAlignmentMatrix(int **matrix, const string &s1, const string &s2) {

    matrix[0][0] = 0;

    for (uint i = 1; i <= s1.length(); i++)
        matrix[i][0] = matrix[i-1][0] + GAP_PENALTY;

    for (uint i = 1; i <= s2.length(); i++)
        matrix[0][i] = matrix[0][i-1] + GAP_PENALTY;
    
    for (uint i = 1; i <= s1.length(); i++) {
        for (uint j = 1; j <= s2.length(); j++) {
            uint idx1 = i - 1, idx2 = j - 1;
            matrix[i][j] = min(
                matrix[i-1][j-1] + (s1[idx1] != s2[idx2] ? MISMATCH_PENALTY : 0),
                min(matrix[i-1][j], matrix[i][j-1]) + GAP_PENALTY
            );
        }
    }
}


void deleteAlignmentMatrix(int **matrix, uint str1Length) {
    for (uint i = 0; i <= str1Length; i++)
        delete [] matrix[i];
    delete [] matrix;
}


int main(void) {

    string s1, s2;
    uint l1, l2;

    while (cin >> l1 >> s1 >> l2 >> s2) {
        int **matrix = createAlignmentMatrix(l1, l2);
        fillAlignmentMatrix(matrix, s1, s2);
        cout << matrix[s1.length()][s2.length()] << "\n";
        deleteAlignmentMatrix(matrix, l1);
    }

    return 0;
}

