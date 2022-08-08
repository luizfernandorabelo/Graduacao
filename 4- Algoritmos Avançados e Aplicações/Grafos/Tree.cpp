// SUB: (⊙_◎) ? means poor input treatment

#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <unordered_map>

#define EMPTY_CODE -1 // (⊙_◎) ?

using namespace std;

typedef long long int llint;
typedef pair<int, list<int>> Vertex;
typedef vector<Vertex> Graph;


Graph readGraph() {

    unordered_map<llint, int> vertices;
    Graph graph; 

    llint startVertex = 0, endVertex = 0;
    int totalVertices = 0;

    do {
        cin >> startVertex >> endVertex;
        if (startVertex <= -1)
            return graph;
        if (vertices.find(startVertex) == vertices.end()) {
            vertices.insert({startVertex, totalVertices});
            list<int> adjList;
            graph.push_back({totalVertices++, adjList});
        }
        if (vertices.find(endVertex) == vertices.end()) {
            vertices.insert({endVertex, totalVertices});
            list<int> adjList;
            graph.push_back({totalVertices++, adjList});
        }
        int mapedStartVertex = vertices[startVertex], mapedEndVertex = vertices[endVertex];
        graph[mapedStartVertex].second.push_back(mapedEndVertex);
    } while (startVertex > 0);

    if (startVertex == 0 && graph.size() > 1) // (⊙_◎) ?
        graph.erase(graph.end() - 1);
    else
        graph[0].first = EMPTY_CODE; // (⊙_◎) ?

    return graph;
}


bool isInvalidSubtree(Graph &graph, int currentVertex, bool* marks) {

    marks[currentVertex] = true;

    list<int> adjacencyList = graph[currentVertex].second;

    for (list<int>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        int neighbor = *it;
        if (marks[neighbor] || isInvalidSubtree(graph, neighbor, marks))
            return true;
    }

    return false;
}


bool isGraphTree(Graph &graph) {

    if (graph[0].first == EMPTY_CODE) // (⊙_◎) ?
        return true;

    bool* marks = (bool*) malloc(graph.size() * sizeof(bool));
    
    for (uint i = 0; i < graph.size(); i++) {
        memset(marks, false, graph.size() * sizeof(bool));
        if (isInvalidSubtree(graph, i, marks))
            return false;
        bool allReachable = true;
        for (uint j = 0; j < graph.size(); j++) {
            if (!marks[j]) {
                allReachable = false;
                break;
            }
        }
        if (allReachable)
            return true;
    }

    return false;
}


int main(void) {

    Graph graph = readGraph();

    for (int i = 0; graph.size() > 0; i++) {
        if (isGraphTree(graph))
            cout << "Case " << i + 1 << " is a tree.\n";
        else
            cout << "Case " << i + 1 << " is not a tree.\n";
        graph = readGraph();
    }

    return 0;
}