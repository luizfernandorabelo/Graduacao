/*

  * General idea:

    - Let's assume F1, F2, S1 and S2 as the traversal times of
      the fastest person, the second fastest person, the slowest
      person and the second slowest person, respectively, and
      consider the prefix 'P' for the person who owns the time
      of the suffix (e.g. PF1 is the fastest person...);

    - For the crosses there are a few possibilities:
      - (1) Cross with PF1 and PF2 if they are the only ones remaining (trivial case);
      - (2) Cross with PF1 and PS2, cross back with PF1 and continue at (1), if there are 3 people remaining (leads to trivial case)
      - (3) Cross with PF1 and PS1, cross back with PF1
      - (4) Cross with PF1 and PF2, cross back with PF1, cross with PS1 and PS2, cross back with PF2

    - The (3) and (4) cases are the most important, and the time spent differ according to the input, that is:
      - CASE 4: when F1 and F2 are way smaller than S1 and S2, it is better to cross PS1 and PS2 together, since
          there won't be a lot of time wasted with a cross back, which can be performed quickly by PF1 and PF2;
      - CASE 3: otherwise, there is not need to cross PF1 and PF2 just to ensure a quick cross back, since the
          PF1, PF2, PS1 and PS2 are not that different. Therefore it compensates to cross PS1 and PF1 and cross back with PF1
    
    - To build an optimal greedy solution, we can think about the ratio TOTAL_TIME_CROSSED / TOTAL_TRANSPORTATION_TIME, where TOTAL_TIME_CROSSED
      is the sum of the times tha has been transported and don't need come back, and the TOTAL_TRANSPORTATION_TIME is the total time to
      perform the cross, including the crosses back:
      - (3) ratio = S1 / (S1 + F1)
      - (4) ratio = (S1 + S2) / (F2 + F1 + S1 + F2)
    
    - Besides the trivial cases, if (3) ratio is greater than (4) ratio, (3) is the best choice. Otherwise, (4) is the best choice.

*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


typedef struct {

    string track = "";
    uint totalTime = 0;
    vector<uint> peopleTimes;
    bool timesSorted = false;

    void sortPeopleTimes() {
        if (!timesSorted)
            sort(peopleTimes.begin(), peopleTimes.end());
        timesSorted = true;
    }

    pair<uint,uint> getFastestTimes() {
        sortPeopleTimes();
        return { peopleTimes[0], peopleTimes[1] };
    }

    pair<uint,uint> getSlowestTimes() {
        sortPeopleTimes();
        uint size = peopleTimes.size();
        return { peopleTimes[size - 1], peopleTimes[size - 2] };
    }

    void cross(uint fastestTime, uint slowestTime) {
        track += (to_string(fastestTime) + " " + to_string(slowestTime) + "\n");
        totalTime += slowestTime;
    }

    void crossBack(uint time) {
        track += (to_string(time) + "\n");
        totalTime += time;
    }

    void popTimes(int amount) {
        for (int i = 0; i < amount; i++)
            peopleTimes.pop_back();
    }

} Traversal;


vector<uint> readPeopleTimes(uint totalPeople) {
    vector<uint> times;
    for (uint i = 0; i < totalPeople; i++) {
        int currentTime; cin >> currentTime;
        times.push_back(currentTime);
    }
    return times;
}


void buildTraversalFastestTrackRec(Traversal *traversal) {

    pair<uint,uint> fastestPair = traversal->getFastestTimes();
    pair<uint,uint> slowestPair = traversal->getSlowestTimes();

    if (traversal->peopleTimes.size() == 2) {
        traversal->cross(fastestPair.first, fastestPair.second);
        return;
    }

    if (traversal->peopleTimes.size() == 3) {
        traversal->cross(fastestPair.first, slowestPair.first);
        traversal->crossBack(fastestPair.first);
        traversal->cross(fastestPair.first, fastestPair.second);
        return;
    }

    uint f1 = fastestPair.first, f2 = fastestPair.second;
    uint s1 = slowestPair.first, s2 = slowestPair.second;

    double ratio3 = (double) s1 / (s1 + f1);
    double ratio4 = (double) (s1 + s2) / (f2 + f1 + s1 + f2);

    if (ratio3 > ratio4) {
        traversal->cross(fastestPair.first, slowestPair.first);
        traversal->crossBack(fastestPair.first);
        traversal->popTimes(1);
    } else {
        traversal->cross(fastestPair.first, fastestPair.second);
        traversal->crossBack(fastestPair.first);
        traversal->cross(slowestPair.second, slowestPair.first);
        traversal->crossBack(fastestPair.second);
        traversal->popTimes(2);
    }

    buildTraversalFastestTrackRec(traversal);
}


void buildTraversalFastestTrack(Traversal *traversal) {

    if (traversal->peopleTimes.size() == 1) {
        uint onlyTime = traversal->peopleTimes[0];
        traversal->track = to_string(onlyTime) + "\n";
        traversal->totalTime = onlyTime;
        return;
    }

    buildTraversalFastestTrackRec(traversal);
}


Traversal *performTraversal(uint totalPeople) {

    Traversal *traversal = new Traversal;
    traversal->peopleTimes = readPeopleTimes(totalPeople);

    buildTraversalFastestTrack(traversal);

    return traversal;
}


int main(void) {

    int totalTests = 0;
    cin >> totalTests;
    getchar();

    for (int i = 0; i < totalTests; i++) {
        int totalPeople = 0;
        cin >> totalPeople;
        Traversal *traversal = performTraversal(totalPeople);
        cout << traversal->totalTime << "\n" << traversal->track << "\n";
        getchar();
    }

    return 0;
}
