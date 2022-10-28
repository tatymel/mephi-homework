#include <unordered_map>
#include <vector>
#include <string>

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart && this->FloatPart == rhs.FloatPart;
    }
};
namespace std{
    template<>
    struct hash<SuperKey>{
        size_t operator()(const SuperKey& sk) const{
            size_t h1 = hash<string>{}(sk.StrPart);
            size_t h2 = hash<int>{}(sk.IntPart);
            size_t h3 = hash<float>{}(sk.FloatPart);
            return h1 ^ h2 ^ (h3 << 1);
        }
    };
}
void PopulateHashMap(
        std::unordered_map<SuperKey, std::string>& hashMap,
        const std::vector<std::pair<SuperKey, std::string>>& toAdd
);


