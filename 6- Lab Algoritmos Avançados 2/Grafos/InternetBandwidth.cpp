#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define NULL_VERTEX -1
#define UNWEIGHTED_EDGE 0

using namespace std;

typedef vector<vector<int>> AdjMatrix;


AdjMatrix readAdjacencyMatrix(int totalVertices, int totalEdges) {

    AdjMatrix adjMatrix(totalVertices, vector<int>(totalVertices, UNWEIGHTED_EDGE));

    for (int i = 0; i < totalEdges; i++) {
        int sourceVertex, targetVertex, weight;
        cin >> sourceVertex >> targetVertex >> weight;
        adjMatrix[sourceVertex-1][targetVertex-1] += weight;
        adjMatrix[targetVertex-1][sourceVertex-1] += weight;
    }

    return adjMatrix;
}


vector<int> buildPredecessors(int startVertex, int endVertex, const AdjMatrix &adjMatrix, int totalVertices) {

    vector<int> predecessors(totalVertices, NULL_VERTEX);
    vector<bool> marks(totalVertices, false);

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

    return predecessors;
}


vector<int> buildPath(int startVertex, int endVertex, const AdjMatrix &adjMatrix, int totalVertices) {

    vector<int> path, predecessors = buildPredecessors(startVertex, endVertex, adjMatrix, totalVertices);

    if (predecessors[endVertex] != NULL_VERTEX) { 
        int currentVertex = endVertex;
        while (currentVertex != startVertex) {
            path.push_back(currentVertex);
            currentVertex = predecessors[currentVertex];
        }
        path.push_back(startVertex);
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


int evaluateMaxNetworkFlow(int startVertex, int endVertex, AdjMatrix &adjMatrix, int totalVertices) {

    int maxFlow = 0;
    vector<int> path = buildPath(startVertex, endVertex, adjMatrix, totalVertices);

    while (path.size() > 0) {
        int bottleNeck = evaluateBottleNeck(path, adjMatrix);
        updateAdjacencyMatrix(adjMatrix, path, bottleNeck);
        maxFlow += bottleNeck;
        path = buildPath(startVertex, endVertex, adjMatrix, totalVertices);
    }

    return maxFlow;
}


int main(void) {

    int totalVertices, startVertex, endVertex, totalEdges;

    for (int network = 1; cin >> totalVertices >> startVertex >> endVertex >> totalEdges; network++) {
        AdjMatrix adjMatrix = readAdjacencyMatrix(totalVertices, totalEdges);
        int bandwidth = evaluateMaxNetworkFlow(startVertex - 1, endVertex - 1, adjMatrix, totalVertices);
        cout << "Network " << network << "\nThe bandwidth is " << bandwidth << ".\n\n";
    }

    return 0;
}
