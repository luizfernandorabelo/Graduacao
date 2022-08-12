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


int evaluateSubstringIndex(const string &str, const string &substr, const vector<int> &prefixSuffixArray) {

    uint i = 0, j = 0;

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
        if (j == substr.length())
            return i - substr.length();
    }

    return -1;
}


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        string str;
        int totalQueries;
        cin >> str >> totalQueries;
        for (int j = 0; j < totalQueries; j++) {
            string substr; cin >> substr;
            vector<int> prefixSuffixArray = buildPrefixSuffixArray(substr);
            if (evaluateSubstringIndex(str, substr, prefixSuffixArray) != NOT_FOUND)
                cout << "y\n";
            else
                cout << "n\n";
        }
    }
        
    return 0;
}

