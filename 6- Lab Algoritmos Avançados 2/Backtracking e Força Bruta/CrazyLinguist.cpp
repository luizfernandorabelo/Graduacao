#include <iostream>
#include <vector>
#include <unordered_map>

#define ALPHABET_SIZE 26

using namespace std;

const vector<char> CONSONANTS = {
    'b', 'c', 'd', 'f', 'g', 'h', 'j',
    'k', 'l', 'm', 'n', 'p', 'q', 'r',
    's', 't', 'v', 'w', 'x', 'y', 'z'
};

const vector<char> VOWELS = {
    'a', 'e', 'i', 'o', 'u'
};


const vector<double> PROBABILITIES = {
    12.53, 1.42, 4.68, 5.86, 13.68, 0.69,
    1.01, 0.70, 6.25, 0.44, 0.00, 4.97, 3.15,
    6.71, 8.68, 2.51, 0.88, 6.87, 7.98, 4.63,
    3.93, 0.90, 0.02, 0.22, 0.90, 0.52
};


vector<int> initCharCountVector(char firstCharacter) {
    vector<int> charCount(ALPHABET_SIZE, 0);
    charCount[firstCharacter - 'a'] = 1;
    return charCount;
}


double evaluateSBC(const string &word) {
    double sum = 0;

    for (uint i = 1; i <= word.length(); i++)
        sum += i * PROBABILITIES[word[i-1] - 'a'];

    return sum;
}


void buildWords(uint i, string &current, uint wordLength, vector<int> &charCount, double &sum, uint &totalWords) {

    if (i == wordLength) {
        sum += evaluateSBC(current);
        totalWords++;
        return;
    }

    for (char character : (i % 2 ? VOWELS : CONSONANTS)) {
        int countIdx = character - 'a';
        if (charCount[countIdx] < 2) {
            string previous = current;
            current += character;
            charCount[countIdx]++;
            buildWords(i + 1, current, wordLength, charCount, sum, totalWords);
            current = previous;
            charCount[countIdx]--;
        }
    }
}


int main(void) {

    unordered_map<string,double> knownAverages;

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        string word; cin >> word;
        string avgKey = to_string(word.length()) + word[0];
        if (knownAverages.find(avgKey) == knownAverages.end()) {
            string current(1, word[0]);
            vector<int> charCount = initCharCountVector(word[0]);
            double sum = 0;
            uint totalWords = 0;
            buildWords(1, current, word.length(), charCount, sum, totalWords);
            knownAverages[avgKey] = sum / totalWords;
        }
        if (evaluateSBC(word) < knownAverages[avgKey])
            cout << "below\n";
        else
            cout << "above or equal\n";
    }

    return 0;
}
