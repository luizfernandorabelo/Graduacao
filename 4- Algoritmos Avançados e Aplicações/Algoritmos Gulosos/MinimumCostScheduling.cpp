/*
  -> Optimal Greedy Approach:
    - In order to minimize the cost (cumulated length * current weight), we may think:
        - The greater the weight, the shorter the cumulated length needs to be;
    - So, we need to sort the jobs by the ratio length / weight and calculate the cost.
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    int length;
    int weight;
} Job;


vector<Job*> readJobs(int totalJobs) {

    vector<Job*> jobs;

    for (int i = 0; i < totalJobs; i++) {
        jobs.push_back(new Job);
        cin >> jobs[i]->length >> jobs[i]->weight;
    }

    return jobs;
}


bool compare(const Job* a, const Job *b) {
    double ratioA = (double) a->length / a->weight * 100;
    double ratioB = (double) b->length / b->weight * 100;
    return ratioA < ratioB;
}


int evaluateMinimalCostScheduling(vector<Job*> &jobs) {

    sort(jobs.begin(), jobs.end(), compare);

    int cost = 0;
    int cumulatedLength = 0;

    for (unsigned int i = 0; i < jobs.size(); i++) {
        cumulatedLength += jobs[i]->length;
        cost += cumulatedLength * jobs[i]->weight;
    }

    return cost;
}


int main(void) {

    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalJobs; cin >> totalJobs;
        vector<Job*> jobs = readJobs(totalJobs);
        cout << evaluateMinimalCostScheduling(jobs) << '\n';
    }

    return 0;
}
