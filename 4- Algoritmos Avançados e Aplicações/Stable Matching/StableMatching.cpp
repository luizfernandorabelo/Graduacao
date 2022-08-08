#include <iostream>
#include <queue>

#define NULL_ID -1

using namespace std;

struct Person {
    queue<int> preferences;
    int id;
    bool single;
    int partnerId;
};

typedef Person** People;


People readPeople(int totalPeople) {

    People people = new Person*[totalPeople];

    for (int i = 0; i < totalPeople; i++) {
        people[i] = new Person;
        people[i]->single = true;
        people[i]->partnerId = NULL_ID;
        cin >> people[i]->id;
        for (int j = 0; j < totalPeople; j++) {
            int target; cin >> target;
            people[i]->preferences.push(target-1); // 0-based id
        }
        people[i]->id--; // 0-based id
    }

    return people;
}


int popTargetIndex(Person *person) {

    int targetIndex = person->preferences.front();
    person->preferences.pop();

    return targetIndex;
}


bool areLovers(Person *man, Person *woman) {

    bool lovers = false;
    int topId = NULL_ID;
    queue<int>preferencesCopy(woman->preferences);

    do {
        topId = woman->preferences.front();
        if (topId == man->id) {
            lovers = true;
            break;
        }
        woman->preferences.pop();
    } while (topId != woman->partnerId);

    woman->preferences = preferencesCopy;

    return lovers;
}


void engage(Person *man, Person *woman) {

    man->single = false;
    man->partnerId = woman->id;

    woman->single = false;
    woman->partnerId = man->id;

}


void propose(int manId, int womanId, People men, People women) {

    if (women[womanId]->single) {
        engage(men[manId], women[womanId]);
    }
    else if (areLovers(men[manId], women[womanId])) {
        int divorcedManId = women[womanId]->partnerId;
        engage(men[manId], women[womanId]);
        propose(divorcedManId, popTargetIndex(men[divorcedManId]), men, women);
    }
    else {
        propose(manId, popTargetIndex(men[manId]), men, women);
    }

}


void makeMatching(People men, People women, int totalMarriages) {

    for (int i = 0; i < totalMarriages; i++) {
        propose(i, popTargetIndex(men[i]), men, women);
    }

}


void printMarriages(People men, int totalMarriages) {

    for (int i = 0; i < totalMarriages; i++) {
        cout << men[i]->id+1 << ' ' << men[i]->partnerId+1 << '\n'; // 1-based id's
    }

}


int main(void) {

    int totalTests = 0; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalMarriages; cin >> totalMarriages;
        People women = readPeople(totalMarriages);
        People men = readPeople(totalMarriages);
        makeMatching(men, women, totalMarriages);
        printMarriages(men, totalMarriages);
        delete men; delete women;
    }

    return 0;
}
