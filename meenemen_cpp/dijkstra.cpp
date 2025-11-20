#include <limits.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits>

using namespace std;


// Print path from source to j using parent[]
void printPath(const vector<int>& parent, int j) {
    stack<int> path;
    int current = j;
    while (current != -1) {
        path.push(current);
        current = parent[current];
    }
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

// Print results
void printSolution(const vector<int>& dist, const vector<int>& parent) {
    cout << "Vertex\tDistance from Source\tPath\n";
    for (size_t i = 0; i < dist.size(); i++) {
        cout << i << "\t\t" << dist[i] << "\t\t\t";
        printPath(parent, (int)i);
    }
}

vector<int> dijkstra(const vector<vector<pair<int,int>>>& graph, int src) {
    size_t V = graph.size();
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);

    // Min-heap priority queue: (distance, vertex)
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Skip if this is already an outdated distance
        if (d > dist[u]) continue;

        // Explore neighbors
        for (auto &[v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    printSolution(dist, parent);
    // Optionally return parent if you need paths
    return dist;
}

int main() {
    // Convert your adjacency matrix into adjacency list form
/*
init adj list
        vector<vector<pair<int,int>>> adjList(n, vector<pair<int,int>>());

        int v1,v2, length;
        for (int i = 0; i < m; i++) {
            cin >> v1 >> v2 >> length;
            adjList.at(v1-1).push_back(make_pair(v2-1, length));
            adjList.at(v2-1).push_back(make_pair(v1-1, length));
        }

*/



    vector<vector<pair<int,int>>> adjList = {
        { {1,4}, {7,8} },                     // 0
        { {0,4}, {2,8}, {7,11} },             // 1
        { {1,8}, {3,7}, {5,4}, {8,2} },       // 2
        { {2,7}, {4,9}, {5,14} },             // 3
        { {3,9}, {5,10} },                    // 4
        { {2,4}, {3,14}, {4,10}, {6,2} },     // 5
        { {5,2}, {7,1}, {8,6} },              // 6
        { {0,8}, {1,11}, {6,1}, {8,7} },      // 7
        { {2,2}, {6,6}, {7,7} }               // 8
    };

    vector<int> dists = dijkstra(adjList, 0);

    return 0;
}
