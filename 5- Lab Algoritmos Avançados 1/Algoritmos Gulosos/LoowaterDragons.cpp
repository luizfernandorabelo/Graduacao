#include <iostream>
#include <vector>
#include <algorithm>

#define IMPOSSIBLE -1

using namespace std;


vector<int> readVector(int vectorSize) {

    vector<int> v;

    for (int i = 0; i < vectorSize; i++) {
        int newElement; cin >> newElement;
        v.push_back(newElement);
    }

    return v;
}


int evaluateMinimumNumberOfGoldCoinsSpent(vector<int> &heads, vector<int> &knights) {

    sort(heads.begin(), heads.end());
    sort(knights.begin(), knights.end());

    uint headsRemaining = heads.size();
    uint goldCoinsSpent = 0, i = 0, j = 0;

    while (i < heads.size() && j < knights.size()) {
        int currentHead = heads[i];
        int currentKnight = knights[j];
        if (currentKnight >= currentHead) {
            headsRemaining--;
            goldCoinsSpent += currentKnight;
            i++;
            j++;
        } else {
            j++;
        }
    }

    return headsRemaining == 0 ? goldCoinsSpent : IMPOSSIBLE;
}


int main(void) {

    int totalHeads, totalKnights;
    cin >> totalHeads >> totalKnights;

    while (totalHeads > 0 && totalKnights > 0) {
        vector<int> heads = readVector(totalHeads);
        vector<int> knights = readVector(totalKnights);
        int minCoins = evaluateMinimumNumberOfGoldCoinsSpent(heads, knights);
        if (minCoins != IMPOSSIBLE)
            cout << minCoins << "\n";
        else
            cout << "Loowater is doomed!\n";
        cin >> totalHeads >> totalKnights;
    }

    return 0;
}
