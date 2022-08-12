#include <iostream>
#include <stack>

using namespace std;


stack<int> readStack(int totalElements) {

    stack<int> s;

    for (int i = 0; i < totalElements; i++) {
        int elementToPush; cin >> elementToPush;
        s.push(elementToPush);
    }

    return s;
}


void printReversedStack(stack<int> s) {

    if (s.empty())
        return;

    int removedElement = s.top(); s.pop();
    cout << removedElement << "\n";

    printReversedStack(s);
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalElements; cin >> totalElements;
        stack<int> currentStack = readStack(totalElements);
        printReversedStack(currentStack);
        if (i < totalTests - 1) cout << "\n";
    }

    return 0;
}
