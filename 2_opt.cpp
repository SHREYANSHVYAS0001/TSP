#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Calculates the cost of a given path in the TSP
int calculateCost(const vector<int>& path, const vector<vector<int>>& graph) {
    int cost = 0;
    int pathSize = path.size();

    for (int i = 0; i < pathSize - 1; ++i) {
        // city1 -> city2
        int city1 = path[i];
        int city2 = path[i + 1];
        cost += graph[city1][city2];
    }

    int lastCity = path[pathSize - 1];
    int firstCity = path[0];
    cost += graph[lastCity][firstCity];

    return cost;
}

// Performs the 2-opt optimization on a given path
vector<int> twoOpt(const vector<int>& initialPath, const vector<vector<int>>& graph) {
    int n = initialPath.size();
    vector<int> newPath = initialPath;
    bool improvement = true;

    while (improvement) {
        improvement = false;

        for (int i = 1; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // it creates reversed path for index i->j
                vector<int> reversedPath(newPath.begin() + i, newPath.begin() + j + 1);
                reverse(reversedPath.begin(), reversedPath.end());

                // original-reversed-original
                vector<int> newPathCandidate(newPath.begin(), newPath.begin() + i);
                newPathCandidate.insert(newPathCandidate.end(), reversedPath.begin(), reversedPath.end());
                newPathCandidate.insert(newPathCandidate.end(), newPath.begin() + j + 1, newPath.end());

                int currentCost = calculateCost(newPath, graph);
                int candidateCost = calculateCost(newPathCandidate, graph);

                if (candidateCost < currentCost) {
                    newPath = newPathCandidate;
                    improvement = true;
                }
            }
        }
    }

    return newPath;
}

int main() {
    // Example usage

    // Define the adjacency matrix representing distances between cities


    // vector<vector<int>> graph = {
    //     {0, 2, 9, 10},
    //     {1, 0, 6, 4},
    //     {15, 7, 0, 8},
    //     {6, 3, 12, 0}
    // };

    // // Define the initial path
    // vector<int> initialPath = {0,3,2,1};

    vector<vector<int>> graph = {
        {0,12,10,19,8},
        {12,0,3,7,2},
        {10,3,0,6,20},
        {19,7,6,0,4},
        {8,2,20,4,0}
    };

    // Define the initial path
    vector<int> initialPath = {0,3,2,1,4};



    // Apply 2-opt optimization
    vector<int> optimizedPath = twoOpt(initialPath, graph);

    // Print the optimized path
    cout << "Optimized Path: ";
    for (int city : optimizedPath) {
        cout << city << " ";
    }
    cout << endl;

    // Calculate the cost of the optimized path
    int optimizedCost = calculateCost(optimizedPath, graph);
    cout << "Optimized Cost: " << optimizedCost << endl;

    return 0;
}
