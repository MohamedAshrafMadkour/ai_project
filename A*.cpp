#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <climits> 

using namespace std;

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

int capacity = 150;


bool isGoal(const State& s) {
    int used = 0;
    for (int i = 0; i < s.allocated.size(); i++) {
        used += s.allocated[i];
        if (s.allocated[i] < regions[i].demand && used < capacity)
            return false;
    }
    return true;
}


int heuristic(const State& s) {
    int remaining = 0;
    int minCost = INT_MAX;

    for (int i = 0; i < regions.size(); i++) {
        remaining += max(0, regions[i].demand - s.allocated[i]);
        minCost = min(minCost, regions[i].cost);
    }
    return remaining * minCost;
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

        int usedPower = 0;
        for (int x : current.allocated)
            usedPower += x;

        if (isGoal(current)) {
            cout << "\nA* Power Distribution Result\n";
            cout << "----------------------------\n";
            for (int i = 0; i < regions.size(); i++) {
                cout << regions[i].name << " -> "
                     << current.allocated[i] << " / "
                     << regions[i].demand << endl;
            }
            cout << "Total Cost = " << current.g << endl;
            return;
        }

        closed.insert(current.allocated);

        for (int i = 0; i < regions.size(); i++) {

            if (current.allocated[i] < regions[i].demand &&
                usedPower < capacity) {

                State next = current;
                next.allocated[i] += 1;
                next.g = current.g + regions[i].cost;
                next.h = heuristic(next);
                next.f = next.g + next.h;

                if (closed.find(next.allocated) == closed.end()) {
                    open.push(next);
                }
            }
        }
    }
}

int main() {
    AStar();
    return 0;
}
