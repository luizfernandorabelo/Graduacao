#include <iostream>

using namespace std;


int* readArray(int arraySize) {

    int* array = new int[arraySize];

    for (int i = 0; i < arraySize; i++)
        cin >> array[i];

    return array;
}


int evaluateLongestIncreasingSubsequenceLength(int* array, int arraySize) {

    int* lengths = new int[arraySize];
    lengths[0] = 1;

    int lis = lengths[0];

    for (int i = 1; i < arraySize; i++) {
        int currLength = 1;
        for (int j = 0; j < i; j++) {
            if (array[j] < array[i])
                currLength = lengths[j] + 1 > currLength ? lengths[j] + 1 : currLength;
        }
        lengths[i] = currLength;
        lis = currLength > lis ? currLength : lis;
    }

    delete [] lengths;

    return lis;
}


int main(void) {

    int arraySize = 0;
    cin >> arraySize;

    int* array = readArray(arraySize);

    cout << evaluateLongestIncreasingSubsequenceLength(array, arraySize) << "\n";

    delete [] array;

    return 0;
}
