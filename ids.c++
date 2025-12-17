#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<string, int>>> graph;

bool DLS(string current, string goal, int limit,
         set<string> &visited, vector<string> &path)
{
    path.push_back(current);

    if (current == goal)
        return true;

    if (limit == 0) {
        path.pop_back();
        return false;
    }

    visited.insert(current);

    for (auto &neighbor : graph[current]) {
        string next = neighbor.first;
        if (!visited.count(next)) {
            if (DLS(next, goal, limit - 1, visited, path))
                return true;
        }
    }

    visited.erase(current);
    path.pop_back();
    return false;
}

void IDS(string start, string goal, int maxDepth)
{
    for (int depth = 0; depth <= maxDepth; depth++) {
        set<string> visited;
        vector<string> path;

        if (DLS(start, goal, depth, visited, path)) {
            for (auto &node : path)
                cout << node << " ";
            cout << endl;
            return;
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

    IDS("Station", "Goal", 5);
    return 0;
}
