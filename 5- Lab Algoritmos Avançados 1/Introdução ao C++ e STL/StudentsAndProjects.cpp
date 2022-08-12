#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define PROJECT_NAME 1
#define USER_NAME 2
#define INVALID_INPUT 3

using namespace std;

typedef map<string,string> UserToProjectMap;
typedef map<string,int> ProjectToSignupsMap;


int getInputType(string input) {

    if (input[0] >= 'a')
        return USER_NAME;

    if (input[0] >= 'A')
        return PROJECT_NAME;
    
    return INVALID_INPUT;
}


void insertProject(ProjectToSignupsMap &projectToSignups, string projectName) {

    try {
        projectToSignups.at(projectName);
    } catch (const out_of_range&) {
        projectToSignups.insert({projectName, 0});
    }

}


void incrementProject(ProjectToSignupsMap &projectToSignups, string &projectName) {

    ProjectToSignupsMap::iterator it;

    if ((it = projectToSignups.find(projectName)) != projectToSignups.end())
        it->second += 1;

}


void decrementProject(ProjectToSignupsMap &projectToSignups, string &projectName) {

    ProjectToSignupsMap::iterator it;

    if ((it = projectToSignups.find(projectName)) != projectToSignups.end())
        it->second -= 1;

}


void insertUser(UserToProjectMap &userToProject, ProjectToSignupsMap &projectToSignups, string &userName, string &projectName) {

    UserToProjectMap::iterator it = userToProject.find(userName);

    if (it != userToProject.end()) {
        string existentProject = it->second;
        if (existentProject.compare(projectName) != 0) {
            decrementProject(projectToSignups, existentProject);
            it->second = "";
        }
    } else {
        userToProject.insert({userName, projectName});
        incrementProject(projectToSignups, projectName);
    }

}


vector<pair<string,int>> buildProjectsAndSignupsVector(ProjectToSignupsMap &projectToSignups) {

    vector<pair<string,int>> v;

    for (auto it = projectToSignups.begin(); it != projectToSignups.end(); it++) {
        v.push_back({it->first, it->second}); 
    }
    
    return v;
}


bool comp(pair<string,int> &a, pair<string,int> b) {
    if (b.second < a.second)
        return true;
    if (b.second == a.second && b.first.compare(a.first) > 0)
        return true;
    return false;
}


void printProjectsAndSignupsAscended(ProjectToSignupsMap &projectToSignups) {

    vector<pair<string,int>> v = buildProjectsAndSignupsVector(projectToSignups);

    sort(v.begin(), v.end(), comp);

    for (auto element : v) {
        cout << element.first << " " << element.second << "\n";
    }

}


void fillProjectToSignupsMap(ProjectToSignupsMap &projectToSignups) {

    string input, lastProject;
    UserToProjectMap userToProject;

    while (getline(cin, input)) {
        switch (getInputType(input)) {
            case PROJECT_NAME:
                insertProject(projectToSignups, input);
                lastProject = input;
                break;
            case USER_NAME:
                insertUser(userToProject, projectToSignups, input, lastProject);
                break;
            case INVALID_INPUT:
                return;
            default:
                break;
        }
    }

}


int main(void) {

    ProjectToSignupsMap projectToSignups;

    while (true) {
        fillProjectToSignupsMap(projectToSignups);
        if (projectToSignups.size() > 0)
            printProjectsAndSignupsAscended(projectToSignups);
        else
            break;
        projectToSignups.clear();
    }

    return 0;
}
