#include <iostream>
#include <vector>
#include <algorithm>

#define END_DELIMITER "_"

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


string evaluateExtensionToPalindrome(const string &original) {

    string reversed = original;
    reverse(reversed.begin(), reversed.end());
    reversed += END_DELIMITER + original;

    vector<int> psArray = buildPrefixSuffixArray(reversed);

    uint fillingLength = original.length() - psArray[reversed.length() - 1];

    string extended = original;

    for (int i = fillingLength - 1; i >= 0; i--)
        extended.push_back(original[i]);

    return extended;
}


int main(void) {

    string original;

    while (cin >> original)
        cout << evaluateExtensionToPalindrome(original) << "\n";

    return 0;
}
