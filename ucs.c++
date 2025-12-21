#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>

using namespace std;

struct Region {
    string name;
    int demand;
    int cost;
};

struct State {
    vector<int> alloc;
    int totalCost;
};

struct Compare {
    bool operator()(const State& a, const State& b) const {
        return a.totalCost > b.totalCost;
    }
};

set<vector<int>> visited;

int main() {
    int capacity = 150;

    vector<Region> regions = {
        {"Hospital", 50, 2},
        {"Factory", 70, 3},
        {"Residential", 60, 1}
    };

    priority_queue<State, vector<State>, Compare> pq;

    State start;
    start.alloc = vector<int>(regions.size(), 0);
    start.totalCost = 0;

    pq.push(start);

    State best;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (visited.count(current.alloc))
            continue;

        visited.insert(current.alloc);

        int used = 0;
        for (int x : current.alloc)
            used += x;

        if (used == capacity) {
            best = current;
            break;
        }

        for (int i = 0; i < regions.size(); i++) {
            if (current.alloc[i] < regions[i].demand) {
                State next = current;
                next.alloc[i]++;
                next.totalCost += regions[i].cost;
                pq.push(next);
            }
        }
    }

    cout << "UCS Result:\n";
    for (int i = 0; i < regions.size(); i++)
        cout << regions[i].name << " -> " << best.alloc[i] << " units\n";

    cout << "Total Cost = " << best.totalCost << endl;

    return 0;
}
/* 
UCS Result:
Hospital -> 50 units
Factory -> 40 units
Residential -> 60 units
Total Cost = 280
*/
