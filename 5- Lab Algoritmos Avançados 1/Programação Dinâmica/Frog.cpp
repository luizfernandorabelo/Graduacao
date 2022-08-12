#include <iostream>
#include <vector>

using namespace std;


vector<int> readStoneHeights(int totalStones) {

    vector<int> stoneHeights;

    for (int i = 0; i < totalStones; i++) {
        int stoneHeight; cin >> stoneHeight;
        stoneHeights.push_back(stoneHeight);
    }

    return stoneHeights;
}


int evaluateJumpCost(vector<int> &stoneHeights, int origin, int target) {
    return abs(stoneHeights[origin] - stoneHeights[target]);
}


int evaluateMinimumCostToCross(vector<int> &stoneHeights, int totalStones) {

    if (totalStones <= 1)
        return 0;

    vector<int> costs(totalStones, 0);
    costs[0] = 0, costs[1] = evaluateJumpCost(stoneHeights, 0, 1);

    for (int i = 2; i < totalStones; i++) {
        int jumpCost1, jumpCost2;
        jumpCost1 = evaluateJumpCost(stoneHeights, i - 1, i);
        jumpCost2 = evaluateJumpCost(stoneHeights, i - 2, i);
        costs[i] = min(jumpCost1 + costs[i-1], jumpCost2 + costs[i-2]);
    }

    return costs[totalStones - 1];
}


int main(void) {

    int totalStones;
    cin >> totalStones;

    vector<int> stoneHeights = readStoneHeights(totalStones);

    cout << evaluateMinimumCostToCross(stoneHeights, totalStones) << "\n";

    return 0;
}
