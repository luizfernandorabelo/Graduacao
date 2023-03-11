#include <iostream>
#include <vector>
#include <map>

using namespace std;


typedef unsigned int uint;
typedef long long int llint;


vector<int> readSequence(int totalNumbers) {

    vector<int> sequence;

    for (int i = 0; i < totalNumbers; i++) {
        int number; cin >> number;
        sequence.push_back(number);
    }

    return sequence;
}


map<llint,llint> buildTermsCount(const vector<int> &sequence) {

    map<llint,llint> m;

    for (uint i = 0; i < sequence.size(); i++)
        m[sequence[i]] += 1;

    return m;
}


llint evaluateNumberOfGPs(const vector<int> &sequence, int ratio) {

    llint totalGPs = 0;

    map<llint,llint> rightTermsCount = buildTermsCount(sequence);
    map<llint,llint> leftTermsCount;

    for (llint term : sequence) {
        rightTermsCount[term] -= 1;
        if (term % ratio == 0)
            totalGPs += leftTermsCount[term / ratio] * rightTermsCount[term * ratio];
        leftTermsCount[term]++;
    }

    return totalGPs;
}


int main(void) {

    int totalNumbers, ratio;
    cin >> totalNumbers >> ratio;

    vector<int> sequence = readSequence(totalNumbers);

    cout << evaluateNumberOfGPs(sequence, ratio) << "\n";

    return 0;
}
