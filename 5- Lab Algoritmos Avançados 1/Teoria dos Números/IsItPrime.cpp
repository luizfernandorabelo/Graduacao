#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


bool isPrime(int n) {

    if (n <= 1)
        return false;

    int limit = sqrt(n) + 1;

    for (int i = 2; i < limit; i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}


int main(void) {

    int n; cin >> n;

    if (isPrime(n))
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
