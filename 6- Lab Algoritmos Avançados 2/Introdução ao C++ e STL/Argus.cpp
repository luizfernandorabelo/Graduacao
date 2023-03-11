#include <iostream>
#include <queue>

using namespace std;

struct Query {
    int id;
    int originalTime;
    int nextTime;
};

class Comparison {
public:
    bool operator() (Query a, Query b) {
        if (a.nextTime > b.nextTime)
            return true;
        if (a.nextTime == b.nextTime)
            return a.id > b.id;
        return false;
    }
};

typedef priority_queue<Query, vector<Query>, Comparison> pqueue;

Query readQuery() {
    Query q;
    cin >> q.id >> q.originalTime;
    q.nextTime = q.originalTime;
    return q;
}

void executeQueries(pqueue &queries, int totalExecutions) {
    for (int i = 0; i < totalExecutions; i++) {
        Query topQuery = queries.top(); queries.pop();
        cout << topQuery.id << "\n";
        topQuery.nextTime += topQuery.originalTime;
        queries.push(topQuery);
    }
}

int main(void) {

    pqueue queries;
    string command; cin >> command;

    while (command == "Register") {
        queries.push(readQuery());
        cin >> command;
    }

    int totalExecutions; cin >> totalExecutions;
    executeQueries(queries, totalExecutions);

    return 0;
}
