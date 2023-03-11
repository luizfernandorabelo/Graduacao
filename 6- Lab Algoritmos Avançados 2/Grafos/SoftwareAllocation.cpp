#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define NULL_VERTEX -1
#define UNWEIGHTED_EDGE 0
#define END_OF_LINE ';'
#define IMPOSSIBLE "!"
#define TOTAL_COMPUTERS 10
#define TOTAL_DESCRIPTIONS 26
#define TOTAL_VERTICES (TOTAL_COMPUTERS + TOTAL_DESCRIPTIONS + 2)
#define START_VERTEX (TOTAL_VERTICES - 2)
#define SINK_VERTEX (TOTAL_VERTICES - 1)

using namespace std;

typedef vector<vector<int>> AdjMatrix;


struct Job {
    char id;
    int requests;
    vector<int> availableComputers;
};


Job* readJob() {

    Job *job = new Job;
    job->id = job->requests = 0;

    string input;
    getline(cin, input);

    if (input.length() > 2) {
        job->id = input[0];
        job->requests = (int) input[1] - '0';
        for (uint i = 3; i < input.length(); i++) {
            if (input[i] != END_OF_LINE)
                job->availableComputers.push_back((int) (input[i] - '0'));
        }
    }
    
    return job;
}


vector<Job*> readJobs() {

    vector<Job*> jobs;

    while (true) {
        Job* newJob = readJob();
        if (newJob->requests == 0)
            break;
        jobs.push_back(newJob);
    }

    return jobs;
}


int evaluateExpectedFlow(const vector<Job*> &jobs) {

    int expectedFlow = 0;

    for (Job* job : jobs)
        expectedFlow += job->requests;

    return expectedFlow;
}


AdjMatrix buildAdjMatrixFromJobs(const vector<Job*> &jobs) {

    AdjMatrix adjMatrix(TOTAL_VERTICES, vector<int>(TOTAL_VERTICES, UNWEIGHTED_EDGE));

    for (Job* job : jobs) {
        int sourceVertex = job->id - 'A' + TOTAL_COMPUTERS;
        for (int targetVertex : job->availableComputers)
            adjMatrix[sourceVertex][targetVertex] = 1;
        adjMatrix[START_VERTEX][sourceVertex] = job->requests;
    }

    for (int i = 0; i < TOTAL_COMPUTERS; i++)
        adjMatrix[i][SINK_VERTEX] = 1;

    return adjMatrix;
}


vector<int> buildPredecessors(const AdjMatrix &adjMatrix) {

    vector<int> predecessors(TOTAL_VERTICES, NULL_VERTEX);
    vector<bool> marks(TOTAL_VERTICES, false);

    bool endVertexAchieved = false;
    int currentVertex = START_VERTEX;

    queue<int> q;
    q.push(currentVertex);
    marks[currentVertex] = true;

    while (!q.empty() && !endVertexAchieved) {
        currentVertex = q.front(); q.pop();
        for (int neighborVertex = 0; neighborVertex < TOTAL_VERTICES; neighborVertex++) {
            int neighborEdgeWeight = adjMatrix[currentVertex][neighborVertex];
            if (marks[neighborVertex] || neighborEdgeWeight == UNWEIGHTED_EDGE)
                continue;
            predecessors[neighborVertex] = currentVertex;
            if (neighborVertex == SINK_VERTEX) {
                endVertexAchieved = true;
                break;
            }
            q.push(neighborVertex);
            marks[neighborVertex] = true;
        }
    }

    return predecessors;
}


vector<int> buildPath(const AdjMatrix &adjMatrix) {

    vector<int> path, predecessors = buildPredecessors(adjMatrix);

    if (predecessors[SINK_VERTEX] != NULL_VERTEX) { 
        int currentVertex = SINK_VERTEX;
        while (currentVertex != START_VERTEX) {
            path.push_back(currentVertex);
            currentVertex = predecessors[currentVertex];
        }
        path.push_back(START_VERTEX);
        reverse(path.begin(), path.end());
    }

    return path;
}


int evaluateBottleNeck(const vector<int> &path, AdjMatrix &adjMatrix) {

    if (path.size() == 1)
        return adjMatrix[path[0]][path[0]];

    int bottleNeck = INT32_MAX;

    for (uint i = 0; i < path.size() - 1; i++) {
        int sourceVertex = path[i], targetVertex = path[i+1];
        bottleNeck = min(bottleNeck, adjMatrix[sourceVertex][targetVertex]);
    }

    return bottleNeck;
}


void updateAdjacencyMatrix(AdjMatrix &adjMatrix, const vector<int> &path, int bottleNeck) {
    for (uint i = 0; i < path.size() - 1; i++) {
        int sourceVertex = path[i], targetVertex = path[i+1];
        adjMatrix[sourceVertex][targetVertex] -= bottleNeck;
        adjMatrix[targetVertex][sourceVertex] += bottleNeck;
    }
}


int evaluateMaxNetworkFlow(AdjMatrix &adjMatrix) {

    int maxFlow = 0;
    vector<int> path = buildPath(adjMatrix);

    while (path.size() > 0) {
        int bottleNeck = evaluateBottleNeck(path, adjMatrix);
        updateAdjacencyMatrix(adjMatrix, path, bottleNeck);
        maxFlow += bottleNeck;
        path = buildPath(adjMatrix);
    }

    return maxFlow;
}


int main(void) {

    while (true) {

        vector<Job*> jobs = readJobs();

        if (jobs.size() == 0)
            break;

        AdjMatrix adjMatrix = buildAdjMatrixFromJobs(jobs);

        int expectedFlow = evaluateExpectedFlow(jobs);
        int maxFlow = evaluateMaxNetworkFlow(adjMatrix);

        if (maxFlow == expectedFlow) {
            string configuration = "__________";
            for (int i = 0; i < TOTAL_COMPUTERS; i++) {
                if (adjMatrix[SINK_VERTEX][i] == 1) {
                    for (Job *job : jobs) {
                        if (adjMatrix[i][job->id - 'A' + TOTAL_COMPUTERS] == adjMatrix[SINK_VERTEX][i]) {
                            configuration[i] = job->id;
                            break;
                        }
                    }
                }
            }
            cout << configuration << "\n";
        } else {
            cout << IMPOSSIBLE << "\n";
        }
    }

    return 0;
}
