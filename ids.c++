#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Region {
    string name;
    int demand;
};

bool dfs(vector<int>& alloc, const vector<Region>& regions, int capacity, int depth, int limit) {

    if (depth == limit) {
        int sum = 0;
        for (int x : alloc) sum += x;
        if (sum > capacity) return false;

        for (int i = 0; i < regions.size(); i++)
            if (alloc[i] < regions[i].demand)
                return false;

        return true;
    }

    for (int i = 0; i < regions.size(); i++) {
        alloc[i]++;
        int used = 0;
        for (int x : alloc) used += x;

        if (used <= capacity) {
            if (dfs(alloc, regions, capacity, depth + 1, limit))
                return true;
        }
        alloc[i]--;
    }

    return false;
}

int main() {

    int capacity = 150;

    vector<Region> regions = {
        {"Hospital", 50},
        {"Factory", 70},
        {"Residential", 60}
    };

    vector<int> allocation(regions.size(), 0);

    for (int limit = 0; limit <= capacity; limit++) {
        if (dfs(allocation, regions, capacity, 0, limit)) {
            cout << "IDS Result:\n";
            for (int i = 0; i < regions.size(); i++)
                cout << regions[i].name << " -> " << allocation[i] << endl;
            break;
        }
    }

    return 0;
}
