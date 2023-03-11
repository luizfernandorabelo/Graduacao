#include <iostream>

using namespace std;


void solve(string &current, string &original, int index) {

    if (current.length() == original.length()) {
        cout << current << "\n";
        return;
    }

    for (uint i = 0; i <= current.length(); i++) {
        string previous = current;
        current = current.substr(0, i) + original[index] + current.substr(i);
        solve(current, original, index + 1);
        current = previous;
    }
}


int main(void) {

    string original, current;
    cin >> original;

    current = "";
    solve(current, original, 0);

    while (cin >> original) {
        cout << "\n";
        current = "";
        solve(current, original, 0);
    }

    return 0;
}
