#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Region {
    string name;
    int demand;
    string priority;
    int cost;
    double score;
    int allocated;
};

int priorityWeight(const string& priority) {
    if (priority == "High") return 3;
    if (priority == "Medium") return 2;
    return 1; 
}

void greedyPowerDistribution(vector<Region>& regions, int capacity, int& totalCost) {

    totalCost = 0;

    for (int i = 0; i < regions.size(); i++) {
        regions[i].score = (double)priorityWeight(regions[i].priority) / regions[i].cost;
        regions[i].allocated = 0;
    }

    sort(regions.begin(), regions.end(),
        [](const Region& a, const Region& b) {
            return a.score > b.score;
        });

    for (int i = 0; i < regions.size(); i++) {
        if (capacity <= 0)
            break;

        int allocatedPower = min(regions[i].demand, capacity);
        regions[i].allocated = allocatedPower;
        capacity -= allocatedPower;

        totalCost += allocatedPower * regions[i].cost; 
    }
}

void printResult(const vector<Region>& regions, int totalCost) {
    cout << "Power Distribution Result (Greedy Algorithm)" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 0; i < regions.size(); i++) {
        cout << regions[i].name << " -> Allocated: "
             << regions[i].allocated << " / Demand: "
             << regions[i].demand << endl;
    }

    cout << "Total Cost: " << totalCost << endl;
}

int main() {

    int stationCapacity = 150;

    vector<Region> regions;
    regions.push_back({"Hospital", 50, "High", 2});
    regions.push_back({"Factory", 70, "Medium", 3});
    regions.push_back({"Residential", 60, "Low", 1});

    int totalCost = 0;
    greedyPowerDistribution(regions, stationCapacity, totalCost);
    printResult(regions, totalCost);

    return 0;
}
/*
Power Distribution Result (Greedy Algorithm)
-------------------------------------------
Hospital -> Allocated: 50 / Demand: 50
Residential -> Allocated: 60 / Demand: 60
Factory -> Allocated: 40 / Demand: 70
Total Cost: 280
*/
