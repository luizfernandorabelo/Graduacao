#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#define TOTAL_COURSES 5

using namespace std;

typedef long long ll;


vector<int> readCourses() {

    vector<int> courses;

    for (int i = 0; i < TOTAL_COURSES; i++) {
        int courseNumber; cin >> courseNumber;
        courses.push_back(courseNumber);
    }

    return courses;
}


ll evaluateMappedSum(vector<int> &courses) {

    ll sum = 0;

    for (int course : courses) {
        sum *= 1000;
        sum += course;
    }

    return sum;
}


void solve(int totalFrosh) {

    map<ll,int> froshMap;
    int greatestPopularity = 1;

    for (int i = 0; i < totalFrosh; i++) {
        vector<int> courses = readCourses();
        sort(courses.begin(), courses.end());
        ll sum = evaluateMappedSum(courses);
        if (froshMap.find(sum) == froshMap.end())
            froshMap.insert({ sum, 1 }); 
        else
            froshMap[sum] = froshMap[sum] + 1;
        greatestPopularity = max(greatestPopularity, froshMap[sum]);
    }

    int totalWinners = 0;
    for (auto frosh : froshMap) {
        if (frosh.second == greatestPopularity)
            totalWinners += frosh.second;
    }

    cout << totalWinners << "\n";
}


int main(void) {
    
    int totalFrosh;
    cin >> totalFrosh;

    while (totalFrosh != 0) {
        solve(totalFrosh);
        cin >> totalFrosh;
    }

    return 0;
}
