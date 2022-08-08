/*
  -> Optimal Greedy Approach:
    - sort the items by the ratio value / weight, which is
      directly proportional to the values and inversely
      proportional to the weights
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


typedef struct {
    double value;
    double weight;
    double fraction;
} Item;

typedef pair<vector<Item*>, double> KnapsackSolution;


vector<Item*> readItems(int totalItems) {

    vector<Item*> items;

    for (int i = 0; i < totalItems; i++) {
        items.push_back(new Item);
        cin >> items[i]->value >> items[i]->weight;
    }

    return items;
}


bool compareRatio(const Item* item1, const Item* item2) {
    double ratio1 = item1->value / item1->weight;
    double ratio2 = item2->value / item2->weight;
    return ratio2 <= ratio1;
}


KnapsackSolution buildKnapsackSolution(vector<Item*> items, double knapsackCapacity) {

    vector<Item*> itemsTaken;

    double remainingCapacity = knapsackCapacity;
    double totalValuesTaken = 0;

    sort(items.begin(), items.end(), compareRatio);

    for (Item* item : items) {
        if (item->weight <= remainingCapacity) {
            item->fraction = 1;
            remainingCapacity -= item->weight;
            totalValuesTaken += item->value;
            itemsTaken.push_back(item);
        } else {
            if (remainingCapacity > 0) {
                item->fraction = remainingCapacity / item->weight;
                remainingCapacity -= item->fraction * item->weight;
                totalValuesTaken += item->fraction * item->value;
                itemsTaken.push_back(item);
            }
            break;
        }
    }

    return make_pair(itemsTaken, totalValuesTaken);
}


void printSolution(KnapsackSolution solution) {

    for (Item* item : solution.first) {
        cout << item->value << " " << item->weight << " " << item->fraction << "\n";
    }

    cout << solution.second << "\n";
}


int main(void) {

    int totalItems;
    cin >> totalItems;

    vector<Item*> items = readItems(totalItems);

    double knapsackCapacity;
    cin >> knapsackCapacity;

    if (knapsackCapacity > 0) {
        KnapsackSolution solution = buildKnapsackSolution(items, knapsackCapacity);
        printSolution(solution);
    } else {
        cout << "0\n";
    }

    return 0;
}
