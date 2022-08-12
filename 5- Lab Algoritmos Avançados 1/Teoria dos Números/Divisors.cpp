#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


vector<int> findAscendedDivisors(int number) {

    vector<int> divisors, ascended, descended;
    int limit = sqrt(number) + 1;

    divisors.push_back(1);

    for (int i = 2; i < limit; i++) {
        if (number % i == 0) {
            ascended.push_back(i);
            if (number / i != i)
                descended.push_back(number / i);
        }
    }

    for (uint i = 0; i < ascended.size(); i++)
        divisors.push_back(ascended[i]);

    for (int i = descended.size() - 1; i >= 0; i--)
        divisors.push_back(descended[i]);

    divisors.push_back(number);

    return divisors;
}


void printDivisors(vector<int> &divisors) {

    for (uint i = 0; i < divisors.size() - 1; i++)
        cout << divisors[i] << " ";

    cout << divisors[divisors.size()-1] << "\n";
}


int main(void) {

    int number;
    cin >> number;

    vector<int> divisors = findAscendedDivisors(number);

    printDivisors(divisors);

    return 0;
}
