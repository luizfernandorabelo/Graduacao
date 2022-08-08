#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> evaluateDigits(int number) {

    vector<int> digits;

    if (number <= 9) {
        digits.push_back(number);
        return digits;
    }

    for (int divisor = 9; divisor > 1; divisor--) {
        while (number % divisor == 0) {
            digits.push_back(divisor);
            number /= divisor;
        }
    }

    if (number > 1) {
        vector<int> impossible;
        impossible.push_back(-1); 
        return impossible;
    }

    reverse(digits.begin(), digits.end()); 

    return digits;
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int number; cin >> number;
        vector<int> digits = evaluateDigits(number);
        for (int digit : digits)
            cout << digit;
        cout << "\n";
    }

    return 0;
}
