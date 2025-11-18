#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <stdio.h>
#include <stack>
#include <cmath>
#include <tuple>
#include <queue>
#include <limits>

using namespace std;
// constexpr double M_E = 2.71828182845904523536;


// A C++ program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph

// Find vertex with minimum dist value



// Use adjacency list instead of matrix
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
    
    // Optionally return parent if you need paths
    return dist;
}


double compute_expected_value(vector<tuple<int,int>> dists_total_index, vector<double> kruidnoot_probs) {
    double res = 0;
    double cur_log_prob = 0;
    for (int i = 0; i < dists_total_index.size(); i++) {
        
        int cur_vector_index = get<1>(dists_total_index[i]);
        // cout << "cur_vector_index = " << cur_vector_index  << endl;
        if (kruidnoot_probs[cur_vector_index] > 0) {
            
            int cur_value = get<0>(dists_total_index[i]);
            double cur_prob = kruidnoot_probs.at(cur_vector_index);
            
            double total_cur_prob = cur_prob * pow(M_E, cur_log_prob);

            res += total_cur_prob*cur_value;
            // cout << "adding " << total_cur_prob << "*" << cur_value << " to res\n";
            
            cur_log_prob += log(1-cur_prob);
        }
    }
    
    return res;
}


int main() {
    try
{        int n, m, k;
        
        cin >> n >> m >> k;
        
        vector<vector<pair<int,int>>> adjList(n, vector<pair<int,int>>());

        int v1,v2, length;
        for (int i = 0; i < m; i++) {
            cin >> v1 >> v2 >> length;
            adjList.at(v1-1).push_back(make_pair(v2-1, length));
            adjList.at(v2-1).push_back(make_pair(v1-1, length));
        }
        int kruidnoot_index;
        vector<int> kruidnoot_indices_alone = {};
        vector<double> kruidnoot_probs(n, 0);
        double prob;
        bool have_seen_prob_1 = false;
        for (int j = 0; j < k; j++) {
            cin >> kruidnoot_index >> prob;
            if (prob == 1.0) {
                have_seen_prob_1 = true;
            }
            kruidnoot_probs.at(kruidnoot_index-1) = prob;
            kruidnoot_indices_alone.push_back(kruidnoot_index-1);
        }
        if (!have_seen_prob_1) {
            // no kruidnoten present has prob > 0
            cout << "impossible" << endl;
            return 0;
        }
        
        vector<int> dists1 = dijkstra(adjList, 0);
        
        vector<int> dists2 = dijkstra(adjList, n-1);

        
        vector<tuple<int,int>> dists_total_index = {};

        for (int i = 0; i < n; i++) {
            // v        this can be faster with a hashmap       v
            if (find(kruidnoot_indices_alone.begin(), kruidnoot_indices_alone.end(), i) != kruidnoot_indices_alone.end()) {
                // kruidnoot_indices_alone contains i, so we consider it
                dists_total_index.push_back(make_tuple(dists1[i] + dists2[i], i));
            }
        }
        
        sort(dists_total_index.begin(), dists_total_index.end());
        for (tuple<int,int> elt : dists_total_index) {
            // cout << "(" << get<0>(elt) << ", " << get<1>(elt) << ")\n";
        }
        double res = compute_expected_value(dists_total_index, kruidnoot_probs);
        cout << res << endl;
        return 0;}
        catch (const exception& e) {
            cerr << "exception: " << e.what() << endl;
            
        }
}

