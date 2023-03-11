#include <cmath>
#include <vector>
#include <iostream>  
#include <algorithm>

#define IMPOSSIBLE -1

using namespace std;

typedef pair<double,double> Sprinkler;


Sprinkler makeSprinkler(int center, int radius, double widthFactor) {
    double maxRange = sqrt((double) radius * radius - widthFactor);
    return make_pair(center - maxRange, center + maxRange);
}


vector<Sprinkler> readSprinklers(int totalSprinklers, int grassWidth) {

    vector<Sprinkler> sprinklers;
    double widthFactor = (double) grassWidth * grassWidth / 4.0;

    for (int i = 0; i < totalSprinklers; i++) {
        int center, radius;
        cin >> center >> radius;
        if (2 * radius > grassWidth) {
            Sprinkler newSprinkler = makeSprinkler(center, radius, widthFactor);
            sprinklers.push_back(newSprinkler);
        }
    }

    return sprinklers;
}

 
int evaluateMinNumberOfSprinklers(vector<Sprinkler> &sprinklers, int grassLength) {

    sort(sprinklers.begin(), sprinklers.end());

    int minSprinklers = 0;
    double rightMostX = 0;
    bool solved = false;

    for (uint i = 0, j; i < sprinklers.size() && !solved; i = j) {
        if (sprinklers[i].first > rightMostX)
            return IMPOSSIBLE;
        for (j = i + 1; j < sprinklers.size() && sprinklers[j].first <= rightMostX; j++) {
            if (sprinklers[j].second > sprinklers[i].second)
                i = j;
        }
        minSprinklers++;
        rightMostX = sprinklers[i].second;
        solved = rightMostX >= grassLength;
    }

    return solved ? minSprinklers : IMPOSSIBLE;
}


int main() {

    int totalSprinklers, grassLength, grassWidth;

    while (cin >> totalSprinklers >> grassLength >> grassWidth) {
        vector<Sprinkler> sprinklers = readSprinklers(totalSprinklers, grassWidth);
        cout << evaluateMinNumberOfSprinklers(sprinklers, grassLength) << "\n";
    }

    return 0;
}
