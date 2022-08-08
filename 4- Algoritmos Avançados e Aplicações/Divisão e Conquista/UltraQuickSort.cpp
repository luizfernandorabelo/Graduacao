#include <iostream>

#define MAX_SIZE 500000

using namespace std;

typedef long long int llint;


void readArray(llint array[], int realSize) {
    for (int i = 0; i < realSize; i++)
        cin >> array[i];
}


llint merge(llint array[], int startIdx, int middleIdx, int endIdx) {

    int i = startIdx, j = middleIdx + 1, k = 0;
    llint sortedArray[endIdx-startIdx+1];
    llint swaps = 0;

    while (i <= middleIdx && j <= endIdx) {
        if (array[i] < array[j]) {
            sortedArray[k++] = array[i++];
        }
        else {
            sortedArray[k++] = array[j++];
            swaps += (middleIdx - i + 1);
        }
    }

    while (i <= middleIdx)
        sortedArray[k++] = array[i++];

    while (j <= endIdx)
        sortedArray[k++] = array[j++];
    
    for (int l = 0; l < endIdx - startIdx + 1; l++)
        array[startIdx+l] = sortedArray[l];
    
    return swaps;
}


llint countSwapOperations(llint array[], int startIdx, int endIdx) {

    if (startIdx >= endIdx)
        return 0;

    int middleIdx = (endIdx + startIdx) / 2;

    llint leftSwaps = countSwapOperations(array, startIdx, middleIdx);
    llint rightSwaps = countSwapOperations(array, middleIdx + 1, endIdx);
    llint mergeSwaps = merge(array, startIdx, middleIdx, endIdx);

    return leftSwaps + rightSwaps + mergeSwaps;
}


int main(void) {

    llint array[MAX_SIZE];

    int realSize; cin >> realSize;

    while (realSize != 0) {
        readArray(array, realSize);
        cout << countSwapOperations(array, 0, realSize-1) << "\n";
        cin >> realSize;
    }

    return 0;
}