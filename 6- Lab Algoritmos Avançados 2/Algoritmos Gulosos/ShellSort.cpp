#include <iostream>
#include <vector>

using namespace std;


vector<string> readTurtles(int totalTurtles) {

    vector<string> turtles;

    for (int i = 0; i < totalTurtles; i++) {
        string name = "";
        while (!name.length()) {
            getline(cin, name);
        }
        turtles.push_back(name);
    }

    return turtles;
}


void printLeavingOrder(const vector<string> &finalTurtles, const vector<string> &actualTurtles) {

    int firstMismatchIdx = finalTurtles.size() - 1;

    for (int i = firstMismatchIdx; i >= 0; i--) {
        if (finalTurtles[i] == actualTurtles[firstMismatchIdx])
            firstMismatchIdx--;
    }

    for (int i = firstMismatchIdx; i >= 0; i--) {
        cout << actualTurtles[i] << "\n";
    }

    cout << "\n";
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalTurtles; cin >> totalTurtles;
        vector<string> finalTurtles = readTurtles(totalTurtles);
        vector<string> actualTurtles = readTurtles(totalTurtles);
        printLeavingOrder(finalTurtles, actualTurtles);
    }

    return 0;
}
