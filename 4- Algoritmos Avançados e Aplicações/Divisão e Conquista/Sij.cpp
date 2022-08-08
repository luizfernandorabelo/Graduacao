#include <iostream>
#include <vector>
#include <set>

using namespace std;


int findGreatestValue(vector<int> &elements, set<pair<int,int>> &elementsIndexes, int startIdx, int endIdx) {

    if (startIdx <= endIdx) {

        pair<int,int> setBegin = *elementsIndexes.begin();
        int minValue = setBegin.first;
        int minValueIdx = setBegin.second;
        elementsIndexes.erase(setBegin);

        int v1 = minValue * (endIdx - startIdx + 1);

        set<pair<int,int>> elementsIndexes2;
        for (int i = startIdx; i < minValueIdx; i++) {
            pair<int,int> insertedPair = make_pair(elements[i], i);
            elementsIndexes.erase(insertedPair);
            elementsIndexes2.insert(insertedPair);
        }

        int v2 = findGreatestValue(elements, elementsIndexes2, startIdx, minValueIdx-1);
        int v3 = findGreatestValue(elements, elementsIndexes, minValueIdx+1, endIdx);

        return max(v1, max(v2, v3));
    }

    return 0;
}


int main(void) {

    int totalElements;
    cin >> totalElements;

    vector<int> elements;
    set<pair<int,int>> elementsIndexes;

    for (int i = 0; i < totalElements; i++) {
        int newElement; cin >> newElement;
        elements.push_back(newElement);
        elementsIndexes.insert(make_pair(newElement, i));
    }

    cout << findGreatestValue(elements, elementsIndexes, 0, totalElements - 1) << "\n";

    return 0;
}