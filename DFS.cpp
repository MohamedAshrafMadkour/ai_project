#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include<string>
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
int stepSize = 10; 
int nodesExplored = 0;


struct State {
    vector<int> distribution; 
    int cost;
    int depth;

    State(vector<int> dist, int c, int d) : distribution(dist), cost(c), depth(d) {}
};

string stateToString(const vector<int>& state) {
    string s = "";
    for (int val : state) {
        s += to_string(val) + ",";
    }
    return s;
}


int calculateCost(const vector<int>& distribution) {
    int totalPower = 0;
    int transmissionCost = 0;
    int penalty = 0;

    for (int i = 0; i < distribution.size(); i++) {
        totalPower += distribution[i];
        transmissionCost += distribution[i] * requirements[i].cost;

        
        if (distribution[i] < requirements[i].requiredAmount) {
            int unmet = requirements[i].requiredAmount - distribution[i];
            penalty += requirements[i].priority * unmet * 10;
        }
    }

    
    if (totalPower > allOfCapacity) {
        penalty += (totalPower - allOfCapacity) * 100;
    }

    return transmissionCost + penalty;
}


bool isGoalState(const vector<int>& distribution) {
    int totalPower = 0;
    for (int i = 0; i < distribution.size(); i++) {
        totalPower += distribution[i];
        
        if (requirements[i].priority == 3 &&
            distribution[i] < requirements[i].requiredAmount) {
            return false;
        }
    }
    return totalPower <= allOfCapacity;
}

vector<State> generateSuccessors(const State& current) {
    vector<State> successors;

    
    for (int i = requirements.size() - 1; i >= 0; i--) {
        vector<int> newDist = current.distribution;

        
        if (newDist[i] < requirements[i].requiredAmount + stepSize) {
            newDist[i] += stepSize;
            int newCost = calculateCost(newDist);
            successors.push_back(State(newDist, newCost, current.depth + 1));
        }
    }

    return successors;
}


vector<int> runDFS() {
    nodesExplored = 0;
    stack<State> frontier;
    set<string> visited;

    
    vector<int> initialDist(requirements.size(), 0);
    State initialState(initialDist, calculateCost(initialDist), 0);

    frontier.push(initialState);
    visited.insert(stateToString(initialDist));

    State bestState = initialState;
    int bestCost = initialState.cost;

    int maxDepth = 20; 

    while (!frontier.empty()) {
        State current = frontier.top();
        frontier.pop();
        nodesExplored++;

        
        if (current.cost < bestCost) {
            bestCost = current.cost;
            bestState = current;
        }

        
        if (isGoalState(current.distribution)) {
            cout << "Goal state reached at depth " << current.depth << endl;
            return current.distribution;
        }

        
        if (current.depth >= maxDepth) {
            continue;
        }

        
        vector<State> successors = generateSuccessors(current);
        for (const State& successor : successors) {
            string stateKey = stateToString(successor.distribution);
            if (visited.find(stateKey) == visited.end()) {
                visited.insert(stateKey);
                frontier.push(successor);
            }
        }
    }

    cout << "Search completed. Returning best state found.\n";
    return bestState.distribution;
}

int main() {
    cout << "=== Depth-First Search (DFS) ===" << endl;
    cout << "Station Capacity: " << allOfCapacity << " units\n";
    cout << "Step Size: " << stepSize << " units\n\n";

    vector<int> bestSolution = runDFS();

    cout << "\n=== Best Power Distribution (DFS) ===" << endl;
    int totalPower = 0;
    for (int i = 0; i < requirements.size(); i++) {
        cout << requirements[i].name << ": " << bestSolution[i] << " units";
        cout << " (Required: " << requirements[i].requiredAmount << ")";
        if (bestSolution[i] >= requirements[i].requiredAmount) {
            cout << " ?";
        }
        else {
            cout << " ? (Shortage: "
                << requirements[i].requiredAmount - bestSolution[i] << ")";
        }
        cout << endl;
        totalPower += bestSolution[i];
    }

    cout << "\nTotal Power Used: " << totalPower << "/" << allOfCapacity << endl;
    cout << "Total Cost: " << calculateCost(bestSolution) << endl;
    cout << "Nodes Explored: " << nodesExplored << endl;

    return 0;
}