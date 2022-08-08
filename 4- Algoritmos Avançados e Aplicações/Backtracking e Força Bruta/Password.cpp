#include <iostream>
#include <vector>

#define WORD '#'
#define DIGIT '0'

using namespace std;

typedef struct {
    vector<string> dictionary;
    vector<string> rules;
} Description;

typedef unsigned int uint;


vector<Description*> readDescriptions() {

    vector<Description*> descriptions;
    int totalWords, totalRules;

    while (cin >> totalWords) {
        Description* newDescription = new Description;
        for (int i = 0; i < totalWords; i++) {
            string word; cin >> word;
            newDescription->dictionary.push_back(word);
        }
        cin >> totalRules;
        for (int i = 0; i < totalRules; i++) {
            string rule; cin >> rule;
            newDescription->rules.push_back(rule);
        }
        descriptions.push_back(newDescription);
    }

    return descriptions;
}


void printPossiblePasswordsRec(vector<string> words, string rule, uint ruleIndex, string password) {

    if (ruleIndex == rule.length()) {
        cout << password << '\n';
        return;
    }

    if (rule[ruleIndex] == DIGIT) {
        for (int i = 0; i < 10; i++)
            printPossiblePasswordsRec(words, rule, ruleIndex + 1, password + to_string(i));
    }
    else {
        for (uint i = 0; i < words.size(); i++)
            printPossiblePasswordsRec(words, rule, ruleIndex + 1, password + words[i]);
    }

}


void printPossiblePasswords(Description* description) {

    Description* d = description;

    for (uint i = 0; i < d->rules.size(); i++)
        printPossiblePasswordsRec(d->dictionary, d->rules[i], 0, "");

}


int main(void) {
    
    vector<Description*> descriptions = readDescriptions();

    for (uint i = 0; i < descriptions.size(); i++) {
        cout << "--\n";
        printPossiblePasswords(descriptions[i]);
    }

    return 0;
}
