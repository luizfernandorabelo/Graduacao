#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;


struct Item {
    ll weight;
    ll value;
};


vector<Item*> readItems(int totalItems) {

    vector<Item*> items;

    for (int i = 0; i < totalItems; i++) {
        Item* currentItem = new Item;
        cin >> currentItem->weight >> currentItem->value;
        items.push_back(currentItem);
    }

    return items;
}


ll** initializeSumMatrix(int totalItems, int capacity) {

    ll **sums = new ll*[totalItems + 1];

    for (int i = 0; i <= totalItems; i++)
        sums[i] = new ll[capacity + 1];

    for (int j = 0; j <= capacity; j++)
        sums[0][j] = 0;

    return sums;
}


void deleteSumMatrix(ll** sums, int totalItems) {

    for (int i = 0; i <= totalItems; i++)
        delete sums[i];

    delete sums;
}


ll evaluateMaximalPossibleSum(vector<Item*> &items, int capacity) {

    int totalItems = items.size();
    ll** sums = initializeSumMatrix(totalItems, capacity);

    for (int i = 1; i <= totalItems; i++) {
        Item* currentItem = items[i-1];
        for (int j = 0; j <= capacity; j++) {
            if (currentItem->weight > j)
                sums[i][j] = sums[i-1][j];
            else
                sums[i][j] = max(sums[i-1][j], currentItem->value + sums[i-1][j-currentItem->weight]);
        }
    }

    ll maxSum = sums[totalItems][capacity];

    deleteSumMatrix(sums, totalItems);

    return maxSum;
}


int main(void) {

    int totalItems, capacity;
    cin >> totalItems >> capacity;

    vector<Item*> items = readItems(totalItems);

    cout << evaluateMaximalPossibleSum(items, capacity) << "\n";

    return 0;
}
