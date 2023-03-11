#include <iostream>

using namespace std;


void changeFinalString(string &s) {

    for (int i = 0; i < (int) s.length(); i++) {
        if (i % 2 == 0) {  // Alice's turn
            if (s[i] != 'a')
                s[i] = 'a';
            else
                s[i] = 'b';
        }
        else {  // Bobs's turn
            if (s[i] != 'z')
                s[i] = 'z';
            else
                s[i] = 'y';
        }
    }

}


int main(void) {

    int totalTests;
    cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        string s;
        cin >> s;
        changeFinalString(s);
        cout << s << "\n";
    }

    return 0;
}
