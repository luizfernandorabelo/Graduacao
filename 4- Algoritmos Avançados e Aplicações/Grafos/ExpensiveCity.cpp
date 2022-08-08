#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <queue>

#define IMPOSSIBLE_TRAVEL -1

using namespace std;

typedef pair<int, int> Edge;
typedef list<Edge> AdjacencyList;
typedef pair<int, AdjacencyList> Vertex;
typedef vector<Vertex> Graph;
typedef priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> MinPriorityQueue;


pair<Graph,int> readGraphAndStartVertexId(int totalVertices, int totalEdges) {

    Graph graph;
    unordered_map<string, int> stationMap;
    string stationName1, stationName2;
    int stationCode1, stationCode2, cost;

    for (int i = 0; i < totalVertices; i++) {
        cin >> stationName1;
        stationMap.insert({stationName1, i});
        graph.push_back({i, AdjacencyList()});
    }

    for (int i = 0; i < totalEdges; i++) {
        cin >> stationName1 >> stationName2 >> cost;
        stationCode1 = stationMap[stationName1];
        stationCode2 = stationMap[stationName2];
        graph[stationCode1].second.push_back({cost, stationCode2});
        graph[stationCode2].second.push_back({cost, stationCode1});
    }

    cin >> stationName1;

    return {graph, stationMap[stationName1]};
}


void insertAdjacentVerticesToPriorityQueue(Graph &graph, MinPriorityQueue &pqueue,
                                           int currentVertexId, bool* marks)
{
    marks[currentVertexId] = true;

    AdjacencyList adjList = graph[currentVertexId].second;

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        int edgeWeight = (*it).first, neighborId = (*it).second;
        if (!marks[neighborId])
            pqueue.push({edgeWeight,neighborId});
    }
}


int evaluateMinimumMonthlyPrice(Graph &graph, int startVertexId) {

    MinPriorityQueue pqueue;
    bool* marks = (bool*) calloc(graph.size(), sizeof(bool));
    uint totalInserted = 1, minCost = 0;

    insertAdjacentVerticesToPriorityQueue(graph, pqueue, startVertexId, marks);

    while (!pqueue.empty() && totalInserted != graph.size()) {
        Edge frontEdge = pqueue.top(); pqueue.pop();
        int frontEdgeWeight = frontEdge.first, frontEdgeNeighbor = frontEdge.second;
        if (!marks[frontEdgeNeighbor]) {
            minCost += frontEdgeWeight;
            insertAdjacentVerticesToPriorityQueue(graph, pqueue, frontEdgeNeighbor, marks);
            totalInserted++;
        }
    }


    if (totalInserted != graph.size())
        return IMPOSSIBLE_TRAVEL;

    return minCost;
}


int main(void) {

    int totalVertices, totalEdges;
    cin >> totalVertices >> totalEdges;

    while (totalVertices > 0) {
        pair<Graph,int> input = readGraphAndStartVertexId(totalVertices, totalEdges);
        int mmp = evaluateMinimumMonthlyPrice(input.first, input.second);
        if (mmp != IMPOSSIBLE_TRAVEL)
            cout << mmp << "\n";
        else
            cout << "Impossible\n";
        cin >> totalVertices >> totalEdges;
    }

    return 0;
}