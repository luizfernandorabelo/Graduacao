#include <iostream>
#include <vector>

using namespace std;


vector<int> buildPrefixSuffixArray(const string &str) {

    int strLength = str.length();

    if (strLength <= 1)
        return { 0 };

    vector<int> prefixSuffixArray(strLength, 0);

    int prefixIdx = 0, suffixIdx = 1;

    while (suffixIdx < strLength) {
        if (str[prefixIdx] == str[suffixIdx]) {
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


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        string s; int k;
        cin >> s >> k;
        vector<int> prefixSuffixArray = buildPrefixSuffixArray(s);
        cout << s.length() + (k - 1) * (s.length() - prefixSuffixArray[s.length()-1]) << "\n";
    }

    return 0;
}
