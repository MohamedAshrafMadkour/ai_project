#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

const int STEP = 5;

struct Region {
    string name;
    int demand;
    int cost;
};

struct State {
    vector<int> allocated;
    int g;
    int h;
    int f;

    bool operator<(const State& other) const {
        return f > other.f; 
    }
};

vector<Region> regions = {
    {"Hospital", 50, 2},
    {"Factory", 70, 3},
    {"Residential", 60, 1}
};

int capacity = 180;

bool isGoal(const State& s) {
    int used = 0;
    for (int x : s.allocated)
        used += x;
    return used == capacity;
}

int heuristic(const State& s) {
    int h = 0;
    for (int i = 0; i < regions.size(); i++) {
        int remaining = max(0, regions[i].demand - s.allocated[i]);
        h += remaining * regions[i].cost;
    }
    return h;
}

void AStar() {

    priority_queue<State> open;
    set<vector<int>> closed;

    State start;
    start.allocated = {0, 0, 0};
    start.g = 0;
    start.h = heuristic(start);
    start.f = start.g + start.h;

    open.push(start);

    while (!open.empty()) {

        State current = open.top();
        open.pop();

        if (closed.count(current.allocated))
            continue;

        closed.insert(current.allocated);

        if (isGoal(current)) {
            cout << "Power Distribution Result (A* Algorithm)\n";
            cout << "----------------------------------------\n";

            for (int i = 0; i < regions.size(); i++) {
                cout << regions[i].name << " -> Allocated: "
                     << current.allocated[i] << " / Demand: "
                     << regions[i].demand << endl;
            }

            cout << "Total Cost = " << current.g << endl;
            return;
        }

        int usedPower = 0;
        for (int x : current.allocated)
            usedPower += x;

        for (int i = 0; i < regions.size(); i++) {

            if (current.allocated[i] < regions[i].demand &&
                usedPower + STEP <= capacity) {

                State next = current;
                next.allocated[i] += STEP;

                if (next.allocated[i] > regions[i].demand)
                    continue;

                next.g = current.g + STEP * regions[i].cost;
                next.h = heuristic(next);
                next.f = next.g + next.h;

                if (!closed.count(next.allocated)) {
                    open.push(next);
                }
            }
        }
    }

    cout << "No solution found.\n";
}
int main() {
    AStar();
    return 0;
}
/*     the output
    Power Distribution Result (A* Algorithm)
----------------------------------------
Hospital -> Allocated: 50 / Demand: 50
Factory -> Allocated: 70 / Demand: 70
Residential -> Allocated: 60 / Demand: 60
Total Cost = 370
    */
