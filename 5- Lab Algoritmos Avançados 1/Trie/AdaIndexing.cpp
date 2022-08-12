#include <iostream>

#define ALPHABET_SIZE 26

using namespace std;


struct Node {
    char character;
    Node* children[ALPHABET_SIZE];
    int degree;

    Node(char character) {
        this->character = character;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            this->children[i] = NULL;
        this->degree = 0;
    }
};


struct Trie {
    Node* root;

    Trie() {
        this->root = new Node('\0');
    }
};


void insertWordIntoTrie(Trie* trie, const string &word) {

    Node* currentNode = trie->root;

    for (char c : word) {
        int childIndex = c - 'a';
        if (currentNode->children[childIndex] == NULL)
            currentNode->children[childIndex] = new Node(c);
        currentNode = currentNode->children[childIndex];
        currentNode->degree += 1;
    }

}


Trie* buildTrie(int totalWords) {

    Trie* trie = new Trie();

    for (int i = 0; i < totalWords; i++) {
        string word;
        cin >> word; 
        insertWordIntoTrie(trie, word);
    }

    return trie;
}


int evaluateDegree(Trie* trie, const string &word) {

    Node* currentNode = trie->root;

    for (char c : word) {
        int childIndex = c - 'a';
        if (currentNode->children[childIndex] == NULL)
            return 0;
        currentNode = currentNode->children[childIndex];
    }

    return currentNode->degree;
}


void executeQueries(Trie* trie, int totalQueries) {

    for (int i = 0; i < totalQueries; i++) {
        string word;
        cin >> word;
        cout << evaluateDegree(trie, word) << "\n";
    }
}


int main(void) {

    int totalWords, totalQueries;
    cin >> totalWords >> totalQueries;

    Trie* trie = buildTrie(totalWords);

    executeQueries(trie, totalQueries);

    return 0;
}
