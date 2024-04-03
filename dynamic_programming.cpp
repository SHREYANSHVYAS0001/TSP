#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
// const int INF = numeric_limits<int>::max();
const int INF = 1000000000;


int tspDynamicProgramming(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    int numSubsets = 1 << n;
    vector<vector<int>> dp(numSubsets, vector<int>(n, INF));

    // Base case: starting point to itself
    dp[1 << start][start] = 0;

    // Iterate over all subsets of cities
    for (int subset = 1; subset < numSubsets; ++subset) {
        // the city to which it travels 
        for (int cur = 0; cur < n; ++cur) { 
            // it checks whether cur belongs to subset 
            if ((subset & (1 << cur)) != 0) {
                // prev is the previous city from which salesman comes to cur city
                for (int prev = 0; prev < n; ++prev) {
                    if (prev != cur && (subset & (1 << prev)) != 0) {
                        dp[subset][cur] = min(dp[subset][cur],
                         graph[prev][cur] + dp[subset ^ (1 << cur)][prev]);
                    }
                }
            }
        }
    }

    // Find the minimum cost of returning to the starting city
    int minCost = INF;
    for (int i = 0; i < n; ++i) {
        if (i != start) {
            //it indicates all cities are visited and from i to start i.e the last move
            minCost = min(minCost, graph[i][start] + dp[numSubsets - 1][i]);
        }
    }

    return minCost;
}

int main() {
    // Example usage

    // Define the graph with edge weights
    // vector<vector<int>> graph = {
    //     {0, 10, 15, 20},
    //     {10, 0, 35, 25},
    //     {15, 35, 0, 30},
    //     {20, 25, 30, 0}
    // };
    vector<vector<int>> graph = {
        {0,12,10,19,8},
        {12,0,3,7,2},
        {10,3,0,6,20},
        {19,7,6,0,4},
        {8,2,20,4,0}
    };


    // Starting city
    int start = 0;

    // Calculate the minimum cost of the TSP tour using dynamic programming
    int minCost = tspDynamicProgramming(graph, start);

    // Print the result
    cout << "Minimum Cost TSP Tour: " << minCost << endl;

    return 0;
}
