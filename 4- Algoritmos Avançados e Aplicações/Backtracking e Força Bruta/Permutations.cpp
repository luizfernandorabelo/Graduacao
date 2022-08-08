#include <iostream>

using namespace std;


void generatePermutations(char *track, int index, int n) {

    if (index == n) {
        printf("%s\n", track);
        return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        track[index] = c;
        generatePermutations(track, index + 1, n);
    }
}


int main() {

    int n; cin >> n;

    char *track = new char[n + 1];
    track[n] = '\0';

    generatePermutations(track, 0, n);

    return 0;
}
