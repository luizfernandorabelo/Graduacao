#include <iostream>
#include <vector>

using namespace std;


struct ActivityHappiness {
    int a;  // swim in the sea
    int b;  // catch bugs
    int c;  // do homework
};


vector<ActivityHappiness*> readActivityHappinessVector(int totalActivities) {

    vector<ActivityHappiness*> v;

    for (int i = 0; i < totalActivities; i++) {
        ActivityHappiness* actHappiness = new ActivityHappiness;
        cin >> actHappiness->a >> actHappiness->b >> actHappiness->c; 
        v.push_back(actHappiness);
    }

    return v;
}


int findMaximumTotalPoints(vector<ActivityHappiness*> &actHappinessVector, int totalActivities) {

    for (int i = 1; i < totalActivities; i++) {
        actHappinessVector[i]->a += max(actHappinessVector[i-1]->b, actHappinessVector[i-1]->c);
        actHappinessVector[i]->b += max(actHappinessVector[i-1]->a, actHappinessVector[i-1]->c);
        actHappinessVector[i]->c += max(actHappinessVector[i-1]->a, actHappinessVector[i-1]->b);
    }

    int finalA = actHappinessVector[totalActivities-1]->a;
    int finalB = actHappinessVector[totalActivities-1]->b;
    int finalC = actHappinessVector[totalActivities-1]->c;

    return max(finalA, max(finalB, finalC));
}


int main(void) {

    int totalActivities;
    cin >> totalActivities;

    vector<ActivityHappiness*> actHappinessVector = readActivityHappinessVector(totalActivities);

    cout << findMaximumTotalPoints(actHappinessVector, totalActivities) << "\n";

    return 0;
}
