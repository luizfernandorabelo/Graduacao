#include <iostream>
#include <cstring>
#include <vector>

#define OLLIE 0
#define STAN 1

using namespace std;


vector<int> readRemovalPossibilities(int totalPossibilities) {

    vector<int> removalPossibilities;

    for (int i = 0; i < totalPossibilities; i++) {
        int newPossibility; cin >> newPossibility;
        removalPossibilities.push_back(newPossibility);
    }

    return removalPossibilities;
}



int predictWinner(int totalStones, vector<int> &possibilities) {

    int* winners = (int*) calloc(totalStones + 1, sizeof(int));

    for (int currentStone = 1; currentStone <= totalStones; currentStone++) {
        for (int removal : possibilities) {
            if (currentStone == removal) {
                winners[currentStone] = STAN;
            }
            else if (currentStone - removal > 0) {
                if (winners[currentStone - removal] == OLLIE) {
                    winners[currentStone] = STAN;
                }
            }
        }
    }

    int winner = winners[totalStones];

    free(winners);

    return winner;
}


int main(void) {

    int totalStones, totalPossibilities;

    while (cin >> totalStones) {
        cin >> totalPossibilities;
        vector<int> possibilities = readRemovalPossibilities(totalPossibilities);
        int winner = predictWinner(totalStones, possibilities);
        if (winner == OLLIE)
            cout << "Ollie wins\n";
        else 
            cout << "Stan wins\n";
    }
    
    return 0;
}