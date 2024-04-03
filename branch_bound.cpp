#include <iostream>
#include <vector>
#include <limits>

using namespace std;
const int INF = numeric_limits<int>::max();

int n;  // Number of cities
vector<vector<int>> graph;  // Adjacency matrix representing the distances between cities
vector<int> bestPath;  // Stores the best path found so far
int bestCost = INF;  // Stores the cost of the best path found so far

void branchAndBound(int currentNode, int currentCost, vector<int>& path, vector<bool>& visited) {
    if (path.size() == n) {  
        // All cities visited, check if it forms a better path
        if (graph[currentNode][0] != 0 && currentCost + graph[currentNode][0] < bestCost) {
            bestCost = currentCost + graph[currentNode][0];
            bestPath = path;
            bestPath.push_back(0);
        }
        return;
    }

    for (int nextNode = 0; nextNode < n; ++nextNode) {
        if (!visited[nextNode] && graph[currentNode][nextNode] != 0) {
            visited[nextNode] = true;
            path.push_back(nextNode);

            // Calculate the lower bound by finding the minimum outgoing edge from the current node
            int lowerBound = currentCost + graph[currentNode][nextNode];

            if (lowerBound < bestCost) {  // Prune if the lower bound is worse than the best cost so far
                branchAndBound(nextNode, lowerBound, path, visited);
            }

            path.pop_back();
            visited[nextNode] = false;
        }
    }
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> n;

    // Initialize the graph with distances between cities
    graph.resize(n, vector<int>(n));
    cout << "Enter the adjacency matrix representing distances between cities:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    vector<int> path;
    path.push_back(0);  // Start with the first city

    vector<bool> visited(n, false);
    visited[0] = true;

    branchAndBound(0, 0, path, visited);

    cout << "Best TSP Path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;

    cout << "Best TSP Cost: " << bestCost << endl;

    return 0;
}
