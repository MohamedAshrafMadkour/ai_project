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
    vector<int> allocated;
    int cost;
};

vector<Region> regions = {
    {"Hospital", 50, 2},
    {"Factory", 70, 3},
    {"Residential", 60, 1}
};

int capacity = 150;


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
    if (allSatisfied) return true;

    if (used >= capacity) return true;

    return false;
}

void BFS() {
    queue<State> q;
    set<vector<int>> visited;

    State start;
    start.allocated = { 0, 0, 0 };
    start.cost = 0;

    q.push(start);
    visited.insert(start.allocated);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int usedPower = 0;
        for (int x : current.allocated)
            usedPower += x;

        if (isGoal(current)) {
            cout << "\nBFS Power Distribution Result\n";
            cout << "----------------------------\n";
            for (int i = 0; i < regions.size(); i++) {
                cout << regions[i].name << " -> "
                    << current.allocated[i] << " / "
                    << regions[i].demand << endl;
            }
            cout << "Total Cost = " << current.cost << endl;
            return;
        }

        for (int i = 0; i < regions.size(); i++) {
            if (current.allocated[i] < regions[i].demand &&
                usedPower < capacity) {
                State next = current;
                next.allocated[i] += 1;
                next.cost += regions[i].cost;

                if (visited.find(next.allocated) == visited.end()) {
                    visited.insert(next.allocated);
                    q.push(next);
                }
            }
        }
    }
}

int main() {
    BFS();
    return 0;
}
