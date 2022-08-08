#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


vector<int> readVesselsContents(int totalVessels) {

    vector<int> vesselsContents;

    for (int i = 0; i < totalVessels; i++) {
        int content; cin >> content;
        vesselsContents.push_back(content);
    }

    return vesselsContents;
}


bool isValidCapacity(int capacity, vector<int> vesselsContents, int totalConveyors) {

    int conveyorsUsed = 1;
    int conveyorContent = 0;

    for (int vesselContent : vesselsContents) {
        if (conveyorContent + vesselContent <= capacity) {
            conveyorContent += vesselContent;
        }
        else {
            if (vesselContent > capacity)
                return false;
            conveyorsUsed++;
            conveyorContent = vesselContent;
        }
    }

    return conveyorsUsed <= totalConveyors;
}


int findBestConveyorCapacity(vector<int> vesselsContents, int totalConveyors) {

    int lowCapacity = 0;
    int highCapacity = accumulate(vesselsContents.begin(), vesselsContents.end(), 0);
    int midCapacity;

    while (lowCapacity != highCapacity) {
        midCapacity = (lowCapacity + highCapacity) / 2;
        if (isValidCapacity(midCapacity, vesselsContents, totalConveyors)) {
            highCapacity = midCapacity;
        }
        else {
            lowCapacity = midCapacity + 1;
        }
    }

    return lowCapacity;
}


int main(void) {

    int totalVessels = 0, totalConveyors = 0;

    while (cin >> totalVessels) {
        cin >> totalConveyors;
        vector<int> vesselsContents = readVesselsContents(totalVessels);
        cout << findBestConveyorCapacity(vesselsContents, totalConveyors) << "\n";
    }

    return 0;
}
