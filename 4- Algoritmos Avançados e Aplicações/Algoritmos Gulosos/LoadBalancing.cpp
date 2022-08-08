/*
  -> Optimal Greedy Approach:
    - if the total animals is less than 2 * total jails, then add 0s to
      animal weights array, so that its new size will be 2 * total jails;
    - sort the animal weights array (in ascending or descending order);
    - for each jail, pick the current lightest and heaviest animals.
    NOTE: it only works if animals per jail is 2;
*/


#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#define ANIMALS_PER_JAIL 2
#define NULL_WEIGHT 0

using namespace std;


typedef list<int> Jail;


vector<int> readAnimalWeights(int totalAnimals) {

    vector<int> animalWeights;

    for (int i = 0; i < totalAnimals; i++) {
        int newWeight; cin >> newWeight;
        animalWeights.push_back(newWeight);
    }

    return animalWeights;
}


vector<Jail> divideJails(vector<int> animalWeights, int totalAnimals, int totalJails) {

    vector<Jail> jails;
    vector<int> divisionWeights(animalWeights.begin(), animalWeights.end());
    int totalEmptyWeights = ANIMALS_PER_JAIL * totalJails - totalAnimals;

    for (int i = 0; i < totalEmptyWeights; i++) {
        divisionWeights.push_back(NULL_WEIGHT);
    }

    sort(divisionWeights.begin(), divisionWeights.end());

    uint divWeightsSize = divisionWeights.size();

    for (uint i = 0; i < divWeightsSize / 2; i++) {
        Jail currentJail;
        currentJail.push_back(divisionWeights[i]);
        currentJail.push_back(divisionWeights[divWeightsSize - (i + 1)]);
        jails.push_back(currentJail);
    }

    return jails;
}


int main(void) {

    uint totalJails, totalAnimals;
    cin >> totalJails >> totalAnimals;

    vector<int> animalWeights = readAnimalWeights(totalAnimals);

    vector<Jail> jails = divideJails(animalWeights, totalAnimals, totalJails);

    if (jails.size() > totalJails) {
        cout << "Impossible!\n";
    } else for (Jail jail : jails) {
        cout << jail.front() << " " << jail.back() << "\n";
    }

    return 0;
}
