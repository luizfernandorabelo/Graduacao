#include <iostream>
#include <cstring>

using namespace std;


int* buildTimes(int totalTime, int bTime1, int bTime2) {

    int* times = new int[totalTime+1];
    memset(times, 0, (totalTime+1) * sizeof(int));

    int currentTime = 0;

    while (currentTime < bTime1 && currentTime < bTime2)
        currentTime++;

    while (currentTime <= totalTime) {
        if (currentTime == bTime1 || currentTime == bTime2) {
            times[currentTime] = 1;
        }
        int prevTime1 = (currentTime - bTime1 >= 0) ? times[currentTime-bTime1] : 0;
        int prevTime2 = (currentTime - bTime2 >= 0) ? times[currentTime-bTime2] : 0;
        if (prevTime1 != 0 || prevTime2 != 0) {
            int maxPrev = max(prevTime1 + 1, prevTime2 + 1);
            times[currentTime] = max(times[currentTime], maxPrev);
        }
        currentTime++;
    }
    
    return times;
}


void printMaximumNumberOfBurgers(int* times, int totalTime) {

    while (totalTime >= 0) {
        if (times[totalTime] != 0 || totalTime == 0)
            break;
        totalTime--;
    }

    cout << times[totalTime];
}


void printMinimumNumberOfBeers(int* times, int totalTime) {

    int numberOfBeers = 0;
    int currIdx = totalTime;

    while (currIdx > 0 && times[currIdx] == 0) {
        numberOfBeers++;
        currIdx--;
    }

    if (currIdx == 0)
        cout << totalTime;
    else if (numberOfBeers > 0)
        cout << numberOfBeers;
}


int main(void) {

    int totalTime, burgerTime1, burgerTime2;

    while (cin >> burgerTime1) {
        cin >> burgerTime2 >> totalTime;
        int* times = buildTimes(totalTime, burgerTime1, burgerTime2);
        printMaximumNumberOfBurgers(times, totalTime);
        cout << " ";
        printMinimumNumberOfBeers(times, totalTime);
        cout << "\n";
        delete times;
    }

    return 0;
}