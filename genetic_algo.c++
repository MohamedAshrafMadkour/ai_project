#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Requirement {
    string name;
    int requiredAmount;
    int priority;
    int cost;
};

vector<Requirement> requirements = {
    {"Hospital", 50, 3, 2},
    {"Factory", 70, 2, 3},
    {"Residential", 60, 1, 1}
};

int allOfCapacity = 150;
int populationSize = 20;
int generations = 50;
double mutationRate = 0.1;

vector<int> generateRandomSolution() {
    vector<int> solution;
    for (int i = 0; i < requirements.size(); i++) {
        solution.push_back(rand() % (requirements[i].requiredAmount + 1));
    }
    return solution;
}

vector<vector<int>> initializePopulation() {
    vector<vector<int>> population;
    if (populationSize < 2) {
        cout << "Population size must be at least 2\n";
        return population;
    }
    for (int i = 0; i < populationSize; i++) {
        population.push_back(generateRandomSolution());
    }
    return population;
}

int calculateFitness(const vector<int>& chromosome) {
    int populationSolutionPower = 0;
    int populationSolutionCost = 0;
    int penalty = 0;
    for (int i = 0; i < chromosome.size(); i++) {
        populationSolutionPower += chromosome[i];
        populationSolutionCost += chromosome[i] * requirements[i].cost;
        if (chromosome[i] < requirements[i].requiredAmount) {
            penalty += requirements[i].priority *
                       (requirements[i].requiredAmount - chromosome[i]);
        }
    }
    if (populationSolutionPower > allOfCapacity) {
        penalty += (populationSolutionPower - allOfCapacity) * 10;
    }
    int fitness = populationSolutionCost + penalty;
    return -fitness;
}

pair<vector<int>, vector<int>> selectBestParents(
    vector<vector<int>>& population) {
    sort(population.begin(), population.end(),
        [](const vector<int>& a, const vector<int>& b) {
            return calculateFitness(a) > calculateFitness(b);
        });
    return { population[0], population[1] };
}

pair<vector<int>, vector<int>> performCrossover(
    const vector<int>& parent1,
    const vector<int>& parent2) {
    int crossoverPoint = rand() % (parent1.size() - 1) + 1;
    vector<int> child1, child2;
    for (int i = 0; i < parent1.size(); i++) {
        if (i < crossoverPoint) {
            child1.push_back(parent1[i]);
            child2.push_back(parent2[i]);
        } else {
            child1.push_back(parent2[i]);
            child2.push_back(parent1[i]);
        }
    }
    return { child1, child2 };
}

void applyMutation(vector<int>& chromosome) {
    int index = rand() % chromosome.size();
    int change = rand() % 11 - 5;
    chromosome[index] = max(0, chromosome[index] + change);
}

vector<int> runGeneticAlgorithm() {
    vector<vector<int>> population = initializePopulation();
    for (int gen = 0; gen < generations; gen++) {
        vector<vector<int>> newPopulation;
        while (newPopulation.size() < populationSize) {
            auto [parent1, parent2] = selectBestParents(population);
            auto [child1, child2] = performCrossover(parent1, parent2);
            if ((rand() / double(RAND_MAX)) < mutationRate)
                applyMutation(child1);
            if ((rand() / double(RAND_MAX)) < mutationRate)
                applyMutation(child2);
            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }
        population = newPopulation;
    }

    return *max_element(population.begin(), population.end(),
        [](const vector<int>& a, const vector<int>& b) {
            return calculateFitness(a) < calculateFitness(b);
        });
}

// دالة لحساب التكلفة الإجمالية
int calculateTotalCost(const vector<int>& solution) {
    int totalCost = 0;
    for (int i = 0; i < solution.size(); i++) {
        totalCost += solution[i] * requirements[i].cost;
    }
    return totalCost;
}

int main() {
    srand(time(0));
    vector<int> bestSolution = runGeneticAlgorithm();
    
    cout << "Best Power Distribution:\n";
    for (int i = 0; i < requirements.size(); i++) {
        cout << requirements[i].name << ": "
             << bestSolution[i] << " units\n";
    }

    cout << "Fitness Value: "
         << calculateFitness(bestSolution) << endl;

    int totalCost = calculateTotalCost(bestSolution);
    cout << "Total Cost: " << totalCost << endl;

    return 0;
}

/* 
Best Power Distribution:
Hospital: 50 units
Factory: 0 units
Residential: 40 units
Fitness Value: -300
Total Cost: 140
    */
