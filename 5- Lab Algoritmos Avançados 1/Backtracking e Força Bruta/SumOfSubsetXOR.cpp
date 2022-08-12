#include <iostream>
#include <vector>

using namespace std;


vector<int> readElements(int totalElements) {

    vector<int> elements;

    for (int i = 0; i < totalElements; i++) {
        int newElement; cin >> newElement;
        elements.push_back(newElement);
    }

    return elements;
}


int evaluateXorTotalRec(vector<int> &elements, vector<int> &currentPermutation) {

    int permutationResult = 0;

    if (currentPermutation.size() == elements.size()) {
        for (uint i = 0; i < currentPermutation.size(); i++)
            permutationResult ^= currentPermutation[i];
    }
    else {
        currentPermutation.push_back(elements[currentPermutation.size()]);
        permutationResult += evaluateXorTotalRec(elements, currentPermutation);
        currentPermutation.pop_back();
        currentPermutation.push_back(0);
        permutationResult += evaluateXorTotalRec(elements, currentPermutation);
        currentPermutation.pop_back();
    }

    return permutationResult;
}


int evaluateXorTotal(vector<int> &elements) {

    vector<int> startPermutation;

    return evaluateXorTotalRec(elements, startPermutation);
}


int main(void) {

    int totalElements;
    cin >> totalElements;

    vector<int> elements = readElements(totalElements);

    cout << evaluateXorTotal(elements) << "\n";

    return 0;
}
