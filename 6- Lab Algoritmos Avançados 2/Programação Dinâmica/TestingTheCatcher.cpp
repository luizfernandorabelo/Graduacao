#include <iostream>
#include <vector>

#define END -1

using namespace std;

typedef unsigned int uint;


vector<int> readMissilesHeights() {

    vector<int> missilesHeights;
    int height;

    while (true) {
        cin >> height;
        if (height == END) break;
        missilesHeights.push_back(height);
    }

    return missilesHeights;
}


int evaluateMaxNumberOfInterceptions(vector<int> &missilesHeights) {

    vector<int> lengths(missilesHeights.size());
    lengths[0] = 1;

    int ldc = lengths[0];  // longest decreasing subsequence

    for (uint i = 1; i < missilesHeights.size(); i++) {
        lengths[i] = 1;
        for (uint j = 0; j < i; j++) {
            if (missilesHeights[j] >= missilesHeights[i])
                lengths[i] = max(lengths[i], lengths[j] + 1);
        }
        ldc = max(ldc, lengths[i]);
    }

    return ldc;
}


int main(void) {

    int currentTest = 1;

    while (true) {
        vector<int> missilesHeights = readMissilesHeights();
        if (missilesHeights.empty()) break;
        int maxInterceptions = evaluateMaxNumberOfInterceptions(missilesHeights);
        if (currentTest != 1) cout << "\n";
        cout << "Test #" << currentTest++ << ":\n";
        cout << "  maximum possible interceptions: " << maxInterceptions << "\n";
    }

    return 0;
}
