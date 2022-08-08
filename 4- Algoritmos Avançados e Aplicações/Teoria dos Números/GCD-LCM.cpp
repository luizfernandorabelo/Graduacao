#include <iostream>

using namespace std;

typedef long long ll;


ll gcd(ll a, ll b) {

    while (a > 0 && b > 0) {
        if (a >= b)
            a %= b;
        else
            b %= a;
    }

    return max(a, b);
}


pair<ll,ll> evaluateTargetPair(ll targetGCD, ll targetLCM) {

    for (ll i = targetGCD; i <= targetLCM; i++) {
        if (targetLCM % i == 0) {
            for (ll j = i; j <= targetLCM; j++) {
                if (targetLCM % j == 0) {
                    ll gcdValue = gcd(i, j);
                    ll lcmValue = i * j / gcdValue;
                    if (gcdValue == targetGCD && lcmValue == targetLCM)
                        return {i, j};
                }
            }
        }
    }

    return {-1, -1};
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int targetGCD, targetLCM;
        cin >> targetGCD >> targetLCM;
        pair<ll,ll> solvedPair = evaluateTargetPair(targetGCD, targetLCM);
        if (solvedPair.first == -1)
            cout << -1 << "\n";
        else
            cout << solvedPair.first << " " << solvedPair.second << "\n";
    }

    return 0;
}