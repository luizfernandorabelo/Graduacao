/*
  -> Optimal Greedy Approach:
    (1) Sort intervals by starting time so that s1 <= s2 <= ... <= sn;
    (2) totalClassrooms = 0
    (3) for i = 1 to n:
            if (lecture i is compatible with some classroom k):
                schedule lecture i in classroom k
            else:
                allocate a new classroom (totalClassrooms++)
                schedule lecture j in the new classroom
    NOTE: keeping the classrooms in a priority queue (sorted in ascending order of finish time)
          reduces the complexity from n^2 log n to n log n
*/


#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

typedef struct {
    char id;
    int startTime;
    int endTime;
} Job;

typedef stack<Job*> Room;

class endTimeComparator {
public:
    int operator() (const Room& r1, const Room& r2) {
        return r1.top()->endTime >= r2.top()->endTime;
    }
};

typedef priority_queue<Room, vector<Room>, endTimeComparator> Rooms;


vector<Job*> readJobs(int totalJobs) {

    vector<Job*> jobs;

    for (int i = 0; i < totalJobs; i++) {
        jobs.push_back(new Job);
        cin >> jobs[i]->id >> jobs[i]->startTime >> jobs[i]->endTime;
    }

    return jobs;
}


bool compareStartTime(const Job* a, const Job* b) {
    return a->startTime <= b->startTime;
}


bool isJobCompatibleWithTopRoom(Job* job, Rooms rooms) {
    if (rooms.empty()) {
        return false;
    }
    return rooms.top().top()->endTime <= job->startTime;
}


Rooms allocateMinRooms(vector<Job*> jobs) {

    Rooms rooms;

    sort(jobs.begin(), jobs.end(), compareStartTime);

    for (Job* job : jobs) {
        if (isJobCompatibleWithTopRoom(job, rooms)) {
            Room topRoom = rooms.top(); rooms.pop();
            topRoom.push(job);
            rooms.push(topRoom);
        } else {
            Room newRoom;
            newRoom.push(job);
            rooms.push(newRoom);
        }
    }

    return rooms;
}


void printJobs(Room& room) {

    if (room.empty())
        return;

    Job* topJob = room.top(); room.pop();

    printJobs(room);

    cout << topJob->id << "[" << topJob->startTime << "," << topJob->endTime << "); ";
}


void printRooms(Rooms& rooms) {

    int counter = 0;

    while (!rooms.empty()) {
        cout << "Room " << counter++ << ": ";
        Room topRoom = rooms.top(); rooms.pop();
        printJobs(topRoom);
        cout << "\n";
    }

}


int main(void) {

    int totalJobs;
    cin >> totalJobs;

    vector<Job*> jobs = readJobs(totalJobs);

    Rooms rooms = allocateMinRooms(jobs);

    cout << "Total rooms: " << rooms.size() << "\n";

    printRooms(rooms);

    return 0;
}
