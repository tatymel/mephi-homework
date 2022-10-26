#include "task.h"

bool operator <(const SuperKey& lhs, const SuperKey& rhs) {
    if(lhs.StrPart > rhs.StrPart)
        return false;
    if(lhs.StrPart < rhs.StrPart)
        return true;
    if(lhs.IntPart > rhs.IntPart)
        return false;
    if(lhs.IntPart < rhs.IntPart)
        return true;
    if(lhs.FloatPart > rhs.FloatPart)
        return false;
    if(lhs.FloatPart < rhs.FloatPart)
        return true;
    return false;
}

void PopulateMap(
    std::map<SuperKey, std::string>& map,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd
) {
    for(auto el : toAdd){
        map.insert(el);
    }
}
