#include <iostream>
#include <vector>

#define UNDEFINED -1

using namespace std;


long evaluateNumberOfWaysRec(long totalRows, long totalCols, vector<vector<long>> &definedWays) {

    if (totalRows == 0 || totalCols == 0) {
        definedWays[totalRows][totalCols] = 0;
        return 0;
    }

    if (totalRows == 1 && totalCols == 1) {
        definedWays[totalRows][totalCols] = 1;
        return 1;
    }

    if (definedWays[totalRows-1][totalCols] == UNDEFINED)
        definedWays[totalRows-1][totalCols] = evaluateNumberOfWaysRec(totalRows-1, totalCols, definedWays);

    if (definedWays[totalRows][totalCols-1] == UNDEFINED)
        definedWays[totalRows][totalCols-1] = evaluateNumberOfWaysRec(totalRows, totalCols-1, definedWays);
        
    return definedWays[totalRows-1][totalCols] + definedWays[totalRows][totalCols-1];
}


long evaluateNumberOfWays(long totalRows, long totalCols) {
    vector<vector<long>> definedWays(totalRows + 1, vector<long>(totalCols + 1, UNDEFINED));
    return evaluateNumberOfWaysRec(totalRows, totalCols, definedWays);
}


int main(void) {

    long totalRows, totalCols;
    cin >> totalRows >> totalCols;

    cout << evaluateNumberOfWays(totalRows, totalCols) << "\n";

    return 0;
}
