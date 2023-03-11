#include <iostream>

using namespace std;

typedef long long int llint;


void readArray(llint array[], int realSize) {
    for (int i = 0; i < realSize; i++)
        cin >> array[i];
}


llint countIntersections(llint array[], int startIdx, int middleIdx, int endIdx) {

    int i = startIdx, j = middleIdx + 1, k = 0;
    llint sortedArray[endIdx-startIdx+1];
    llint intersections = 0;

    while (i <= middleIdx && j <= endIdx) {
        if (array[i] < array[j]) {
            sortedArray[k++] = array[i++];
        }
        else {
            sortedArray[k++] = array[j++];
            intersections += (middleIdx - i + 1);
        }
    }

    while (i <= middleIdx)
        sortedArray[k++] = array[i++];

    while (j <= endIdx)
        sortedArray[k++] = array[j++];
    
    for (int l = 0; l < endIdx - startIdx + 1; l++)
        array[startIdx+l] = sortedArray[l];
    
    return intersections;
}


llint countIntersectionOperations(llint array[], int startIdx, int endIdx) {

    if (startIdx >= endIdx)
        return 0;

    int middleIdx = (endIdx + startIdx) / 2;

    llint leftIntersections = countIntersectionOperations(array, startIdx, middleIdx);
    llint rightIntersections = countIntersectionOperations(array, middleIdx + 1, endIdx);
    llint mergeIntersections = countIntersections(array, startIdx, middleIdx, endIdx);

    return leftIntersections + rightIntersections + mergeIntersections;
}


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int length; cin >> length;
        llint *array = new llint[length];
        readArray(array, length);
        cout << countIntersectionOperations(array, 0, length - 1) << "\n";
    }

    return 0;
}
