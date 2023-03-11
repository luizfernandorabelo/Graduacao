#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> buildPrefixSuffixArray(const string &substr) {

    int strLength = substr.length();

    if (strLength <= 1)
        return { 0 };

    vector<int> prefixSuffixArray(strLength + 1, -1);

    int prefixIdx = 0, suffixIdx = -1;

	while (prefixIdx < strLength) {
		while (suffixIdx >= 0 && substr[prefixIdx] != substr[suffixIdx])
			suffixIdx = prefixSuffixArray[suffixIdx];
		prefixIdx++;
		suffixIdx++;
		prefixSuffixArray[prefixIdx] = suffixIdx;
	}

    return prefixSuffixArray;
}


string findSecretWord(const string &original) {

    string reversed = original;
    reverse(reversed.begin(), reversed.end());

    vector<int> psArray = buildPrefixSuffixArray(original);

    int i = 0, j = 0, greatestLength = -1;

	while (i < (int) reversed.length()) {
		while (j >= 0 && reversed[i] != original[j]) j = psArray[j];
		i++; j++;
		if (j > greatestLength) greatestLength = j;
		if (j == (int) original.length()) j = psArray[j];
	}

    string secret = "";
    for (int i = greatestLength - 1; i >= 0; i--)
        secret += original[i];

    return secret;
}


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        string original; cin >> original;
        cout << findSecretWord(original) << "\n";
    }

    return 0;
}
