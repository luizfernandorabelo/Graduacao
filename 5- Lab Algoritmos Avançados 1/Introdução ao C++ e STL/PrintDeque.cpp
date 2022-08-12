#include <iostream>
#include <deque>

#define SWITCHING_COST 0
#define PRINTING_COST 1

using namespace std;

typedef struct Job {
    int index;
    int priority;
    Job(int index, int priority) {
        this->index = index;
        this->priority = priority;
    }
} Job;


deque<Job*> readJobs(int totalJobs) {

    deque<Job*> jobs;

    for (int i = 0; i < totalJobs; i++) {
        int priority; cin >> priority;
        Job* newJob = new Job(i, priority);
        jobs.push_back(newJob);
    }

    return jobs;
}


void removeFrontJob(deque<Job*> &jobs) {
    Job *removedJob = jobs.front();
    jobs.pop_front();
    delete removedJob;
}


int estimateTime(deque<Job*> &jobs, int targetJobIndex) {

    Job* frontJob = jobs.front();

    for (Job* job : jobs) {
        if (job->priority > frontJob->priority) {
            jobs.push_back(new Job(frontJob->index, frontJob->priority));
            removeFrontJob(jobs);
            return SWITCHING_COST + estimateTime(jobs, targetJobIndex);
        }
    }

    if (frontJob->index == targetJobIndex)
        return PRINTING_COST;  // front job has the greatest priority and the target index
    
    removeFrontJob(jobs);

    return PRINTING_COST + estimateTime(jobs, targetJobIndex);
}


void deleteRemainingJobs(deque<Job*> &jobs) {

    while (!jobs.empty()) {
        removeFrontJob(jobs);
    }

}


int main(void) {
    
    int totalTests; cin >> totalTests;

    for (int i = 0; i < totalTests; i++) {
        int totalJobs, targetJobIndex;
        cin >> totalJobs >> targetJobIndex;
        deque<Job*> jobs = readJobs(totalJobs);
        cout << estimateTime(jobs, targetJobIndex) << "\n";
        deleteRemainingJobs(jobs);
    }

    return 0;
}
