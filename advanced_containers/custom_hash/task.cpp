#include "task.h"

using namespace std;

void PopulateHashMap(
        unordered_map<SuperKey, string>& hashMap,
        const vector<pair<SuperKey, string>>& toAdd
) {
    for(auto el : toAdd)
        hashMap[el.first] = el.second;
}