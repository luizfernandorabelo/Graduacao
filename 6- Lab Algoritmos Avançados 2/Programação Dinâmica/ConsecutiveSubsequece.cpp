#include <iostream>
#include <vector>
#include <map>

using namespace std;


typedef unsigned int uint;


vector<int> readArray(int totalNumbers) {

    vector<int> array;

    for (int i = 0; i < totalNumbers; i++) {
        int number; cin >> number;
        array.push_back(number);
    }

    return array;
}


void printMaxLengthSubsequence(const vector<int> &array) {

    map<int,int> lengths;

    int firstTerm = -1, maxLength = 0;

    for (int currentTerm : array) {
        lengths[currentTerm] = lengths[currentTerm-1] + 1;
        if (lengths[currentTerm] > maxLength) {
            maxLength = lengths[currentTerm];
            firstTerm = currentTerm - lengths[currentTerm] + 1;
        }
    }

    cout << maxLength << "\n";

    int nextTerm = firstTerm;

    for (uint i = 0; i < array.size(); i++) {
        if (array[i] == nextTerm) {
            cout << i + 1 << " ";  // 1-based indexes
            nextTerm++;
        }
    }

    cout << "\n";
}


int main(void) {

    int totalNumbers;
    cin >> totalNumbers;

    vector<int> array = readArray(totalNumbers);

    printMaxLengthSubsequence(array);

    return 0;
} 
