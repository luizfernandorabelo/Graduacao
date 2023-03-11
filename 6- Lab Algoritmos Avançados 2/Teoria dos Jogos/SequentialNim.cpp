#include <iostream>
#include <vector>

using namespace std;


vector<int> readStonePiles(int totalPiles) {

    vector<int> v(totalPiles);

    for (int i = 0; i < totalPiles; i++)
        cin >> v[i];

    return v;
}


string evaluateWinner(vector<int> &piles) {

    string players[] = {"First", "Second"};

    int winnerIndex = 1, i = 0;

    while (i < (int) piles.size() && piles[i] == 1) {
        i++;
        winnerIndex = !winnerIndex;
    }

    if (i < (int) piles.size())
        winnerIndex = !winnerIndex;

    return players[winnerIndex];
}


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalPiles;
        cin >> totalPiles;
        vector<int> piles = readStonePiles(totalPiles);
        cout << evaluateWinner(piles) << "\n";
    }

    return 0;
}
