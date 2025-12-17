#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<string, int>>> graph;

struct Node {
    string name;
    int cost;
    vector<string> path;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

void UCS(string start, string goal)
{
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<string> visited;

    pq.push({start, 0, {start}});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (visited.count(current.name))
            continue;

        visited.insert(current.name);

        if (current.name == goal) {
            for (auto &node : current.path)
                cout << node << " ";
            cout << current.cost << endl;
            return;
        }

        for (auto &neighbor : graph[current.name]) {
            string next = neighbor.first;
            int edgeCost = neighbor.second;

            if (!visited.count(next)) {
                auto newPath = current.path;
                newPath.push_back(next);
                pq.push({next, current.cost + edgeCost, newPath});
            }
        }
    }
}

int main()
{
    graph["Station"] = {{"A", 3}, {"B", 6}};
    graph["A"] = {{"C", 4}};
    graph["B"] = {{"C", 2}};
    graph["C"] = {{"Goal", 1}};
    graph["Goal"] = {};

    UCS("Station", "Goal");
    return 0;
}
