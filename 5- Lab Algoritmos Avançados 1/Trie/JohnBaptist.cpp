#include <iostream>

#define ALPHABET_SIZE 26

#define INSERT 1
#define REMOVE 2
#define DEGREE 3

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


void insertWordIntoTrie(Trie* trie, string word) {

    Node* currentNode = trie->root;

    for (char c : word) {
        int childIndex = c - 'a';
        if (currentNode->children[childIndex] == NULL)
            currentNode->children[childIndex] = new Node(c);
        currentNode = currentNode->children[childIndex];
        currentNode->degree += 1;
    }

}


int evaluateDegree(Trie* trie, string word) {

    Node* currentNode = trie->root;

    for (char c : word) {
        int childIndex = c - 'a';
        if (currentNode->children[childIndex] == NULL)
            return 0;
        currentNode = currentNode->children[childIndex];
    }

    return currentNode->degree;
}


void removeWordFromTrie(Trie* trie, string word) {

    if (word.length() == 0)
        return;
        
    Node* currentNode = trie->root;

    for (char c : word) {
        Node* nextNode = currentNode->children[c - 'a'];
        nextNode->degree -= 1;
        if (nextNode->degree == 0)
            currentNode->children[c - 'a'] = NULL;
        if (currentNode->degree == 0 && currentNode != trie->root)
            delete currentNode;
        // if (currentNode->degree == 0)
        //     delete currentNode;
        currentNode = nextNode;
    }

}


int main(void) {

    int totalQueries;
    cin >> totalQueries;

    Trie* trie = new Trie;

    for (int i = 0; i < totalQueries; i++) {
        int queryType; string word;
        cin >> queryType >> word;
        switch (queryType) {
            case INSERT:
                insertWordIntoTrie(trie, word);
                break;
            case REMOVE:
                removeWordFromTrie(trie, word);
                break;
            case DEGREE:
                cout << evaluateDegree(trie, word) << "\n";
                break;
            default:
                break;
        }
    }
    
    return 0;
}
