#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <string>
using namespace std;

struct Region {
    string name;
    int demand;
    int priority;
    int cost;
};

struct State {
    vector<int> allocated;
    int totalCost;
    int currentRegion;
};

vector<Region> regions = {
    {"Hospital", 50, 1, 2},
    {"Factory", 70, 2, 3},
    {"Residential", 60, 3, 1}
};

int capacity = 150;
int STEP_SIZE = 10;
int MAX_DEPTH = 50;

bool isGoal(const State& s) {
    int used = 0;
    for (int x : s.allocated)
        used += x;

    bool allSatisfied = true;
    for (int i = 0; i < s.allocated.size(); i++) {
        if (s.allocated[i] < regions[i].demand) {
            allSatisfied = false;
            break;
        }
    }

    return allSatisfied || (used >= capacity);
}

void DFS() {
    stack<State> stk;
    set<vector<int>> visited;

    State start;
    start.allocated = vector<int>(regions.size(), 0);
    start.totalCost = 0;
    start.currentRegion = 0;

    stk.push(start);
    visited.insert(start.allocated);

    State bestSolution = start;

    while (!stk.empty()) {
        State current = stk.top();
        stk.pop();

        int usedPower = 0;
        for (int x : current.allocated)
            usedPower += x;

        if (isGoal(current)) {
            bestSolution = current;
            break;
        }

        if (usedPower >= capacity) {
            continue;
        }

        int currentRegionIdx = current.currentRegion;

        if (currentRegionIdx < regions.size() &&
            current.allocated[currentRegionIdx] < regions[currentRegionIdx].demand) {

            State next = current;

            int toAllocate = min({
                STEP_SIZE,
                regions[currentRegionIdx].demand - current.allocated[currentRegionIdx],
                capacity - usedPower
                });

            next.allocated[currentRegionIdx] += toAllocate;
            next.totalCost += regions[currentRegionIdx].cost * toAllocate;

            if (next.allocated[currentRegionIdx] >= regions[currentRegionIdx].demand) {
                next.currentRegion = currentRegionIdx + 1;
            }

            if (visited.find(next.allocated) == visited.end()) {
                visited.insert(next.allocated);
                stk.push(next);
            }
        }
        else if (currentRegionIdx < regions.size()) {
            State next = current;
            next.currentRegion = currentRegionIdx + 1;

            if (visited.find(next.allocated) == visited.end()) {
                visited.insert(next.allocated);
                stk.push(next);
            }
        }
    }

    cout << "Power Distribution Result (DFS Algorithm)\n";
    cout << "-------------------------------------------\n";
    for (int i = 0; i < regions.size(); i++) {
        cout << regions[i].name << " -> Allocated: " << bestSolution.allocated[i]
            << " / Demand: " << regions[i].demand << endl;
    }
    cout << "Total Cost: " << bestSolution.totalCost << endl;
}

int main() {
    DFS();
    return 0;
}

/*
Power Distribution Result (DFS Algorithm)
-------------------------------------------
Hospital -> Allocated: 50 / Demand: 50
Factory -> Allocated: 70 / Demand: 70
Residential -> Allocated: 30 / Demand: 60
Total Cost: 340
*/
