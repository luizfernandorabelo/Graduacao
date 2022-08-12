#include <iostream>

using namespace std;


long evaluateCompleteRowsAmount(int coinAmount) {

    long lowerBound = 0, upperBound = coinAmount;
    long completeRows, coinsTaken;

    while (lowerBound <= upperBound) {
        completeRows = lowerBound + (upperBound - lowerBound) / 2;
        coinsTaken = (1 + completeRows) * completeRows / 2;
        if (coinsTaken < coinAmount)
            lowerBound = completeRows + 1;
        else if (coinsTaken > coinAmount)
            upperBound = completeRows - 1;
        else
            return completeRows;
    }

    return upperBound;
}


int main(void) {

    long coinsAmount;
    cin >> coinsAmount;

    cout << evaluateCompleteRowsAmount(coinsAmount) << "\n";

    return 0;
}
