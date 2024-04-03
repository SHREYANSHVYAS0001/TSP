#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int n;  // Number of cities
vector<vector<int>> graph;  // Adjacency matrix representing the distances between cities

// Greedy algorithm for TSP
vector<int> greedyTSP() {
    vector<int> tour;
    vector<bool> visited(n, false);

    // Start from the first city
    int currentCity = 0;
    tour.push_back(currentCity);
    visited[currentCity] = true;

    while (tour.size() < n) {
        int nextCity = -1;
        int minDistance = INF;

        // Find the nearest unvisited city
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && graph[currentCity][i] < minDistance) {
                minDistance = graph[currentCity][i];
                nextCity = i;
            }
        }

        if (nextCity != -1) {
            tour.push_back(nextCity);
            visited[nextCity] = true;
            currentCity = nextCity;
        }
    }

    return tour;
}

int calculateTourCost(const vector<int>& tour) {
    int cost = 0;
    int pathSize = tour.size();

    for (int i = 0; i < pathSize - 1; ++i) {
        int city1 = tour[i];
        int city2 = tour[i + 1];
        cost += graph[city1][city2];
    }

    int lastCity = tour[pathSize - 1];
    int firstCity = tour[0];
    cost += graph[lastCity][firstCity];

    return cost;
}

int main() {
    // Read the number of cities and adjacency matrix
    cout << "Enter the number of cities: ";
    cin >> n;

    graph.resize(n, vector<int>(n));
    cout << "Enter the adjacency matrix representing distances between cities:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    // Apply the greedy algorithm
    vector<int> tour = greedyTSP();

    // Print the tour
    cout << "Greedy TSP Tour: ";
    for (int city : tour) {
        cout << city << " ";
    }
    cout << endl;

    // Calculate and print the cost of the tour
    int tourCost = calculateTourCost(tour);
    cout << "Greedy TSP Cost: " << tourCost << endl;

    return 0;
}
