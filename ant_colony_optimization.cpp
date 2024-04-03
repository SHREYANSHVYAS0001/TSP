#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <limits>
#include <cmath>

using namespace std;

const int MAX_ITERATIONS = 100;  // Maximum number of iterations
const int ANT_COUNT = 10;        // Number of ants in each iteration
const double ALPHA = 1.0;        // Influence of pheromone trail
const double BETA = 2.0;         // Influence of heuristic information
const double RHO = 0.5;          // Pheromone trail evaporation rate

const int INF = numeric_limits<int>::max();

int n;  // Number of cities
vector<vector<int>> graph;  // Adjacency matrix representing the distances between cities

// Represents an ant that traverses the cities
struct Ant {
    vector<int> path;      // Stores the order of visited cities
    vector<bool> visited;  // Tracks the visited cities
    int cost;                   // Stores the cost of the tour

    Ant() : cost(INF) {
        visited.resize(n, false);
    }
};

// Calculates the visibility (heuristic) information for city i and j
double visibility(int i, int j) {
    return 1.0 / graph[i][j];
}

// Initializes the pheromone matrix with a default value
vector<vector<double>> initializePheromones() {
    return vector<vector<double>>(n, vector<double>(n, 1.0));
}

// Updates the pheromone matrix based on the ants' tours
void updatePheromones(vector<vector<double>>& pheromones, const vector<Ant>& ants) {
    // Evaporate pheromones
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pheromones[i][j] *= (1.0 - RHO);
        }
    }

    // Deposit pheromones
    for (const Ant& ant : ants) {
        int pathSize = ant.path.size();
        for (int i = 0; i < pathSize; ++i) {
            int currentCity = ant.path[i];
            int nextCity = ant.path[(i + 1) % pathSize];
            pheromones[currentCity][nextCity] += 1.0 / ant.cost;
            pheromones[nextCity][currentCity] += 1.0 / ant.cost;
        }
    }
}

// Selects the next city for an ant based on pheromone trails and visibility
int selectNextCity(int currentCity, const vector<bool>& visited, const vector<vector<double>>& pheromones) {
    double total = 0.0;
    vector<double> probabilities(n, 0.0);

    // Calculate the total probability
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            probabilities[i] = pow(pheromones[currentCity][i], ALPHA) * pow(visibility(currentCity, i), BETA);
            total += probabilities[i];
        }
    }

    // Select the next city based on probabilities
    random_device rd;
    // Mersenne Twister pseudo-random number generator. The rd() function call generates a random seed for the generator using the random device rd.
    mt19937 generator(rd());
    // uniform_real_distribution<double>;
        uniform_real_distribution<double> distribution(0.0, total);
    double randomValue = distribution(generator);



    // By accumulating the probabilities and comparing them with the random value, the algorithm selects the next city probabilistically. The higher the cumulative probability, the higher the chance of a city being selected. This process ensures that the selection is influenced by both the pheromone trail (pheromone information) and the visibility (heuristic information) factors.
    double cumulative = 0.0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            cumulative += probabilities[i];
            if (cumulative >= randomValue) {
                return i;
            }
        }
    }

    // Fallback to random selection if no city is selected
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            return i;
        }
    }

    return -1;  // Invalid city
}

// Constructs the initial solution for an ant
void constructSolution(Ant& ant, vector<vector<double>>& pheromones) {
    ant.path.clear();
    ant.visited.assign(n, false);
    ant.cost = 0;

    int initialCity = rand() % n;
    ant.path.push_back(initialCity);
    ant.visited[initialCity] = true;

    for (int i = 1; i < n; ++i) {
        int currentCity = ant.path.back();
        int nextCity = selectNextCity(currentCity, ant.visited, pheromones);
        ant.path.push_back(nextCity);
        ant.visited[nextCity] = true;
        ant.cost += graph[currentCity][nextCity];
    }

    int lastCity = ant.path.back();
    ant.cost += graph[lastCity][initialCity];
}

// Performs the ant colony optimization algorithm
vector<int> solveTSP() {
    // Set a random seed(initial value of random) for randomness
    srand(static_cast<unsigned>(time(0))); 

    vector<vector<double>> pheromones = initializePheromones();
    vector<Ant> ants(ANT_COUNT);

    vector<int> bestTour;
    int bestCost = INF;

    for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
        for (int i = 0; i < ANT_COUNT; ++i) {
            constructSolution(ants[i], pheromones);
            if (ants[i].cost < bestCost) {
                bestCost = ants[i].cost;
                bestTour = ants[i].path;
            }
        }

        updatePheromones(pheromones, ants);
    }

    return bestTour;
}

int calculateCost(const vector<int>& path) {
    int cost = 0;
    int pathSize = path.size();

    for (int i = 0; i < pathSize - 1; ++i) {
        int city1 = path[i];
        int city2 = path[i + 1];
        cost += graph[city1][city2];
    }

    int lastCity = path[pathSize - 1];
    int firstCity = path[0];
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

    vector<int> bestTour = solveTSP();

    // Print the best tour
    cout << "Best tour: ";
    for (int city : bestTour) {
        cout << city << " ";
    }
    cout << endl;

    cout << "Best TSP Cost: " << calculateCost(bestTour) << endl;

    return 0;
}

