#include <iostream>
#include <vector>
#include <map>

using namespace std;


map<string,string> readServersAndIPs(int totalElements) {

    map<string,string> serversAndIPs;

    for (int i = 0; i < totalElements; i++) {
        string key, value;
        cin >> value >> key;
        serversAndIPs.insert({key + ";", value});
    }

    return serversAndIPs;
}


vector<pair<string,string>> readCommandsAndIPs(int totalElements) {

    vector<pair<string,string>> commandsAndIPs;

    for (int i = 0; i < totalElements; i++) {
        pair<string,string> p;
        cin >> p.first >> p.second;
        commandsAndIPs.push_back(p);
    }

    return commandsAndIPs;
}


void printConfiguration(map<string,string> servers, vector<pair<string,string>> commands) {

    for (auto command : commands) {
        cout << command.first << " " << command.second << " #" << servers[command.second] << "\n";
    }

}


int main(void) {

    int totalServers, totalCommands;
    cin >> totalServers >> totalCommands;

    map<string,string> servers = readServersAndIPs(totalServers);
    vector<pair<string,string>> commands = readCommandsAndIPs(totalCommands);

    printConfiguration(servers, commands);

    return 0;
}
