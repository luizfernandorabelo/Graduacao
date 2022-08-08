#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

#define NULL_VERTEX -1
#define UNWEIGHTED_EDGE 0

using namespace std;


int** readAdjacencyMatrix(int totalVertices) {

    int** adjMatrix = new int*[totalVertices];

    for (int i = 0; i < totalVertices; i++) {
        adjMatrix[i] = new int[totalVertices];
        for (int j = 0; j < totalVertices; j++)
            cin >> adjMatrix[i][j];
    }

    return adjMatrix;
}


void deleteAdjacencyMatrix(int** adjMatrix, int totalVertices) {

    for (int i = 0; i < totalVertices; i++)
        free(adjMatrix[i]);

    delete [] adjMatrix;

}


int* initializePredecessors(int totalVertices) {

    int* predecessors = new int[totalVertices];

    memset(predecessors, NULL_VERTEX, totalVertices * sizeof(int));

    return predecessors;
}


bool* initializeMarks(int totalVertices) {
    
    bool* marks = new bool[totalVertices];

    memset(marks, false, totalVertices * sizeof(bool));

    return marks;
}


int* buildPredecessors(int startVertex, int endVertex, int** adjMatrix, int totalVertices) {

    int* predecessors = initializePredecessors(totalVertices);
    bool* marks = initializeMarks(totalVertices);

    bool endVertexAchieved = false;
    int currentVertex = startVertex;

    queue<int> q;
    q.push(currentVertex);
    marks[currentVertex] = true;

    while (!q.empty() && !endVertexAchieved) {
        currentVertex = q.front(); q.pop();
        for (int neighborVertex = 0; neighborVertex < totalVertices; neighborVertex++) {
            int neighborEdgeWeight = adjMatrix[currentVertex][neighborVertex];
            if (marks[neighborVertex] || neighborEdgeWeight == UNWEIGHTED_EDGE)
                continue;
            predecessors[neighborVertex] = currentVertex;
            if (neighborVertex == endVertex) {
                endVertexAchieved = true;
                break;
            }
            q.push(neighborVertex);
            marks[neighborVertex] = true;
        }
    }

    delete [] marks;
    
    return predecessors;
}


vector<int> buildPath(int startVertex, int endVertex, int** adjMatrix, int totalVertices) {

    vector<int> path;
    int* predecessors = buildPredecessors(startVertex, endVertex, adjMatrix, totalVertices);

    if (predecessors[endVertex] != NULL_VERTEX) {
        int currentVertex = endVertex;
        while (currentVertex != startVertex) {
            path.push_back(currentVertex);
            currentVertex = predecessors[currentVertex];
        }
        path.push_back(startVertex);
        reverse(path.begin(), path.end());
    }

    delete [] predecessors;

    return path;
}


int evaluateBottleneck(vector<int> &path, int** adjMatrix) {

    if (path.size() == 1)
        return adjMatrix[path[0]][path[0]];

    int bottleNeck = INT32_MAX;

    for (uint i = 0; i < path.size() - 1; i++) {
        int sourceVertex = path[i];
        int targetVertex = path[i+1];
        bottleNeck = min(bottleNeck, adjMatrix[sourceVertex][targetVertex]);
    }

    return bottleNeck;
}


void updateAdjacencyMatrix(int** adjMatrix, vector<int> path, int bottleNeck) {
    for (uint i = 0; i < path.size() - 1; i++) {
        int sourceVertex = path[i];
        int targetVertex = path[i+1];
        adjMatrix[sourceVertex][targetVertex] -= bottleNeck;
        adjMatrix[targetVertex][sourceVertex] += bottleNeck;
    }
}


int evaluateMaxNetworkFlow(int startVertex, int endVertex, int** adjMatrix, int totalVertices) {

    int maxFlow = 0;
    vector<int> path = buildPath(startVertex, endVertex, adjMatrix, totalVertices);

    while (path.size() > 0) {
        int bottleNeck = evaluateBottleneck(path, adjMatrix);
        updateAdjacencyMatrix(adjMatrix, path, bottleNeck);
        maxFlow += bottleNeck;
        path = buildPath(startVertex, endVertex, adjMatrix, totalVertices);
    }

    return maxFlow;
}


int main(void) {

    int totalVertices;
    cin >> totalVertices;

    int** adjMatrix = readAdjacencyMatrix(totalVertices);

    int startVertex, endVertex;
    cin >> startVertex >> endVertex;

    cout << evaluateMaxNetworkFlow(startVertex, endVertex, adjMatrix, totalVertices) << "\n";

    deleteAdjacencyMatrix(adjMatrix, totalVertices);

    return 0;
}
