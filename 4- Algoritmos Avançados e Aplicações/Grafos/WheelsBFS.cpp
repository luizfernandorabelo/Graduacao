#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define TOTAL_WHEELS 4
#define TOTAL_NEIGHBORS 8

using namespace std;

typedef struct {
    int configuration[TOTAL_WHEELS];
    int distance;
} ConfigDistance;

int movements[TOTAL_NEIGHBORS][TOTAL_WHEELS] = { { 1,  0,  0,  0},
                                                 {-1,  0,  0,  0},
                                                 { 0,  1,  0,  0},
                                                 { 0, -1,  0,  0},
                                                 { 0,  0,  1,  0},
                                                 { 0,  0, -1,  0},
                                                 { 0,  0,  0,  1},
                                                 { 0,  0,  0, -1} };


int* readConfiguration() {

    int* currentConfig = new int[TOTAL_WHEELS];

    for (int i = 0; i < TOTAL_WHEELS; i++)
        cin >> currentConfig[i];
    
    return currentConfig;
}


vector<int*> readProhibitedConfigurations(int totalProhibited) {

    vector<int*> prohibitedConfig;

    for (int i = 0; i < totalProhibited; i++)
        prohibitedConfig.push_back(readConfiguration());


    return prohibitedConfig;
}


bool areEqual(int* config1, int* config2) {

    for (int i = 0; i < TOTAL_WHEELS; i++) {
        if (config1[i] != config2[i])
            return false;
    }
    
    return true;
}


bool isValidConfiguration(int* configuration, vector<int*>& prohibConfigs) {

    for (int* prohibited : prohibConfigs) {
        if (areEqual(configuration, prohibited))
            return false;
    }

    return true;
}


ConfigDistance* makeConfigDistance(int* configuration, int distance) {

    ConfigDistance* configDistance = new ConfigDistance;

    memcpy(configDistance->configuration, configuration, TOTAL_WHEELS * sizeof(int));
    configDistance->distance = distance;

    return configDistance;
}


void freeQueue(queue<ConfigDistance*> q) {
    while (!q.empty()) {
        ConfigDistance* cd = q.front(); q.pop();
        free(cd);
    }
}


int* getNewConfiguration(int* currentConfig, int* movement) {
    
    int* newConfiguration = new int[TOTAL_WHEELS];

    for (int i = 0; i < TOTAL_WHEELS; i++)
        newConfiguration[i] = (currentConfig[i] + movement[i] + 10) % 10;
    
    return newConfiguration;
}


bool isMarked(int* configuration, bool (*marks)[10][10][10]) {
    return marks[configuration[0]][configuration[1]][configuration[2]][configuration[3]];
}


void markConfiguration(int* configuration, bool (*marks)[10][10][10]) {
    marks[configuration[0]][configuration[1]][configuration[2]][configuration[3]] = true;
}


int evaluateMinimumNumberOfPresses(int* initialConfig, int* targetConfig,
                                   vector<int*> prohibitedConfigs, bool (*marks)[10][10][10]) {

    queue<ConfigDistance*> q;
    q.push(makeConfigDistance(initialConfig, 0));
    markConfiguration(initialConfig, marks);

    while (!q.empty()) {
        ConfigDistance* currentCD = q.front(); q.pop();
        if (areEqual(currentCD->configuration, targetConfig)) {
            int minPresses = currentCD->distance;
            freeQueue(q);
            return minPresses;
        }
        for (int i = 0; i < TOTAL_NEIGHBORS; i++) {
            int* newConfig = getNewConfiguration(currentCD->configuration, movements[i]);
            if (isValidConfiguration(newConfig, prohibitedConfigs) && !isMarked(newConfig, marks)) {
                markConfiguration(newConfig, marks);
                q.push(makeConfigDistance(newConfig, currentCD->distance + 1));
            }
            free(newConfig);
        }
        free(currentCD);
    }

    return -1;
}


void deleteConfigurations(int* firstConfig, int* targetConfig, vector<int*> prohibitedConfigs) {

    delete [] firstConfig;
    delete [] targetConfig;

    for (unsigned int i = 0; i < prohibitedConfigs.size(); i++)
        delete [] prohibitedConfigs[i];

}


int main(void) {

    bool marks[10][10][10][10];
    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        memset(marks, false, sizeof(marks));
        int* currentConfiguration = readConfiguration();
        int* targetConfiguration = readConfiguration();
        int totalProhibited; cin >> totalProhibited;
        vector<int*> prohibitedConfigs = readProhibitedConfigurations(totalProhibited);
        cout << evaluateMinimumNumberOfPresses(currentConfiguration, targetConfiguration, prohibitedConfigs, marks) << "\n";
        deleteConfigurations(currentConfiguration, targetConfiguration, prohibitedConfigs);
    }

    return 0;
}
