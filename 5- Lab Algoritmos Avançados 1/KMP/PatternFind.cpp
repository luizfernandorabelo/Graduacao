#include <iostream>
#include <vector>

#define NOT_FOUND -1

using namespace std;


vector<int> buildPrefixSuffixArray(const string &substr) {

    int strLength = substr.length();

    if (strLength <= 1)
        return { 0 };

    vector<int> prefixSuffixArray(strLength, 0);

    int prefixIdx = 0, suffixIdx = 1;

    while (suffixIdx < strLength) {
        if (substr[prefixIdx] == substr[suffixIdx]) {
            prefixSuffixArray[suffixIdx] = prefixIdx + 1; 
            prefixIdx++;
            suffixIdx++;
        } else if (prefixIdx != 0) {
            prefixIdx = prefixSuffixArray[prefixIdx-1];
        } else {
            suffixIdx++;
        }
    }

    return prefixSuffixArray;
}


vector<int> evaluateSubstringIndexes(const string &str, const string &substr, const vector<int> &prefixSuffixArray) {

    uint i = 0, j = 0;
    vector<int> indexes;

    while (i < str.length()) {
        if (str[i] == substr[j]) {
            i++;
            j++;
        } else {
            if (j != 0)
                j = prefixSuffixArray[j-1];
            else
                i++;
        }
        if (j == substr.length()) {
            indexes.push_back(i - substr.length());
            j = prefixSuffixArray[j-1];
        }
    }

    return indexes;
}


void printSubstringIndexesAndOccurrences(const string &str, const string &substr) {

    vector<int> prefixSuffixArray = buildPrefixSuffixArray(substr);

    vector<int> indexes = evaluateSubstringIndexes(str, substr, prefixSuffixArray);

    if (indexes.size() == 0) {
        cout << "Not Found\n\n";
        return;
    }

    cout << indexes.size() << "\n";

    for (int index : indexes)
        cout << index + 1 << " ";
    
    cout << "\n\n";
}


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        string str, substr;
        cin >> str >> substr;
        printSubstringIndexesAndOccurrences(str, substr);
    }

    return 0;
}
