#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> min_heap;


min_heap readIntegers(int totalIntegers) {

    min_heap integers;

    for (int i = 0; i < totalIntegers; i++) {
        int newInteger; cin >> newInteger;
        integers.push(newInteger);
    }

    return integers;
}


int evaluateMinimumSumCost(min_heap integers, int totalIntegers) {

    if (totalIntegers == 1)
        return integers.top();
    
    int remainingParcels = integers.size();
    int totalCost = 0;

    while (remainingParcels > 0) {
        if (remainingParcels == 1) {
            totalCost += integers.top();
            integers.pop();
        } else {
            int frontElement = integers.top();
            integers.pop();
            int secondElement = integers.top();
            integers.pop();
            totalCost += frontElement + secondElement;
            if (remainingParcels > 2)
                integers.push(frontElement + secondElement);
        }
        remainingParcels = integers.size();
    }

    return totalCost;
}


int main(void) {

    int totalIntegers;
    cin >> totalIntegers;

    while (totalIntegers > 0) {
        min_heap integers = readIntegers(totalIntegers);
        cout << evaluateMinimumSumCost(integers, totalIntegers) << "\n";
        cin >> totalIntegers;
    }

    return 0;
}
