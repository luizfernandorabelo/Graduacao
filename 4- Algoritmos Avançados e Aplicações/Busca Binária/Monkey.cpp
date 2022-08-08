#include <iostream>
#include <vector>

using namespace std;


vector<int> readRungsPositions(int totalRungs) {

    vector<int> rungsPositions;

    for (int i = 0; i < totalRungs; i++) {
        int newPosition; cin >> newPosition;
        rungsPositions.push_back(newPosition);
    }

    return rungsPositions;
}


bool isValidStrength(int strength, vector<int> rungsPostions) {

    int currentPosition = 0;

    for (int rungPosition : rungsPostions) {
        int jumpWidth = rungPosition - currentPosition;
        if (jumpWidth > strength)
            return false;
        if (jumpWidth == strength)
            strength--;
        currentPosition = rungPosition;
    }

    return true;
}


int findMinimumStrength(vector<int> rungsPostions) {

    int lowStrength = 0;
    int highStrength = *(rungsPostions.end() - 1);
    int middleStrength;
    
    while (lowStrength != highStrength) {
        middleStrength = (lowStrength + highStrength) / 2;
        if (isValidStrength(middleStrength, rungsPostions)) {
            highStrength = middleStrength;
        }
        else {
            lowStrength = middleStrength + 1;
        }
    }

    return lowStrength; 
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalRungs; cin >> totalRungs;
        vector<int> rungsPositions = readRungsPositions(totalRungs);
        int strength = findMinimumStrength(rungsPositions);
        cout << "Case " << i+1 << ": " << strength << "\n";
    }

    return 0;
}