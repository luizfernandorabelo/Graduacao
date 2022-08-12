#include <iostream>
#include <vector>
#include <cmath>

#define PLUS_SIGN '+'
#define MULT_SIGN '*'

using namespace std;

typedef unsigned int uint;
typedef long long ll;


int parseNumberToInteger(string &expression, uint startIndex, uint endIndex) {

    int base = pow(10, (endIndex - startIndex)), number = 0;

    for (uint i = startIndex; i <= endIndex; i++) {
        number += base * (expression[i] - '0');
        base /= 10;
    }

    return number;    
}


pair<vector<int>,vector<char>> buildOperandAndOperationVectors(string &expression) {

    vector<int> operands;
    vector<char> operations;

    uint expressionLength = expression.length();

    for (uint i = 0; i < expressionLength; i++) {
        if (expression[i] == PLUS_SIGN || expression[i] == MULT_SIGN) {
            operations.push_back(expression[i]);
        } else {
            if (i + 1 < expressionLength && isdigit(expression[i+1])) {
                operands.push_back(parseNumberToInteger(expression, i, i + 1));
                i++;
            }
            else {
                operands.push_back(parseNumberToInteger(expression, i, i));
            }
        }
    }

    return { operands, operations };
}


pair<ll,ll> evaluateMaximumAndMinimumInterpretation(string &expression) {

    pair<vector<int>,vector<char>> p = buildOperandAndOperationVectors(expression);

    vector<int> multiplicationOperands(p.first);
    vector<int> additionOperands(p.first);
    vector<char> operations = p.second;

    uint operationsSize = operations.size();

    if (operationsSize == 0)
        return { additionOperands[0], additionOperands[0] };

    ll maximumResult = 1, minimumResult = 0;

    for (uint i = 0; i < operationsSize; i++) {
        if (operations[i] == PLUS_SIGN) {
            multiplicationOperands[i+1] += multiplicationOperands[i];
            minimumResult += additionOperands[i];
        } else {
            additionOperands[i+1] *= additionOperands[i];
            maximumResult *= multiplicationOperands[i];
        }
    }

    maximumResult *= multiplicationOperands[multiplicationOperands.size() - 1];
    minimumResult += additionOperands[additionOperands.size() - 1];

    return { maximumResult, minimumResult };
}


int main(void) {

    int totalTestes; cin >> totalTestes;

    for (int i = 0; i < totalTestes; i++) {
        string expression; cin >> expression;
        pair<ll,ll> p = evaluateMaximumAndMinimumInterpretation(expression);
        cout << "The maximum and minimum are " << p.first << " and " << p.second << ".\n";
    }

    return 0;
}
