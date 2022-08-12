#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

using namespace std;


vector<int> readSnowflakes(int totalSnowflakes) {

    vector<int> snowflakes;

    for (int i = 0; i < totalSnowflakes; i++) {
        int newSnowflake; cin >> newSnowflake;
        snowflakes.push_back(newSnowflake);
    }

    return snowflakes;
}


int evaluateMaxSnowflakesPackageSize(vector<int> snowFlakes, int totalSnowflakes) {

    set<int> serializedSnowflakes;
    int currentSize = 0, previousSize = 0;
    priority_queue<int> createdSizes;
    unordered_map<int,int> flakesToIndexes;

    for (int i = 0; i < totalSnowflakes; i++) {
        previousSize = serializedSnowflakes.size();
        serializedSnowflakes.insert(snowFlakes[i]);
        currentSize = serializedSnowflakes.size();
        if (currentSize != previousSize) {
            flakesToIndexes[snowFlakes[i]] = i;
        } else {
            createdSizes.push(currentSize);
            serializedSnowflakes.clear();
            i = flakesToIndexes[snowFlakes[i]];
        }
    }

    createdSizes.push(currentSize);

    return createdSizes.top();
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalSnowflakes; cin >> totalSnowflakes;
        vector<int> snowFlakes = readSnowflakes(totalSnowflakes);
        cout << evaluateMaxSnowflakesPackageSize(snowFlakes, totalSnowflakes) << "\n";
    }

    return 0;
}
