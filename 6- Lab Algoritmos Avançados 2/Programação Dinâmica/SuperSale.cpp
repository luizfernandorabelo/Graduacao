#include <iostream>
#include <vector>

#define MAX_WEIGHT 30

using namespace std;


struct Product {
    int price;
    int weight;
};


vector<Product> readProducts(int totalProducts) {

    vector<Product> products;

    for (int i = 0; i < totalProducts; i++) {
        Product newProduct;
        cin >> newProduct.price >> newProduct.weight;
        products.push_back(newProduct);
    }

    return products;
}


vector<int> readPeopleCapacity(int totalPeople) {

    vector<int> capacities;

    for (int i = 0; i < totalPeople; i++) {
        int newCapacity; cin >> newCapacity;
        capacities.push_back(newCapacity);
    }
    
    return capacities;
}


vector<int> buildMaxPricesPerWeight(const vector<Product> &products) {

    vector<int> maxPrices(MAX_WEIGHT + 1, 0);

    for (auto product : products) {
        for (int weight = MAX_WEIGHT; weight >= product.weight; weight--)
            maxPrices[weight] = max(
                maxPrices[weight],
                maxPrices[weight - product.weight] + product.price
            );
    }

    return maxPrices;
}


int evaluateMaxValueOfGoods(const vector<Product> &products, const vector<int> &capacities) {

    vector<int> maxPricesPerWeight = buildMaxPricesPerWeight(products);

    int maxValueOfGoods = 0;

    for (int capacity : capacities)
        maxValueOfGoods += maxPricesPerWeight[capacity];

    return maxValueOfGoods;
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalProducts; cin >> totalProducts;
        vector<Product> products = readProducts(totalProducts); 
        int totalPeople; cin >> totalPeople;
        vector<int> capacities = readPeopleCapacity(totalPeople);
        cout << evaluateMaxValueOfGoods(products, capacities) << "\n";
    }

    return 0;
}
