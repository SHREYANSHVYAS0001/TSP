#include <bits/stdc++.h>
using namespace std;

// Function to find the outdegree of start and end points in the MST
pair<int,int> findOutdegree(int start, int end, int V, vector<pair<int,int>> adj[]) {
    return {adj[start].size(), adj[end].size()};
}

// Function to compute the minimum spanning tree (MST) using Prim's algorithm
void spanningTree(int start, int V, vector<pair<int,int>> adj[], vector<pair<int,int>> mstEdges[], int &sum) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> vis(V, 0);
    
    pq.push({0, start}); // Start with the starting vertex
    sum = 0; // Initialize the sum of edge weights
    
    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();
        int node = it.second;
        int wt = it.first;
        
        if (vis[node] == 1) continue; // Skip if the node has already been visited
        
        vis[node] = 1; // Mark the node as visited
        sum += wt; // Add the weight of the edge to the sum
        
        // Traverse the adjacent vertices
        for (auto it : adj[node]) {
            int child = it.first;
            int edW = it.second;
            
            if (!vis[child]) {
                pq.push({edW, child}); // Push the edge to the priority queue
                mstEdges[node].push_back({child, edW}); // Store the edge in the MST
            }
        }
    }
}

int main() {
    int V = 4; // Number of vertices
    // cin>>V;
    vector<pair<int,int>> adj[V + 2]; // Adjacency list to store the graph

    // int q;
    // cin>>q;
    // for(int i=0;i<q;i++){
    //     int u,v,x;
    //     cin>>u>>v>>x;
    //     adj[u].push_back({v,x});
    // }

    // Adjacency matrix representing the graph
    int graph[][V] = { { 0, 10, 15, 20 },
                       { 10, 0, 35, 25 },
                       { 15, 35, 0, 30 },
                       { 20, 25, 30, 0 } };

    // Populate the adjacency list
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j] != 0) {
                adj[i].push_back({j, graph[i][j]});
            }
        }
    }

    int minwt = 1e9; // Initialize the minimum weight to a large value
    int optimalwt = 1e9; // Initialize the optimal weight to a large value
    bool optimal = false; // Initialize the flag for optimality

    // Iterate over all pairs of vertices
    for(int i = 0; i < V; i++) {
        for(int j = i + 1; j < V; j++) {
            int s = 0; // Initialize the sum of edge weights for the current pair
            int flag = 0; // Initialize the flag to check optimality

            // Compute the MST for the current pair of vertices
            vector<pair<int,int>> MST[V + 2];
            spanningTree(i, V, adj, MST, s);

            // Check for a direct edge between the start and end points
            for(auto it : adj[j]) {
                if(it.first == i) {
                    s += it.second;
                    flag = 1;
                    continue;
                }
            }

            // Check the outdegree of start and end points in the MST
            pair<int,int> check = findOutdegree(i, j, V, MST);

            if(check.first == 1 && check.second == 0) {
                flag++;
            }

            // Update minwt and optimalwt based on conditions
            if(flag > 0) {
                minwt = min(minwt, s);
            }
            if(flag > 1) {
                optimalwt = min(s, optimalwt);
            }
        }
    }

    // Check if the optimal and approximate solutions are the same
    if(optimalwt == minwt) {
        optimal = true;
    }

    // Output the result
    // if(optimal == false) {
        cout << "Approximate answer is " << minwt << endl;
    // } else {
        cout << "Optimal answer is " << optimalwt << endl;
    // }

    return 0;
}
