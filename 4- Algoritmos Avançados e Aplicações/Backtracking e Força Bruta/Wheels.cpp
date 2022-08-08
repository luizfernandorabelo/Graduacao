#include <iostream>
#include <vector>
#include <cstring>

#define TOTAL_WHEELS 4

using namespace std;


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


bool solveWheels(int* currConfig, int* targConfig, vector<int*>& prohibConfigs, int& minPresses, int currPresses, int wheel) {

    if (!isValidConfiguration(currConfig, prohibConfigs) || currPresses > minPresses)
        return false;

    if (wheel >= TOTAL_WHEELS) {
        if (areEqual(currConfig, targConfig) && currPresses < minPresses)
            minPresses = currPresses;
        return true;
    }
    
    int* currConfigCopy = new int[TOTAL_WHEELS];
    int initialDigit = currConfig[wheel];

    memcpy(currConfigCopy, currConfig, TOTAL_WHEELS * sizeof(int));
    solveWheels(currConfigCopy, targConfig, prohibConfigs, minPresses, currPresses, wheel + 1);

    memcpy(currConfigCopy, currConfig, TOTAL_WHEELS * sizeof(int));
    for (int i = 1; i < 10; i++) {
        currConfigCopy[wheel] = (i + initialDigit) % 10;
        if(!solveWheels(currConfigCopy, targConfig, prohibConfigs, minPresses, currPresses + i, wheel + 1))
            break;
    }

    memcpy(currConfigCopy, currConfig, TOTAL_WHEELS * sizeof(int));
    for (int i = 1; i < 10; i++) {
        currConfigCopy[wheel] = (initialDigit - i + 10) % 10;
        if(!solveWheels(currConfigCopy, targConfig, prohibConfigs, minPresses, currPresses + i, wheel + 1))
            break;
    }

    return true;
}


int evaluateMinimumNumberOfPresses(int* initialConfig, int* targetConfig, vector<int*> prohibitedConfigs) {

    int minPresses = INT32_MAX / 2;

    solveWheels(initialConfig, targetConfig, prohibitedConfigs, minPresses, 0, 0);

    return minPresses != INT32_MAX / 2 ? minPresses : -1;
}


void deleteConfigurations(int* firstConfig, int* targetConfig, vector<int*> prohibitedConfigs) {

    delete [] firstConfig;
    delete [] targetConfig;

    for (unsigned int i = 0; i < prohibitedConfigs.size(); i++)
        delete [] prohibitedConfigs[i];

}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int* currentConfiguration = readConfiguration();
        int* targetConfiguration = readConfiguration();
        int totalProhibited; cin >> totalProhibited;
        vector<int*> prohibitedConfigs = readProhibitedConfigurations(totalProhibited);
        cout << evaluateMinimumNumberOfPresses(currentConfiguration, targetConfiguration, prohibitedConfigs) << "\n";
        deleteConfigurations(currentConfiguration, targetConfiguration, prohibitedConfigs);
    }

    return 0;
}
