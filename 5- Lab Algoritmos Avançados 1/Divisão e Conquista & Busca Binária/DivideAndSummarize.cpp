// TODO: review time complexity (since we can have a great number of queries, we can store the all possible answers in a set and then, perform each query in the stored set)

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef pair<vector<int>, vector<int>> SlicedArray;


vector<int> readArray(int totalElements) {

    vector<int> array;

    for (int i = 0; i < totalElements; i++) {
        int newElement; cin >> newElement;
        array.push_back(newElement);
    }

    return array;
}


SlicedArray sliceArray(vector<int> &array, int mid) {

    vector<int> smallerValues, greaterValues;

    for (int value : array) {
        if (value <= mid)
            smallerValues.push_back(value);
        else
            greaterValues.push_back(value);
    }

    return { smallerValues, greaterValues };
}


bool isArrayPretty(vector<int> array, int prettinessFactor) {

    if (array.size() == 0)
        return false;

    if (array.size() == 1)
        return array[0] == prettinessFactor;

    int max = *max_element(array.begin(), array.end());
    int min = *min_element(array.begin(), array.end());
    int mid = (max + min) / 2;

    SlicedArray sliced = sliceArray(array, mid);

    int minorSum = accumulate(sliced.first.begin(), sliced.first.end(), 0);
    int majorSum = accumulate(sliced.second.begin(), sliced.second.end(), 0);

    if (minorSum + majorSum == prettinessFactor || minorSum == prettinessFactor || majorSum == prettinessFactor)
        return true;

    if (sliced.first.size() == array.size() || sliced.second.size() == array.size())
        return false;

    if (prettinessFactor <= mid)
        return isArrayPretty(sliced.first, prettinessFactor);

    return isArrayPretty(sliced.first, prettinessFactor) || isArrayPretty(sliced.second, prettinessFactor);
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalElements, totalChecks;
        cin >> totalElements >> totalChecks;
        vector<int> array = readArray(totalElements);
        for (int j = 0; j < totalChecks; j++) {
            int prettinessFactor; cin >> prettinessFactor;
            if (isArrayPretty(array, prettinessFactor))
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }

    return 0;
}
