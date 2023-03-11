#include <iostream>
#include <cmath>

#define ASHISHGUP 0
#define FASTEST_FINGER 1

using namespace std;


bool isPrime(int n) {

    int sqrtN = sqrt(n);

    for (int i = 2; i <= sqrtN; i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}


int evaluateWinner(int n) {

    if (n == 1)
        return FASTEST_FINGER;
    
    if (n % 2 != 0 || n == 2)
        return ASHISHGUP;

    if (n % 4 == 0) {
        while (n % 2 == 0)
            n /= 2;
        return n == 1 ? FASTEST_FINGER : ASHISHGUP;
    }

    return isPrime(n / 2) ? FASTEST_FINGER : ASHISHGUP;
}


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int n;
        cin >> n;
        if (evaluateWinner(n) == ASHISHGUP)
            cout << "Ashishgup\n";
        else
            cout << "FastestFinger\n";
    }

    return 0;
}
