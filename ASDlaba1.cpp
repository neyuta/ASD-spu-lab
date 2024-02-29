#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void topoDfs(int v, vector<bool>& visited, stack<int>& s) {
        visited[v] = true;

        for (int u : adjList[v]) {
            if (!visited[u]) {
                topoDfs(u, visited, s);
            }
        }

        s.push(v);
    }

    void topologicalSort() {
        stack<int> s;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                topoDfs(i, visited, s);
            }
        }

        vector<int> topoSort;
        while (!s.empty()) {
            topoSort.push_back(s.top());
            s.pop();
        }

        cout << "Topological sort order: ";
        for (int vertex : topoSort) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    void calculateEarlyAndLateStart() {
        vector<int> earlyStart(V, 0);
        vector<int> lateStart(V, INT_MAX);

        topologicalSort();

        earlyStart[0] = 0;
        for (int v : adjList[0]) {
            earlyStart[v] = 1;
        }

        for (int i = 0; i < V; ++i) {
            for (int v : adjList[i]) {
                earlyStart[v] = max(earlyStart[v], earlyStart[i] + 1);
            }
        }

        reverse(adjList.begin(), adjList.end());

        lateStart[V - 1] = earlyStart[V - 1];
        for (int i = V - 1; i >= 0; --i) {
            for (int v : adjList[i]) {
                lateStart[i] = min(lateStart[i], lateStart[v] - 1);
            }
        }

        cout << "Early start times: ";
        for (int es : earlyStart) {
            cout << es << " ";
        }
        cout << endl;

        cout << "Late start times: ";
        for (int ls : lateStart) {
            cout << ls << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.calculateEarlyAndLateStart();

    return 0;
}