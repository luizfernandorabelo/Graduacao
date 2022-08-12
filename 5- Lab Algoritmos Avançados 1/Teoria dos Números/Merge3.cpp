#include <iostream>
#include <vector>

using namespace std;


vector<int> readIntegers(int totalIntegers) {

    vector<int> integers;

    for (int i = 0; i < totalIntegers; i++) {
        int newInteger; cin >> newInteger;
        integers.push_back(newInteger);
    }

    return integers;
}


int evaluateMaxDivisibleByThree(vector<int> integers) {

    int remainders[] = { 0, 0, 0 };  // total integers with remainder 0, 1 and 2, respectively

    for (int integer : integers)
        remainders[integer % 3]++;

    /*
        The total amount of integers divisible by 3
        will be represented at 'remainders[0]'. Now,
        our job is to manage the merges.
    */

    int totalMerges = min(remainders[1], remainders[2]);  // the min of them is the max number of merges

    /*
        Since we've evaluated the number of merges,
        we have to discount the remainders
    */

    remainders[1] -= totalMerges;
    remainders[2] -= totalMerges;

    return remainders[0]         // total divisible by 3
           + totalMerges         // maximum possible merges to divide by 3
           + remainders[1] / 3   // for each three 1's => 1 three multiple
           + remainders[2] / 3;  // for each three 2's => 1 three multiple
}


int main(void) {

    int totalQueries; cin >> totalQueries;

    for (int i = 0; i < totalQueries; i++) {
        int totalIntegers; cin >> totalIntegers;
        vector<int> integers = readIntegers(totalIntegers);
        cout << evaluateMaxDivisibleByThree(integers) << "\n";
    }

    return 0;
}
