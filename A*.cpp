#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

struct Region {
    string name;
    int demand;
    int cost;
};

struct State {
    vector<int> alloc;
    int gCost;   
    int fCost;   
};

struct Compare {
    bool operator()(const State& a, const State& b) const {
        return a.fCost > b.fCost;
    }
};

int heuristic(const vector<int>& alloc,
              const vector<Region>& regions,
              int capacity) {
    int used = 0;
    for (int x : alloc) used += x;

    int remaining = capacity - used;
    if (remaining <= 0) return 0;

    int minCost = regions[0].cost;
    for (const auto& r : regions)
        minCost = min(minCost, r.cost);

    return remaining * minCost;
}

int main() {
    int capacity = 150;

    vector<Region> regions = {
        {"Hospital", 50, 2},
        {"Factory", 70, 3},
        {"Residential", 60, 1}
    };

    priority_queue<State, vector<State>, Compare> pq;
    set<vector<int>> visited;

    State start;
    start.alloc = vector<int>(regions.size(), 0);
    start.gCost = 0;
    start.fCost = heuristic(start.alloc, regions, capacity);

    pq.push(start);

    State best;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (visited.count(current.alloc))
            continue;

        visited.insert(current.alloc);

        int used = 0;
        for (int x : current.alloc) used += x;

        if (used == capacity) {
            best = current;
            break;
        }

        for (int i = 0; i < regions.size(); i++) {
            if (current.alloc[i] < regions[i].demand) {
                State next = current;
                next.alloc[i]++;
                next.gCost += regions[i].cost;
                next.fCost = next.gCost +
                             heuristic(next.alloc, regions, capacity);
                pq.push(next);
            }
        }
    }

    cout << "A* Result:\n";
    for (int i = 0; i < regions.size(); i++)
        cout << regions[i].name << " -> "
             << best.alloc[i] << " units\n";

    cout << "Total Cost = " << best.gCost << endl;

    return 0;
}
/* 
A* Result:
Hospital -> 50 units
Factory -> 40 units
Residential -> 60 units
Total Cost = 280
*/
