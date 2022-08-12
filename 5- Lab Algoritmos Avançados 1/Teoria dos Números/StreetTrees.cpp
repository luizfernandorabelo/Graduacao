#include <iostream>
#include <vector>

#define INFINITY 1000000001

using namespace std;


int gcd(int a, int b) {

    while (a > 0 && b > 0) {
        if (a >= b)
            a %= b;
        else
            b %= a;
    }

    return max(a, b);
}


vector<int> readTreesCoordinates(int totalTrees) {

    vector<int> treesCoordinates;

    for (int i = 0; i < totalTrees; i++) {
        int newCoordinate; cin >> newCoordinate;
        treesCoordinates.push_back(newCoordinate);
    }

    return treesCoordinates;
}


pair<int,int> evaluateMinMaxTreeDistance(const vector<int> &treesCoordinates, int totalTrees) {

    int minimalDistance = INFINITY, maximalDistance = -1;

    for (int i = 1; i < totalTrees; i++) {
        minimalDistance = min(minimalDistance, treesCoordinates[i] - treesCoordinates[i-1]);
        maximalDistance = max(maximalDistance, treesCoordinates[i] - treesCoordinates[i-1]);
    }

    return { minimalDistance, maximalDistance };
}


void plantMissingTrees(vector<int> &treesCoordinates, int alreadyPlanted) {

    if (treesCoordinates.size() == 0)
        return;

    pair<int,int> minMaxDistances = evaluateMinMaxTreeDistance(treesCoordinates, alreadyPlanted);

    int idealDistance = gcd(minMaxDistances.first, minMaxDistances.second);
    cout << idealDistance << "\n";

    int i = 1, currentDistance = treesCoordinates[0] + idealDistance;
    
    while (i < alreadyPlanted) {
        if (treesCoordinates[i] != currentDistance)
            treesCoordinates.push_back(currentDistance);
        else
            i++;
        currentDistance += idealDistance;
    }
}


int main(void) {

    int alreadyPlanted;
    cin >> alreadyPlanted;

    vector<int> treesCoordinates = readTreesCoordinates(alreadyPlanted);

    plantMissingTrees(treesCoordinates, alreadyPlanted);

    cout << treesCoordinates.size() - alreadyPlanted << "\n";

    return 0;
}
