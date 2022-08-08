#include <iostream>
#include <cstring>
#include <vector>

#define NULL_VALUE -1

using namespace std;


vector<int> readAvailableCoins(int totalCoins) {

    vector<int> coins;

    for (int i = 0; i < totalCoins; i++) {
        int coin; cin >> coin;
        coins.push_back(coin);
    }

    return coins;
}


int evaluateMinimumNumberOfCoins(vector<int> &availableCoins, int coinsSum) {

    int* tabulation = new int[coinsSum+1];
    int minimum = INT32_MAX -1;

    tabulation[0] = 0;

    for (int currentSum = 1; currentSum <= coinsSum; currentSum++) {
        minimum = INT32_MAX - 1;
        for (int coin : availableCoins) {
            if (currentSum - coin >= 0)
                minimum = min(minimum, tabulation[currentSum - coin] + 1);
        }
        tabulation[currentSum] = minimum;
    }
    
    delete [] tabulation;

    return minimum;
}


int main(void) {

    int coinsSum, totalCoins; 

    cin >> coinsSum >> totalCoins;

    vector<int> availableCoins = readAvailableCoins(totalCoins);

    cout << evaluateMinimumNumberOfCoins(availableCoins, coinsSum) << "\n";

    return 0;
}
