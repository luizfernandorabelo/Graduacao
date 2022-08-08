#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


int* readArray(int arraySize) {

    int* array = new int[arraySize];

    for (int i = 0; i < arraySize; i++)
        cin >> array[i];

    return array;
}


int* buildExpectedArray(int* originalArray, int arraySize) {

    int* expectedArray = new int[arraySize];

    memcpy(expectedArray, originalArray, arraySize * sizeof(int));

    sort(expectedArray, expectedArray + arraySize);

    return expectedArray;
}


int** createTabulation(int dimension) {

    int** tabulation = new int*[dimension];

    for (int i = 0; i < dimension; i++)
        tabulation[i] = new int[dimension];
    
    for (int i = 0; i < dimension; i++) {
        tabulation[i][dimension-1] = dimension - (i + 1);
        tabulation[dimension-1][i] = dimension - (i + 1);
    }
    
    return tabulation;
}


void deleteTabulation(int** tabulation, int dimension) {

    for (int i = 0; i < dimension; i++)
        delete [] tabulation[i];
    
    delete [] tabulation;
}


int evaluateMinimumNumberOfOperations(int* array, int arraySize) {

    int* expected = buildExpectedArray(array, arraySize);
    int** tabulation = createTabulation(arraySize + 1);

    for (int i = arraySize - 1; i >= 0; i--) {
        for (int j = arraySize - 1; j >= 0; j--) {
            if (array[i] == expected[j])
                tabulation[i][j] = tabulation[i+1][j+1];
            else
                tabulation[i][j] = min(tabulation[i+1][j], tabulation[i][j+1]) + 1;
        }
    }
    
    int minimum = tabulation[0][0];

    delete [] expected;
    deleteTabulation(tabulation, arraySize + 1);

    return minimum / 2;
}


int main(void) {

    int arraySize; cin >> arraySize;

    int* array = readArray(arraySize);

    cout << evaluateMinimumNumberOfOperations(array, arraySize) << "\n";

    delete [] array;

    return 0;
}
