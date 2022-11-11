#include <iostream>
#include <unordered_map>
#include <list>
template<typename K, typename V>
class LruCache {
private:
    size_t Max_size_;
    size_t Temp_size_;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> mp;
    std::list<std::pair<K, V>> Elements_;
public:
    LruCache(size_t max_size) : Max_size_(max_size)
    {
        Temp_size_ = 0;
    };

    void Put(const K& key, const V& value)
    {
        if (mp.find(key) == mp.end()) {
            if(Temp_size_ < Max_size_){
                ++Temp_size_;
            } else {
                /*for (auto it = mp.begin(); it != mp.end(); ++it) {
                    if (it->second == --Elements_.end()) {
                        mp.erase(it);
                        break;
                    }
                }*/
                mp.erase(Elements_.back().first);
                Elements_.pop_back();
            }
        }else {
            Elements_.erase(mp[key]);
        }
        Elements_.push_front({key, value});
        mp[key] = Elements_.begin();
    }

    bool Get(const K& key, V* value)
    {
        auto it = mp.find(key);
        if(it == mp.end())
            return false;
        else
        {
            *value = (it->second->second);
            Elements_.push_front({key, (it->second->second)});
            Elements_.erase(it->second);
            mp.erase(key);
            mp[key] = Elements_.begin();
            return true;
        }
    }
};