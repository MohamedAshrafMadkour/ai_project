#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

struct Region {
    string name;
    int demand;
    int cost;
};

struct State {
    vector<int> allocation;
    int totalCost;
};

struct Compare {
    bool operator()(State a, State b) {
        return a.totalCost > b.totalCost;
    }
};

int calculateCost(const vector<int>& alloc, const vector<Region>& regions) {
    int cost = 0;
    for (int i = 0; i < alloc.size(); i++)
        cost += alloc[i] * regions[i].cost;
    return cost;
}

int main() {

    int capacity = 150;

    vector<Region> regions = {
        {"Hospital", 50, 2},
        {"Factory", 70, 3},
        {"Residential", 60, 1}
    };

    priority_queue<State, vector<State>, Compare> pq;
    State start;
    start.allocation = vector<int>(regions.size(), 0);
    start.totalCost = 0;

    pq.push(start);

    State best;
    best.totalCost = INT_MAX;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int used = 0;
        for (int x : current.allocation) used += x;

        if (used <= capacity) {
            bool goal = true;
            for (int i = 0; i < regions.size(); i++)
                if (current.allocation[i] < regions[i].demand)
                    goal = false;

            if (goal) {
                best = current;
                break;
            }
        }

        for (int i = 0; i < regions.size(); i++) {
            if (current.allocation[i] < regions[i].demand && used < capacity) {
                State next = current;
                next.allocation[i]++;
                next.totalCost = calculateCost(next.allocation, regions);
                pq.push(next);
            }
        }
    }

    cout << "UCS Result:\n";
    for (int i = 0; i < regions.size(); i++)
        cout << regions[i].name << " -> " << best.allocation[i] << endl;

    cout << "Total Cost: " << best.totalCost << endl;

    return 0;
}
