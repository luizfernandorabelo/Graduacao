/*

  * ISPM - Interval Scheduling Maximization Problem

    -> Optimal Greedy Approach:
      i.   sort the jobs by finish times, so that f_1 <= f_2 <= f_3 ... <= f_n
      ii.  jobsSelected = { }
      iii. for j = 1 to n:
            if job j compatible with last selected:
                jobsSelected = jobsSelected UNION { j }
      iv.  return jobsSelected

*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    char id;
    int startTime;
    int endTime;
} Job;


vector<Job*> readJobs(int totalJobs) {

    vector<Job*> jobs;

    for (int i = 0; i < totalJobs; i++) {
        jobs.push_back(new Job);
        cin >> jobs[i]->id >> jobs[i]->startTime >> jobs[i]->endTime;
    }

    return jobs;
}


bool compareEndTime(const Job* a, const Job* b) {
    return a->endTime <= b->endTime;
}


vector<Job*> buildMaxIntervalSubset(vector<Job*> jobs) {

    sort(jobs.begin(), jobs.end(), compareEndTime); 

    vector<Job*> subset;
    uint jobsSize = jobs.size();
    int endTime = 0;

    for (uint i = 0; i < jobsSize; i++) {
        Job* currentJob = jobs[i];
        if (currentJob->startTime >= endTime) {
            subset.push_back(currentJob);
            endTime = currentJob->endTime;
        }
    }

    return subset;
}


int main(void) {

    int totalJobs;
    cin >> totalJobs;

    vector<Job*> jobs = readJobs(totalJobs);
    vector<Job*> subset = buildMaxIntervalSubset(jobs);

    for (Job* job : subset) {
        cout << job->id << ": [" << job->startTime << ", " << job->endTime << ")\n";
    }

    return 0;
}
