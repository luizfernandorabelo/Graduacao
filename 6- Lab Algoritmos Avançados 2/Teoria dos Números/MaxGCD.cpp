#include <iostream>

using namespace std;

int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int n;
        cin >> n;
        cout << n / 2 << "\n";
    }

    return 0;
}
