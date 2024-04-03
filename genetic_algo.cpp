#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

const int POPULATION_SIZE = 100;  // Number of individuals in each generation
const int MAX_GENERATIONS = 100;  // Maximum number of generations
const double MUTATION_RATE = 0.1;  // Probability of mutation

const int INF = numeric_limits<int>::max();

int n;  // Number of cities
vector<vector<int>> graph;  // Adjacency matrix representing the distances between cities

// Represents an individual (tour) in the population
struct Individual {
    vector<int> path;  // Stores the order of cities in the tour
    int cost;  // Stores the cost of the tour

    Individual() : cost(INF) {}

    Individual(const vector<int>& newPath, int newCost) : path(newPath), cost(newCost) {}
};

// Generates a random permutation of cities as an initial individual
vector<int> generateRandomPath() {
    vector<int> path(n);
    for (int i = 0; i < n; ++i) {
        path[i] = i;
    }
    random_shuffle(path.begin() + 1, path.end());
    return path;
}

// Calculates the total cost of a tour
int calculateCost(const vector<int>& path) {
    int totalCost = 0;
    for (int i = 0; i < n; ++i) {
        int currentCity = path[i];
        int nextCity = path[(i + 1) % n];
        totalCost += graph[currentCity][nextCity];
    }
    return totalCost;
}

// Performs crossover between two parent individuals to create a child individual
Individual crossover(const Individual& parent1, const Individual& parent2) {
    vector<int> childPath(n, -1);
    int startPos = rand() % n;
    int endPos = rand() % n;

    for (int i = startPos; i <= endPos; ++i) {
        childPath[i] = parent1.path[i];
    }

    int currentPos = (endPos + 1) % n;
    for (int i = 0; i < n; ++i) {
        // this part of the code ensures that the child individual created during crossover receives cities from parent2 that are not already present in the childPath. It helps to maintain diversity in the population and avoid duplicate cities in the tour.

        if (find(childPath.begin(), childPath.end(), parent2.path[i]) == childPath.end()) {
            childPath[currentPos] = parent2.path[i];
            currentPos = (currentPos + 1) % n;
        }
    }

    return Individual(childPath, calculateCost(childPath));
}

// Mutates an individual by swapping two cities in the tour

// The mutate function mutates an individual by swapping two cities in the tour. It iterates through the cities, excluding the first city, and with a probability determined by MUTATION_RATE, it randomly selects another city to swap with. The cost of the individual is updated after the mutation. This introduces variations in the tour and allows the algorithm to explore different solutions in the search space.

void mutate(Individual& individual) {
    for (int i = 1; i < n; ++i) {
        if (rand() < MUTATION_RATE * RAND_MAX) {
            int j = rand() % (n - 1) + 1;
            swap(individual.path[i], individual.path[j]);
        }
    }
    individual.cost = calculateCost(individual.path);
}

// Selects a parent individual for reproduction using tournament selection
Individual tournamentSelection(const vector<Individual>& population) {
    const int TOURNAMENT_SIZE = 5;
    vector<Individual> tournament(TOURNAMENT_SIZE);

    // The random index generation is simply used to choose which individuals participate in the tournament, while the comparison of costs is performed later to determine the winner.

    for (int i = 0; i < TOURNAMENT_SIZE; ++i) {
        int randomIndex = rand() % POPULATION_SIZE;
                tournament[i] = population[randomIndex]; // take individual at randomIndex
    }

    auto compareByCost = [](const Individual& ind1, const Individual& ind2) {
        return ind1.cost < ind2.cost;
    };

    // Select the individual with the lowest cost from the tournament
    return *min_element(tournament.begin(), tournament.end(), compareByCost);
}

// Main Genetic Algorithm function
void geneticAlgorithm() {
    // Generate an initial population
    vector<Individual> population(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        population[i].path = generateRandomPath();
        population[i].cost = calculateCost(population[i].path);
    }

    // Sort the population based on cost
    auto compareByCost = [](const Individual& ind1, const Individual& ind2) {
        return ind1.cost < ind2.cost;
    };
    sort(population.begin(), population.end(), compareByCost);

    int generation = 0;
    while (generation < MAX_GENERATIONS) {
        vector<Individual> newPopulation;

        // Elitism: Keep the best individual from the previous generation
        newPopulation.push_back(population[0]);

        // Generate the rest of the new population through selection, crossover, and mutation
        while (newPopulation.size() < POPULATION_SIZE) {
            Individual parent1 = tournamentSelection(population);
            Individual parent2 = tournamentSelection(population);
            Individual child = crossover(parent1, parent2);
            mutate(child);
            newPopulation.push_back(child);
        }

        // Sort the new population based on cost
        sort(newPopulation.begin(), newPopulation.end(), compareByCost);

        population = newPopulation;
        ++generation;
    }

    // Display the best individual (tour) found
    cout << "Best TSP Path: ";
    for (int city : population[0].path) {
        cout << city << " ";
    }
    cout << endl;

    cout << "Best TSP Cost: " << population[0].cost << endl;
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

    // Set a random seed for randomness
    srand(static_cast<unsigned>(time(nullptr)));

    // Run the Genetic Algorithm
    geneticAlgorithm();

    return 0;
}

