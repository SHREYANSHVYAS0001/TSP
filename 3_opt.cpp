#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// Function to calculate the total distance of a given tour
double calculateDistance(const vector<int>& tour, const vector<vector<double>>& graph) {
    double distance = 0.0;
    int n = tour.size();

    for (int i = 0; i < n - 1; ++i) {
        int u = tour[i];
        int v = tour[i + 1];
        distance += graph[u][v];
    }

    int lastVertex = tour[n - 1];
    int firstVertex = tour[0];
    distance += graph[lastVertex][firstVertex];

    return distance;
}

// Function to perform the 3-opt swap
vector<int> perform3OptSwap(const vector<int>& tour, int i, int j, int k) {
    vector<int> newTour;

    // Take the segments before i, between i and j, between j and k, and after k
    for (int idx = 0; idx <= i; ++idx) {
        newTour.push_back(tour[idx]);
    }

    for (int idx = j; idx >= i + 1; --idx) {
        newTour.push_back(tour[idx]);
    }

    for (int idx = k; idx >= j + 1; --idx) {
        newTour.push_back(tour[idx]);
    }

    for (int idx = k + 1; idx < tour.size(); ++idx) {
        newTour.push_back(tour[idx]);
    }

    return newTour;
}

// Function to perform the 3-opt optimization
vector<int> perform3Opt( vector<int>& tour, const vector<vector<double>>& graph) {
    int n = tour.size();
    vector<int> bestTour = tour;
    double bestDistance = calculateDistance(tour, graph);

    bool improvement = true;
    while (improvement) {
        improvement = false;

        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    // Generate the new tour by performing the 3-opt swap
                    vector<int> newTour = perform3OptSwap(tour, i, j, k);

                    // Calculate the distance of the new tour
                    double newDistance = calculateDistance(newTour, graph);

                    // If the new distance is smaller, update the best tour and distance
                    if (newDistance < bestDistance) {
                        bestTour = newTour;
                        bestDistance = newDistance;
                        improvement = true;
                    }
                }
            }
        }

        tour = vector<int>(bestTour.begin(), bestTour.end()); // Update the current tour with the best tour
    }

    return bestTour;
}


int main() {
    // Define the adjacency matrix (graph) representing the distances between cities
    // vector<vector<double>> graph = {
    //     {0, 2, 9, 10},
    //     {1, 0, 6, 4},
    //     {15, 7, 0, 8},
    //     {6, 3, 12, 0}
    // };

    // // Define the initial tour (path)
    // vector<int> initialTour = {0, 1, 2, 3};

    vector<vector<double>> graph = {
        {0,12,10,19,8},
        {12,0,3,7,2},
        {10,3,0,6,20},
        {19,7,6,0,4},
        {8,2,20,4,0}
    };

    // Define the initial tour (path)
    vector<int> initialTour = {0,3,2,1,4};

    // Perform the 3-opt optimization
    vector<int> optimizedTour = perform3Opt(initialTour, graph);

    // Print the optimized tour
    cout << "Optimized Tour: ";
    for (int city : optimizedTour) {
        cout << city << " ";
    }
    cout << endl;

    // Calculate the total distance of the optimized tour
    double optimizedDistance = calculateDistance(optimizedTour, graph);
    cout << "Optimized Distance: " << optimizedDistance << endl;

    return 0;
}
