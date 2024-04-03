#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int n;  // Number of cities
vector<vector<int>> graph;  // Adjacency matrix representing the distances between cities

vector<int> nearestNeighborTSP(int startCity) {
    vector<int> tour;  // Stores the order of visited cities
    vector<bool> visited(n, false);  // Tracks the visited cities
    tour.push_back(startCity);  // Start with the specified start city
    visited[startCity] = true;

    while (tour.size() < n) {
        int currentCity = tour.back();
        int nextCity = -1;
        int minDistance = INF;

        // Find the nearest unvisited city
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && graph[currentCity][i] < minDistance) {
                minDistance = graph[currentCity][i];
                nextCity = i;
            }
        }

        // Visit the nearest unvisited city
        tour.push_back(nextCity);
        visited[nextCity] = true;
    }

    return tour;
}

int calculateCost(const vector<int>& tour) {
    int cost = 0;
    int tourSize = tour.size();

    for (int i = 0; i < tourSize - 1; ++i) {
        int city1 = tour[i];
        int city2 = tour[i + 1];
        cost += graph[city1][city2];
    }

    int lastCity = tour[tourSize - 1];
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

    // Choose a start city (e.g., 0)
    int startCity = 0;

    // Find the tour using the nearest neighbor algorithm
    vector<int> tour = nearestNeighborTSP(startCity);

    // Print the tour
    cout << "TSP Tour: ";
    for (int city : tour) {
        cout << city << " ";
    }
    cout << endl;

    // Calculate and print the tour cost
    int cost = calculateCost(tour);
    cout << "TSP Cost: " << cost << endl;

    return 0;
}
